
// __________________________________________________________________________ //
// __________________________________________________________________________ //
/// ---

// creates a new matrix of size "size", an object with 
// cx and cy the width and height of the desired matrix
// the elements are not initialized
function NewMatrix( size ) 
{
	var mat = new Array( size.cy );    // height (#rows)
	for (var i = 0; i < mat.length; i++) {
		mat[i] = new Array( size.cx ); // width (#cols)
	};
	return mat;
}

function InitMatrix( mat, val )
{
	for (var i = 0; i < mat.length; i++) { 		  // each row
		for (var j = 0; j < mat[i].length; j++) { // each col
			mat[i][j] = val;					  // init with same value
		};
	};
}

function print_matrix( logger, matrix )
{
	if ( !logger && !logger.log ) 
	{
		return false;
	}	

	for (var i = 0; i < matrix.length; i++) {
		var str = "";
		for (var j = 0; j < matrix[i].length; j++) {
			 str += matrix[i][j] + " ";
		};
		logger.log( str );
	};

	return true;
}

// rotate by 90 degrees
function matrix_rotate_normal( mat, direction )
{
	// mat is [n x m] matrix
	var n = mat.length; 	// height
	var m = mat[0].length;  // width

	var newMat = new Array( m );    // array of rows
	for (var i = m - 1; i >= 0; i--) {
		newMat[i] = new Array( n ); // new number of cols
	};

	if ( direction == 1 || direction === undefined )
	{
		// assume newMat is [m x n] matrix, now copy each element 
		for (var i = n-1; i >= 0; i--) {
			for (var j = m-1; j >= 0; j--) {
				var l = j;
				var p = (n-1)-i;
				newMat[l][p] = mat[i][j]; // for all i,j in mat
			};
		};
	}
	else if ( direction == -1 )
	{
		// assume newMat is [m x n] matrix, now copy each element 
		for (var i = n-1; i >= 0; i--) {
			for (var j = m-1; j >= 0; j--) {
				var l = (m-1)-j;
				var p = i;
				newMat[l][p] = mat[i][j]; // for all i,j in mat
			};
		};
	}
	return newMat;
}

function matrix_rotate_inplace( mat, direction )
{
	assert( (mat.length > 0) && (mat.length == mat[0].length) ); // [n x n]

	if ( direction === undefined || direction > 0 )
	{
		var r = 0;
		var t = 0;   // temp, for swaps all the way around the mat
		var h = mat.length;
		var w = mat[0].length;
		for (var row = 0; row < (h/2); ++row) {
			for (var col = row; col < (w-2)-row; ++col) {
				t = mat[row][col]; 							 		// store for layer when replacing top right
				mat[row][col] 				= mat[(h-1)-col][row]; 	// replace topleft with bottom left
				mat[(h-1)-col][row] 		= mat[(h-1)-row][(w-1)-col]; // replace bottom left with bottom right
				mat[(h-1)-row][(w-1)-col] 	= mat[col][(w-1)-row]; 	// replace bottom right with top right
				mat[col][(w-1)-row] 		= t; 					// topright with what was in topleft ( in t )
			};
		};
	}
	else if ( direction < 0 )
	{
		var r = 0;
		var t = 0;   // temp, for swaps all the way around the mat
		var h = mat.length;
		var w = mat[0].length;
		for (var row = 0; row < (h/2); ++row) {
			for (var col = row; col < (w-2)-row; ++col) {
				t = mat[row][col]; 							 		// store for layer when replacing bottom left
				mat[row][col] 				= mat[col][(w-1)-row]; 	// replace top left
				mat[col][(w-1)-row] 		= mat[(h-1)-row][(w-1)-col]; // replace top right
				mat[(h-1)-row][(w-1)-col]   = mat[(h-1)-col][row]; // replace bottom right
				mat[(h-1)-col][row] 		= t; // replace bottom left
			};
		};
	}

	return mat;
}

// rotate matrix left or right by 90 degrees
function matrix_rotate( m, direction, bShouldReplaceParam ) 
{
	if ( direction === undefined ) {
		direction = 1; // for right rotate
	};

	if ( bShouldReplaceParam !== undefined && 
		 bShouldReplaceParam === true )
	{
		var width = m.length;
		var height = m[0].length;	
		if ( width == height )
		{
			return matrix_rotate_inplace( m, direction );
		}
	}

	// if we dont want the param m to change then we cannot rotate
	// in place anyways, so just create a new mat like normal
	return matrix_rotate_normal( m, direction );
}


// __________________________________________________________________________ //
// returns 4-tuple left, top, right, bottom of the distances/widths 
// from center to the edge of kernal of size k such that the kernal 
// is an ROI that includes only the elements in the mat's range
function getBoundingKernal(m, k, i, j) {
	// kernal with not including center
	var w = Math.floor(k/2);

	// kernel distances not including the center
	var l, t, r, b;

	// expected width w or the smaller width
	l = (j >= w ) ? w : j;
	t = (i >= w ) ? w : i;
	r = ((m[i].length-1)-j >= w ) ? w : (m[i].length-1)-j; 
	b = ((m.length-1)-i >= w ) ? w : (m.length-1)-i;

	// 4-tuple
	return [l,t,r,b];
}




