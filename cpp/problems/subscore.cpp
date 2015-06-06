#include <string>
#include <iostream>

using namespace std;

//// 10 min to figure out a solution

class SquareScoresDiv2
{	
public:
	/// O(n2)
	int getscore(string s)
	{
		int score = 0;
		int cur_start_pos = 0;
		/* Left to right, scan until not same character.
			if not same, dont increment the width, but break
			and increment score counter. Then continue with next item 
		*/

		while( cur_start_pos < s.length() )
		{
			char curChar = s[cur_start_pos];
			for (int i = cur_start_pos; i < s.length(); ++i)
			{
				if (s[i] != curChar){
					break;
				}
				score++;
			}
			cur_start_pos++;
		}

		return score;
	}
};

int main(int argc, char const *argv[])
{
	SquareScoresDiv2 s;
	cout << s.getscore("aaaba") << endl;
	cout << s.getscore("zzzxxzz") << endl;
	cout << s.getscore("p") << endl;
	cout << s.getscore("abcdefghijklmnopqrstuvwxyz") << endl;
	cout << s.getscore("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") << endl;
	
	return 0;
}