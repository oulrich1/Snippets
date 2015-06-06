#pragma once

#include "stdafx.h" // windwos stuff
#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <functional>


namespace {
	template <typename T>
	inline void stack_clear(std::stack<T>& stack) {
		while (!stack.empty()) {
			stack.pop();
		}
	}
}

/*  
	/-/-/-/-----------------------------------------------------------------\-\-\-\
	This is a builder class for creating CSplitterWndEx's from an Owner Window 
	CWnd and a CCreateContext object.  The user can use the left, right top bottom
	overloaded methods to create (1) empty non-leaf nodes which can contain at most
	2 nodes (2) leaf nodes which define the end of a branch in a view heirarchy.
	
	To get the pointer to the view heirarchy call "build()" which also resets the
	builder to it's state just after construction but before user commands.

	The view should automatically show up since the root splitter's parent was 
	passed in as "pOwnerWnd"
	\-\-\-\-----------------------------------------------------------------/-/-/-/
*/

class SplitterBuilder
{
	static const int CONST_MAX_NUM_CHILDREN = 2;
	
public:
	SplitterBuilder(CWnd* pOwnerWnd, CCreateContext* pContext, 
		bool bIsOwnerSplitterWnd = false)
	{
		ASSERT(pOwnerWnd);
		ASSERT_VALID(pOwnerWnd);
		_pOwnerWnd = pOwnerWnd;
		_pContext = pContext;
		_bIsOwnerASplitterWnd = bIsOwnerSplitterWnd;

		/* Figure out how to increment  */
		if (isWndOwnerAndSplitter(_pCurSplitterParent)) {
			initialize_incrementer();
		}

		common_construct();
	}
	virtual ~SplitterBuilder()
	{
		common_destruct();
	}

protected:
	typedef SplitterBuilder& Builder;
	typedef std::pair<int, int> pos_t;
	std::function<pos_t(pos_t)> increment_pos;
	pos_t starting_pos;

	bool isWndOwnerAndSplitter(CWnd* pWnd) {
		if (pWnd != _pOwnerWnd) {
			return false;
		}
		CSplitterWndEx* pSplit = dynamic_cast<CSplitterWndEx*>(pWnd);
		if (_bIsOwnerASplitterWnd) {
			ASSERT(pSplit);
			return true;
		} else {
			ASSERT(!pSplit);
			return false
		}
	}

	/* the incrementer increments the position relative from 0,0 
	in the direction assicated to the owner window's size */
	void initialize_incrementer() {
		CSplitterWndEx* pParentSplitter = dynamic_cast<CSplitterWndEx*>(_pOwnerWnd);
		ASSERT(pParentSplitter);
		const int rows = pParentSplitter->GetRowCount();
		const int cols = pParentSplitter->GetColumnCount();
		ASSERT(rows == 1 || cols == 1);
		if (cols > 1) { // then its a row vector of views
			increment_pos = [](pos_t pos) -> pos_t
			{
				return pos_t(pos.first, pos.second + 1);
			};
		} else { // then its a coumn vector of views
			increment_pos = [](pos_t pos) -> pos_t
			{
				return pos_t(pos.first + 1, pos.second);
			};
		}
		starting_pos = pos_t(0, 0);
	}

	void common_construct() {
		pushSplitter(_pOwnerWnd);
		_nStackParentsChildPosition.push(std::pair<int, int>()); // invalid pair..
		_pCurSplitter = createSplitter();
	}

	void common_destruct() {
		// this is returned after build. this is 
		// assumed to hold the entire view tree. the client must delete
		_pCurSplitter = NULL;
		stack_clear(_pSplitters);
		stack_clear(_nStackNodesCreatedPerLevel);
		stack_clear(_nStackParentsChildPosition);
	}

public:

	CSplitterWndEx* getCurrentSplitter()
	{
		return (CSplitterWndEx*) _pSplitters.top();
	}

	/* These are leafs, these will "create static" */
	/* These end the branch in the tree.. once two are called in a row
	then we complete a branch. When such branch is complete then splitter
	stack is popped */
	/* if this is the second one in a sequence at this level
	then popStack.. otherwise let the branch grow. */
	virtual Builder left(CRuntimeClass* pClass, CSize size)
	{
		const int rows = 1, cols = 2, rowIdx = 0, colIdx = 0;
		createLeafView(pClass, size, rows, cols, rowIdx, colIdx);
		return *this;
	}
	virtual Builder right(CRuntimeClass* pClass, CSize size)
	{
		const int rows = 1, cols = 2, rowIdx = 0, colIdx = 1;
		createLeafView(pClass, size, rows, cols, rowIdx, colIdx);
		return *this;
	}
	virtual Builder top(CRuntimeClass* pClass, CSize size)
	{
		const int rows = 2, cols = 1, rowIdx = 0, colIdx = 0;
		createLeafView(pClass, size, rows, cols, rowIdx, colIdx);
		return *this;
	}
	virtual Builder bottom(CRuntimeClass* pClass, CSize size)
	{
		const int rows = 2, cols = 1, rowIdx = 1, colIdx = 0;
		createLeafView(pClass, size, rows, cols, rowIdx, colIdx);
		return *this;
	}

