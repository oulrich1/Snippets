
// __________________________________________________________________________ //
// __________________________________________________________________________ //
/// ---

// returns an object that encapsulates fib sequence. comes 
// with a find function that finds the n-th fib. fibs are 
// stored in the _Fib array 
function CreateFib(){ 
	return {
		_Fib: [],
		find: function(n) { 
			for( var i = this._Fib.length; i <= n; ++i) {
				var f = 0;
				if (i<=0){f=0;} 
				else if (i<=2){f=1;} 
				else { f = this._Fib[i-1] + this._Fib[i-2]; } 
				this._Fib[i] = f; 
			} 
			return this._Fib[n]; 
		},
		clear: function() { this._Fib = []; }
	};
}


function CreateFactorial() {
	return {
		_Fact: [0,1,2],
		find: function( n ) {
			if (n < 0) {return 1;} //note: not recursive
			for (var i = this._Fact.length; i <= n; ++i) {
				this._Fact.push(this._Fact[i-1] * i); 
			}
			return this._Fact[n];
		}, 
		clear: function() {this.init();},
		init: function() {this._Fact = [0,1,2];}
	};
}
function factorial( n )
{
	var f = n;		
	while( n >= 2 ) {
		n -= 1;
		f = f * n;
	}
	return f;
}

/* permutes all of the permutations of a1 */
function permute( a1, i ) 
{
  	if (i == a1.length)
	{	
		console.log( a1 );
   	}
   	else
   	{
       	for (var j = i; j < a1.length; j++)
       	{
          	swap(a1, i, j);
          	permute(a1, i+1);
          	swap(a1, i, j);
       	}
  	}
} 

/* Applies a callback to each element in the mat */
function ApplyEach() {
	return {
		// public
		// the only necessary function
		run: function(mat, func) {
			this.init( func );
			var numFailures = 0;
			var newMat = NewMatrix( { cx: mat[0].length, cy: mat.length } );
			for (var i = 0; i < mat.length; i++) {
				for (var j = 0; j < mat[i].length; j++) {
					newMat[i][j] = this.callback( mat, this._k, i, j );
					if ( newMat[i][j] === undefined ) {
						numFailures += 1;	
					}
				};
			};
			return newMat;
		},

		// sort of public
		init: function(callback){ 
			if(callback !== undefined) 
				this.setCallback(callback);
		},
		setCallback: function(func) {
			this.callback = func;
		},
		setKernSize: function(K) {
			if( K !== undefined )
				this._k = K;	
		},
		_k: 3,
		callback: function(mat, kern, i, j){ return mat[i][j]; },
	};
}

