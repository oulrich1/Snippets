#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <assert.h>

using namespace std;

class Node
{
public:
	Node(int _id){ id = _id; }
	~Node(){}
	std::map<int, Node*> children; // or hash_set
	Node* pParent;
	int id;
};

class Tree
{
public:
	typedef std::map<int, Node*> map_t;

	Tree(vector <int> a, vector <int> b, int s)
	{
		m_root = NULL;

		// assert( a.size() == b.size() )
		for (int i = 0; i < a.size(); ++i)
		{
			Node* n1 = findCreateIfNot(a[i]);	
			Node* n2 = findCreateIfNot(a[i]);	
			n1->children[n2->id] = n2;
			n2->pParent = n1;

			if (!m_root) { // init root 
				m_root = n1;
			} else if (m_root == n2) { 
				// if root is child then assign root to be the parent
				m_root = n2->pParent;
			}
		}
	}
	~Tree()
	{

	}

	Node* findCreateIfNot(int id)
	{
		Node*& nodeRef = nodes[id];
		if ( !nodeRef )
		{
			nodeRef = new Node(id);
		}
		return nodeRef;
	}

	Node* findNode( int s )
	{
		Node*& nodeRef = nodes[s];
		assert(nodeRef);
		return nodeRef;
	}

	void print()
	{
		print( m_root );
	}

	void print( Node* root )
	{
		assert( root );	
		for (map_t::iterator i = root->children.begin(); 
			 i != root->children.end(); ++i)
		{
			print( i->second );
		}
		cout << root->id << endl;
	}

	map_t nodes;
	Node* m_root;
};


class OneEntrance
{
public:
	int count(vector <int> a, vector <int> b, int s)
	{

		Tree tree( a, b, s );
		tree.print();

		int _count = 0;
		int N = a.size();
		int Nf = factorial( N );

		int nNotPossible = 0; // find from tree structure

		/* Find the number of impossible configurations from 
		   start node 's' to any empty node 'x'
		*/
		

		

		_count = Nf - nNotPossible;

		return _count;	
	}

private:
	int factorial(int n) {
		static vector<int> _Fact = {0,1,2,6,24}; //..
		if (n < 0) {return 1;} //note: not recursive
		for (int i = _Fact.size(); i <= n; ++i) {
			_Fact.push_back(_Fact[i-1] * i); 
		}
		return _Fact[n];
	}
};

int main(int argc, char const *argv[])
{
	OneEntrance ooo;

	// the i-th value is a bidirectional connection between a and b
	vector<int> a; // a[i]-th room 
	vector<int> b; // b[i]-th room
	int s; // the one entrance leads to this s-th room

	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	cout << ooo.count(a, b, s) << endl;
	a.clear();
	b.clear();
	
	return 0;
}