	/* These are empty nodes (non-leafs), from here we can make subsequent
	calls to these but eventually all calls must end in a leaf call..
	these will push the current splitter pointer on the stack and create
	a new splitter. Therefore we expect this until we get to left(...) */
	virtual Builder left()
	{
		createNonLeaf(1, 2, 0, 0);
		return *this;
	}
	virtual Builder right()
	{ 
		createNonLeaf(1, 2, 0, 1);
		return *this;
	}
	virtual Builder top()
	{ 
		createNonLeaf(2, 1, 0, 0);
		return *this;
	}
	virtual Builder bottom()
	{ 
		createNonLeaf(2, 1, 1, 0);
		return *this;
	}

	virtual CSplitterWndEx* build()
	{
		ASSERT(_pCurSplitter);
		ASSERT(_pCurSplitterParent);
		CSplitterWndEx* pShineyNewSplitterTree = _pCurSplitter;
		reset();
		return pShineyNewSplitterTree;
	}

	virtual void reset()
	{
		common_destruct();
		common_construct();
	}

protected:

	/* Simplifies the leaf node creation... see left(...) for example */
	virtual void createLeafView(CRuntimeClass* pClass, CSize size,
		int rows, int cols, int rowIdx, int colIdx)
	{
		createStatic(rows, cols);
		_pCurSplitter->CreateView(rowIdx, colIdx, pClass, size, _pContext);
		incrementCompletedNodes();
		popSplitterIfDeadBranch();
	}

	/* Simplifies the 'empty' non-leaf nodes in the tree */
	virtual void createNonLeaf(int rows, int cols, int rowIdx, int colIdx)
	{
		createStatic(rows, cols);
		incrementCompletedNodes();
		pushSplitter(_pCurSplitter);
		_nStackParentsChildPosition.push(std::pair<int, int>(rowIdx, colIdx));
		_pCurSplitter = createSplitter();
	}


	/// only called when we create the first view in a layer (for each splitter)
	/* - This commands the builder to create a static splitter rows x cols
	shaped. the next two paremeters are indecies into the parent's children,
	used to get the ID of such child so that this new splitter can use such ID.
	- Since this is called from left(), right(), top(), bottom(), we know where
	we are coming from relative to the parent.. */
	void createStatic(int rows, int cols)
	{
		if (getCountCompletedNodes() > 0) {
			return;
		}

		if (_pCurSplitterParent != _pOwnerWnd || _bIsOwnerASplitterWnd) {
			pos_t pos;
			CSplitterWndEx* pParentSplitter = NULL;
			pParentSplitter = dynamic_cast<CSplitterWndEx*>(_pCurSplitterParent);
			ASSERT(pParentSplitter != NULL);
			if (_pCurSplitterParent == _pOwnerWnd && _bIsOwnerASplitterWnd) {
				pos = starting_pos;
			} else {
				pos = _nStackParentsChildPosition.top();
			}
			_pCurSplitter->CreateStatic(pParentSplitter, rows, cols, WS_CHILD | WS_VISIBLE,
				pParentSplitter->IdFromRowCol(pos.first, pos.second));
			if (_pCurSplitterParent == _pOwnerWnd && _bIsOwnerASplitterWnd) {
				starting_pos = increment_pos(starting_pos);
			}
		} else {
			ASSERT(!_bIsOwnerASplitterWnd && _pCurSplitterParent == _pOwnerWnd);
			_pCurSplitter->CreateStatic(_pOwnerWnd, rows, cols);
		} 
	}


	/* returns the expected index into the parent's child array of views */
	std::pair<int, int> getIndexFromSize(CSize splitterSize)
	{
	}

	/* called when we create a non-leaf node.. we need to go deeper */
	void pushSplitter(CWnd* pWnd)
	{
		_pSplitters.push(pWnd);
		_pCurSplitterParent = pWnd;
		_nStackNodesCreatedPerLevel.push(0); // get ready for the nexot level

		// this is done outside everywhere this is called
		// _nStackParentsChildPosition.push(std::pair<int,int>(?,?)); 
	}

