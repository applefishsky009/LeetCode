#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

//想到用Hash Table，涉及到字符串，使用unordered_map统计字符串个数作为“池”；
class Solution
{
  public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
		size_t wordLength = words.front().length();
		size_t catLength = wordLength * words.size();
		vector<int> result;
		if (s.length() < catLength)
			return result;
		//制作字符串池
		unordered_map<string, int> wordCount;
		for (auto const &word : words)
			++wordCount[word];
		//逐个字符暴力破解，直到剩余长度不够
		for (auto i = begin(s); i <= prev(end(s), catLength); ++i)
		{
			unordered_map<string, int> unused(wordCount);
			for (auto j = i; j != next(i, catLength); j += wordLength)
			{
				auto pos = unused.find(string(j, next(j, wordLength)));
				if (pos == unused.end() || pos->second == 0)
					break;
				if (--pos->second == 0)
					unused.erase(pos);
			}
			if (unused.size() == 0)
				result.push_back(distance(begin(s), i));
		}
		return result;
    }
};

int main()
{
    Solution s1;
    string s("barfoothefoobarman");
    vector<string> words{"foo", "bar"};
    vector<int> result = s1.findSubstring(s, words);
	show1DVector(result);
    return 0;
}