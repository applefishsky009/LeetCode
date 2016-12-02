#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//dvdf返回3，注意从上一个重复字符的下一个字符计数
class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
		string temp = "";
		int maxLen = 0; //变量要初始化，否则在一些编译器上会出错
		for (int i = 0; i < s.size(); ++i)
		{
			char tempOne = s[i];
			size_t locate = temp.find(tempOne);
			if (locate != string::npos)
			{
				int len = temp.size();
				maxLen = max(maxLen, len);
				temp = temp.substr(locate + 1); //从上一个重复字符的下一个字符计数
			}
			temp.push_back(tempOne);
		}
		int len = temp.size();
		maxLen = max(maxLen, len); //最后一次
		return maxLen;
    }
};

int main()
{
    string s = "abcabcbb";
    Solution s1;
    cout << s1.lengthOfLongestSubstring(s) << endl;
    return 0;
}