	CSplitterWndEx* createSplitter()
	{
		return new CSplitterWndEx();
	}

	/* Only called when we have completed a subtree (both children are done) */
	CWnd* popSplitter()
	{
		_pCurSplitter = getCurrentSplitter();
		_pSplitters.pop();
		if (_pSplitters.size() == 0) {
			_pCurSplitterParent = _pOwnerWnd;
		} else {
			_pCurSplitterParent = _pSplitters.top();
		}
		ASSERT(_pCurSplitter);
		ASSERT(_pCurSplitterParent);

		// we are done with a level
		_nStackNodesCreatedPerLevel.pop();
		_nStackParentsChildPosition.pop();

		return _pCurSplitter;
	}

	void incrementCompletedNodes()
	{
		int nCount = _nStackNodesCreatedPerLevel.top();
		_nStackNodesCreatedPerLevel.pop();
		_nStackNodesCreatedPerLevel.push(++nCount);
	}
	int getCountCompletedNodes()
	{
		return _nStackNodesCreatedPerLevel.top();
	}
	bool isBranchDead()
	{
		return !_nStackNodesCreatedPerLevel.empty() 
			&& getCountCompletedNodes() == CONST_MAX_NUM_CHILDREN;
	}
	/* Pops the splitter when:
	(1) when the user has completed a subtree
	a.) after inserting leaf nodes.. which completes a branch
	b.) after completeing all branches of a subtree */
	void popSplitterIfDeadBranch()
	{
		while (_pCurSplitterParent != _pOwnerWnd && isBranchDead()) {
			popSplitter();
		}

		if (_pCurSplitterParent == _pOwnerWnd) {
			TRACE("Tree Complete\n");
		} else {
			TRACE(" Parsing Tree some more..\n");
		}
	}

private:
	/* Contants for creating stuff */
	CWnd* 			_pOwnerWnd;
	bool			_bIsOwnerASplitterWnd;
	CCreateContext* _pContext;

	/* Vars that point to current state */
	CWnd* 					_pCurSplitterParent; // only used when creating static
	CSplitterWndEx* 		_pCurSplitter; 		 // when we create splitters this is the current
	std::stack<CWnd*> 		_pSplitters; 		 // this is used to keep track of splitters
	std::stack<int> 				_nStackNodesCreatedPerLevel;
	std::stack<std::pair<int, int>> _nStackParentsChildPosition;
};


//
///* Example Layouts */
//namespace SplitterBuilderTests {
//
//	void test_splitter_builder(CWnd* pOwner, CCreateContext* pContext) {
//
//		/* Create a builder with the owner of the splitter and the context which
//		each splitter/subsplitter needs to know what its configuration is */
//		SplitterBuilder builder(pOwner, pContext);
//		CSplitterWnd* m_pWndSplitter =
//			builder
//			.left(RUNTIME_CLASS(ColumnTabs), CSize(300, 0))		// this creates a leaf node view within the current splitter
//			.right()											// this creates a non-leaf node which will contain more splitter windows
//				.left(RUNTIME_CLASS(LayoutSwitcherView), CSize())  // once we create a full subtree of leaf nodes, the subtree is complete.
//				.right(RUNTIME_CLASS(LayoutSwitcherView), CSize()) // there is no error checking so the splitter will just break if you use it wrong
//			.build();
//		ASSERT(m_pWndSplitter);
//
//		/// Note: we are using the same builder. After we call build() the 
//		/// builder is reset to it's original configuration from construction
//
//		/* Example two - left: [top bottom], right: [top bottom] */
//		m_pWndSplitter =
//			builder
//			.left().top(RUNTIME_CLASS(LayoutSwitcherView), CSize()).bottom(RUNTIME_CLASS(LayoutSwitcherView), CSize())
//			.right().top(RUNTIME_CLASS(LayoutSwitcherView), CSize()).bottom(RUNTIME_CLASS(LayoutSwitcherView), CSize())
//			.build();
//		ASSERT(m_pWndSplitter);
//
//		/* Example three */
//		m_pWndSplitter =
//			builder
//				.left(RUNTIME_CLASS(ColumnTabs), CSize())
//				.right()
//					.left(RUNTIME_CLASS(StageView), CSize())
//					.right()
//						.top(RUNTIME_CLASS(LayoutSwitcherView), CSize())
//						.bottom(RUNTIME_CLASS(LayoutSwitcherView), CSize())
//			.build();
//		ASSERT(m_pWndSplitter);
//	}
//}