// returns undefined if is array.. didnt do transpose yet
function isElementNotArrayDoTranspose( mat )
{
	// check if 0-th element is not an array (if so, 
 	// transpose vec into a column of rows each with 1 element)
	if ( !Array.isArray( mat[0] ) ) 
	{
		var m2 = new Array( mat.length );
		for (var i = mat.length - 1; i >= 0; i--) {
			m2[i] = [];
			m2[i].push( mat[i] );
		}
		return m2;
	}
	return undefined;
}

// private transpose - simply transposes
function _transpose( mat )
{
	var newMat = new Array( mat[0].length );
	for (var col = mat[0].length - 1; col >= 0; col--) {
		var v = new Array( mat.length );
		for (var row = mat.length - 1; row >= 0; row--) {
			v[row] = mat[row][col];
		};
		newMat[col] = v;
	};
	return newMat;
}


function transpose( mat )
{
	// check if not even array or empty
	if ( !Array.isArray( mat ) || 
		 mat.length == 0 )
	{
		return mat;
	}	

	// check if elements are not arrays.. if not then transpose 
	if( t = isElementNotArrayDoTranspose( mat ) ) 
	{
		return t;
	}

	// check if just a vector of empty vectors
	if ( mat[0].length === 0 )
	{
		return mat;
	}

	return _transpose( mat );
}

// sums in one direction at a time, depending on the paramter "mat"
// (0) return param if the param is not an array at least or if length is 0 
// (1) if 2d mat then returns 1d vec of sums
// (2) if 1d vec then returns the sum of the elements
function sum( mat ) 
{
	// not array and not summable
	if ( !Array.isArray( mat ) || 
		 mat.length == 0 )
	{
		return mat;
	}

	// then its a matrix (2d array)
	// return vector of sums, where each sum is that 
	// sum of the elements in the i-th row.
	if ( Array.isArray( mat[0] ) )  
	{
		var sumVec = new Array( mat.length ); 
		for (var i = mat.length - 1; i >= 0; i--) {
			sumVec[i] = sum( mat[i] );
		};
		return sumVec;
	}

	// otherwise its a 1d array.. 
	// just sum the values and return
	var v = 0;
	for (var i = mat.length - 1; 
		 i >= 0; i--) {
		v += mat[i];
	};
	return v;
}


// elementwise multiply
// takes two arrays and returns a 3rd array 
// whose elements are products of the respective 
// i-th elements of the arrays given
function multiply( a1, a2 )
{
	if ( !a2 )
		return [];

	var a3 = [];
	if ( !Array.isArray(a2) )
	{	// multiply a1 by scalar
		var arr_length = a1.length;
		a3 = new Array( arr_length );
		for (var i = arr_length - 1; i >= 0; i--) {
			a3[i] = ( a1[i] * a2 );
		};
	}
	else
	{	// multiply element by element
		var arr_length = minLength(a1, a2);
		a3 = new Array( arr_length );
		for (var i = arr_length - 1; i >= 0; i--) {
			a3[i] = ( a1[i] * a2[i] );
		};
	}
	return a3;	
}

// elementwise add, or scalar broadcast add if a2 is not array
function add( a1, a2 )
{
	if ( !a2 )
		return [];

	var a3 = [];
	if ( !Array.isArray(a2) )
	{	// add a1 by scalar
		var arr_length = a1.length;
		a3 = new Array( arr_length );
		for (var i = arr_length - 1; i >= 0; i--) {
			a3[i] = a1[i] + a2;
		};
	}
	else
	{	// add element by element
		var arr_length = minLength(a1, a2);
		a3 = new Array( arr_length );
		for (var i = arr_length - 1; i >= 0; i--) {
			a3[i] = a1[i] + a2[i];
		};
	}
	return a3;	
}

//element wise, or broadcast a2 if a2 is not array
function subtract( a1, a2 )
{
	if ( !a2 )
		return [];

	var a3 = [];
	if ( !Array.isArray(a2) )
	{	// add a1 by scalar
		var arr_length = a1.length;
		a3 = new Array( arr_length );
		for (var i = arr_length - 1; i >= 0; i--) {
			a3[i] = a1[i] - a2;
		};
	}
	else
	{	// add element by element
		var arr_length = minLength(a1, a2);
		a3 = new Array( arr_length );
		for (var i = arr_length - 1; i >= 0; i--) {
			a3[i] = a1[i] - a2[i];
		};
	}
	return a3;	
}

function dot( arr1, arr2 )
{
	return sum( multiply( arr1, arr2 ) );
}

// returns the sum of the squares of elements of a1
function sum_square( a1 )
{
	return dot( a1, a1 );
}
