
// __________________________________________________________________________ //
// __________________________________________________________________________ //

$(document).ready( function ()
{
	test1_jquery();
	test2_mean_sum();
	test3_independence();

	var fibGen = CreateFib();
	for (var i = 0; i < 80; i++) {
		console.log("Fib #" + i + ": " + fibGen.find(i));
	};

	var fact = CreateFactorial();
	for (var i = 0; i < 150; i++) {
		console.log("Factorial #" + i + ": " + fact.find(i));
	};

	console.log( binomial(2, 5, 1/6) );
	console.log( binomial_range(1, 3, 5, 1/6) );

	Mat = [[0.1, 0.2, 0.2],
			   [0.2, 0.2, 0.1]];

	console.log(Mat);
	console.log(matrix_rotate(Mat));

	Mat = [[1,0,2,5],[3,1,6,9],[8,7,1,4],[2,5,9,7]];

	console.log("Original" + Mat);
	console.log( "InPlace 4x4 (1 right rotation):" + matrix_rotate(Mat, 1, true) );

	console.log( "InPlace 4x4 (3 more right rotations):" +
			matrix_rotate(matrix_rotate(matrix_rotate(Mat, 1, true), 1, true), 1, true)
		);
	console.log( "CopyMat 4x4 (4 right rotations):" +
			matrix_rotate(matrix_rotate(matrix_rotate(matrix_rotate(Mat, 1, false), 1, false), 1, false), 1, false)
		);

	test_apply();
});

// __________________________________________________________________________ //
// __________________________________________________________________________ //


