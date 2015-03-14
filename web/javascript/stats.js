
// ---
// combinations requies memoized.js

function expected_value( arr, p_arr ) 
{
	var sum = 0;
	for (var i = arr.length - 1; i >= 0; i--) {
		sum += arr[i] * p_arr[i];
	};
	return sum; // weighted sum
}
function variance( arr, p_arr )
{
	var mean = expected_value( arr, p_arr );

	var variance = 0;

	for (var i = arr.length - 1; i >= 0; i--) {

		// take the diff and square it
		var diff = (arr[i] - mean);
		diff *= diff;

		// weight the squared difference by p_arr[i]
		variance += diff * p_arr[i]; 
	};
	return variance;
}

function std_dev ( arr, p_arr )
{
	return Math.sqrt( variance( arr, p_arr ) );
}

// ---

function mean( a, p )
{
	assert( a.length === p.length, "Mean could not be calculated" );
	return expected_value( a, p );
}

function average( a1 ) 
{  
	if (!Array.isArray(a1) && a1.length == 0)  // average of empty array is nothing
		return 0;

	var p = [];
	var m = 0;

	for (var i = 0; i < a1.length; i++) {
		p.push( 1 ); // each element in a1 is weighted 1
	};

	// check if 2d array (matrix), if so then average each 
	// array independantly and average the sum of averages
	if ( Array.isArray(a1[0]) ) {
		for (var i = 0; i < a1.length; i++) {
			m += (mean(a1[i], p) / a1.length); // distributive average
		};
	} else {
		m = mean(a1, p);
	}
	return m;
}

// ---

// case1: P(X|Y) = P(X) && case2: P(X^Y) = P(X)*P(Y)
function check_independence( X, Y, P_joint, X_Totals, Y_Totals )
{
	// along Y
	for (var i = Y_Totals.length - 1; i >= 0; i--) {
		//along X
		for (var j = X_Totals.length - 1; j >= 0; j--) {
			if ( P_joint[i][j] != Y_Totals[i] * X_Totals[j] ) 
			{
				return false;
			}
			if ( (P_joint[i][j] / Y_Totals[i]) != X_Totals[j] ) 
			{
				return false;
			}
		};
	};	
	return true;
}

function is_independent( X, Y, P )
{
	var is_first_row = true;
	var X_Totals = []; 					 // pushed 0's if is_first row
	var Y_Totals = [];

	// find X and Y totals 
	for (var i = 0; i < P.length; i++) { // rows
		Y_Totals.push( 0 ); 			 // init with 0 sum first time in row

		for (var j = 0; j < P[i].length; j++) { // cols
			var p = P[i][j]; 			 // probability that both i in X and j in Y

			if ( is_first_row ) {
				X_Totals.push( 0 );      // init with 0 first time going through
			} 

			X_Totals[j] += p;			 // count probabilty for j-th X (column)
			Y_Totals[i] += p; 			 // count total probabilty for i-th Y
		};

		is_first_row = false;
	};

	if ( !check_independence( X, Y, P, X_Totals, Y_Totals ) )
	{
		return false;
	} 
	return true;
}

// takes the mean of the sum of X and Y
// which is the sum of the mean of X and Y
function mean_sum( X, Y, P ) {
	var Ex = mean( X, sum(transpose(P)) );
	var Ey = mean( Y, sum(P) );
	return Ex + Ey;
}

function correlation_coefficient( a1, a2, p1, p2 )
{
	//r = Σ (xy) / sqrt [ ( Σ x2 ) * ( Σ y2 ) ]
	var x = subtract( a1, mean( a1, p1 ) );
	var y = subtract( a2, mean( a2, p2 ) );
	var numerator 	= dot(x,y); 
	var denominator = Math.sqrt( sum_square(x) * sum_square(y) );
	return numerator / denominator;
}

var _fact = CreateFactorial();

function numCombinations( n, r )
{
	// n * (n-1) * (n-2) .. * (n-r+1) / r! === nPr / r!
	// n! / ((n-r)! * r!) 
	// return factorial(n) / (factorial(n-r) * factorial(r));
	return _fact.find(n) / (_fact.find(n-r) * _fact.find(r));
}

// returns probabilty that out of n trials,
// x trails are successful, where each event 
// i in x is a success with probability P
function binomial(x, n, p)
{
	return numCombinations( n, x ) * Math.pow(p, x) * Math.pow(1-p, n-x);
}

function binomial_range( a, b, n, p )
{
	var s = 0;
	for (var i = a; i <= b; i++) {
		s += binomial( i, n, p );
	}
	return s;
}
