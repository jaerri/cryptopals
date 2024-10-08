#include <iostream>
// #include <unordered_set>
#include <string>

#include "hex.hpp"
#include "aes.hpp"
#include "byteutils.hpp"

using namespace std;

int main()
{
    freopen("8.txt", "r", stdin);
	string input;
    
	// unordered_set<string> blocks;
	// string result; int maxscore=0;
	// while (getline(cin, input))
	// {
	// 	bytec bytes = hexDecode(input);
	// 	int score = 0;
	// 	for (auto it=bytes.begin(); it!=bytes.end(); it+=16)
	// 	{
	// 		string block(it, it+16);
	// 		if (blocks.find(block) == blocks.end()) blocks.insert(block);
	// 		else score++;
	// 	}
	// 	if (score>maxscore)
	// 	{
	// 		result = input; maxscore = score;
	// 	}	
	// }
	// cout<<maxscore<<endl<<result<<endl;
	while (getline(cin, input))
	{
		bytec bytes = hexDecode(input);
		if (AES_ECB_Detect(bytes)) cout<<input<<endl;
	}
    
    return 0;
}