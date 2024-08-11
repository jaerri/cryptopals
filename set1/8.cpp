#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "hex.hpp"

using namespace std;

struct VectorHash {
    size_t operator()(const vector<unsigned char>& v) const {
        hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};
int main()
{
    freopen("8.txt", "r", stdin);
	string input;
    
	unordered_set<vector<unsigned char>, VectorHash> blocks;
	string result; int maxscore=0;
	while (getline(cin, input))
	{
		auto bytes = hexDecode(input);
		int score = 0;
		for (auto it=bytes.begin(); it!=bytes.end(); it+=16)
		{
			vector<unsigned char> block(it, it+16);
			if (blocks.find(block) == blocks.end()) blocks.insert(block);
			else score++;
		}
		if (score>maxscore)
		{
			result = input; maxscore = score;
		}	
	}
	cout<<maxscore<<endl<<result<<endl;
    
    return 0;
}