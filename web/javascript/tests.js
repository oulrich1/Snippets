
// __________________________________________________________________________ //
// __________________________________________________________________________ //
// --- TESTS --- 

function test1_jquery() 
{
	var X = [1,2,3,4];
	var Y = [1,2,3];
	var P = [0.25, 0.50, 0.15, 0.10];

	set_text( "#elementId", std_dev( X, P ) );
}

function test2_mean_sum() 
{
	var X = [0,1,2];
	var Y = [3,4];
	var P_joint = [[0.1, 0.2, 0.2],
				   [0.1, 0.2, 0.2]];

    console.log( "Mean Sum X, Y: " + mean_sum( X, Y, P_joint) );
}

function test3_independence() 
{

	var X = [0,1,2];
	var Y = [3,4];
	P_joint = [[0.1, 0.2, 0.2],
			   [0.2, 0.2, 0.1]];

    console.log( "(1) Is Independent: " + is_independent( X, Y, P_joint ) );

	P_joint = [[0.1, 0.2, 0.2],
			   [0.1, 0.2, 0.2]];

    console.log( "(2) Is Independent: " + is_independent( X, Y, P_joint ) );

    var coeff = correlation_coefficient(X, Y, sum(transpose(P_joint)), sum(P_joint) );
    console.log( "(3) Correlation Coef: " + coeff );
}

function test_apply() {
	var mat = [[0,1,2,3,4]];
	for (var i = 1; i < 5; i++) {
		mat.push( add(mat[0],i) );
	};
	console.log( "5x5 gradient thing: " );
	print_matrix( console, mat );
	console.log("\n");

	mat = ApplyEach().run( mat, function(m, k, i, j) {
		 // for each element apply the following::..
		 var bounding_kernal = getBoundingKernal(m, k, i, j);
		 var average = 0;
		 var count = 0;
		 for (var col = j-bounding_kernal[0];  col < j+bounding_kernal[2]; col++) {
		 	for (var row = i-bounding_kernal[1]; row < i+bounding_kernal[3]; row++) {
				var val = m[row][col];
				if ( val !== undefined )
				{
					average += val;
					count += 1;
				}
		 	};
		 };
		 average /= count;
		 return average*2;
	});

	print_matrix( console, mat );
}

