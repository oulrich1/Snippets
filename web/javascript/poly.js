
// __________________________________________________________________________ //
// __________________________________________________________________________ //

// describes: (a*x)^b
function Term() {
	return {
		coeff: 0,
		expon: 0,
		eval: function(x) {
			return Math.pow(this.coeff * x, this.expon);
		}
	}
}

// evalutes a polynomial described by sequence of terms at x, returns the result
function eval_poly( terms, x )
{
	var y = 0;
	for (var i = 0; i < terms.length; i++) {
		y += terms[i].eval(x);
	};
	return y;
}

function Poly() {
	return {
		terms: [],
		eval: function(x) { return eval_poly( this.terms, x ); }
	}
}


// generates a range of values from [start to end)
function generate( start, end )
{
	var vals = [];
	for (var i = start; i < end; i++) {
		vals.push( i );	
	};
	return vals;
}

// returns array of terms 
function terms_from_values( vals, callback ) {
	if ( !callback ) {
		callback = function (coeff) {return coeff;}; // identity function
	}
	var terms = [];
	for (var i = 0; i < vals.length; i++) {
		var term = Term();
		term.coeff = callback(vals[i]);
		term.expon = (vals.length-1)-i;
		terms.push( term );
	};
	return terms; // returns array of terms
}

// returns Poly object which contains terms
function poly_from_values( vals, callback ) {
	var terms = terms_from_values( vals, callback );	
	var poly = Poly();
	poly.terms = terms;
	return poly;
}

