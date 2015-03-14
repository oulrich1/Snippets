//helpers
// __________________________________________________________________________ //
// __________________________________________________________________________ //

function set_text( selector, text ) 
{
	$(selector).html(text);
}

// ---
function assert(condition, message) {
    if (!condition) {
        message = message || "Assertion failed";
        if (typeof Error !== "undefined") {
            throw new Error(message);
        }
        throw message; // Fallback
    }
}

function minLength( arr1, arr2 ) {return Math.min(arr1.length, arr2.length); }

function make_keys_from_object( obj ) { return Object.keys(obj); }

function swap( a1, i, j ) {
	var t = a1[i];
	a1[i] = a1[j];
	a1[j] = t;
}
