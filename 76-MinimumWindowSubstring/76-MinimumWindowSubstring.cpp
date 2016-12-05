#include <string>
#include <climits>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

//注意处理重复元素
class Solution
{
  public:
    string minWindow(string S, string T)
    {
		if (S.empty())
			return "";
		if (S.size() < T.size())
			return "";
		const int ASCII_MAX = 256; //hash table
		int appeared_count[ASCII_MAX];
		int expected_count[ASCII_MAX];
		fill(appeared_count, appeared_count + ASCII_MAX, 0);
		fill(expected_count, expected_count + ASCII_MAX, 0); //初始化
		for (size_t i = 0; i < T.size(); i++)
			expected_count[T[i]]++;	    //建立hash table
		int minWidth = INT_MAX, min_start = 0; //窗口大小，起点
		int wnd_start = 0;		       //尾指针
		int appeared = 0;		       //包含一个完整T;
		//尾指针不断向后扫
		for (size_t wnd_end = 0; wnd_end < S.size(); wnd_end++)
		{
			//找出第一个串很重要，然后利用hash table 收缩
			if (expected_count[S[wnd_end]] > 0)
			{								      // this char is a part of T
				appeared_count[S[wnd_end]]++;				      //现有哈希表，注意，超出数量也算
				if (appeared_count[S[wnd_end]] <= expected_count[S[wnd_end]]) //没有超出数量
					appeared++;						      //现有字符串含有的T中的字符个数，注意第一次找到串后这个值就不变了
			}
			if (appeared == T.size())
			{ //利用字符个数判断是否包含一个完整T，很巧妙
				//收缩头指针
				//保证appeared_count[S[wnd_end]]不小于expected_count[S[wnd_end]]
				while (appeared_count[S[wnd_start]] > expected_count[S[wnd_start]] || expected_count[S[wnd_start]] == 0)
				{				    //多出的重复元素(头重复元素收缩)或者T中没有的元素
					appeared_count[S[wnd_start]]--; //如果是T中没有的,会成为负值，不影响计算
					wnd_start++;
				}
				if (minWidth > (wnd_end - wnd_start + 1))
				{ //取最小
					minWidth = wnd_end - wnd_start + 1;
					min_start = wnd_start;
				}
			}
		}
		if (minWidth == INT_MAX)
			return "";
		else
			return S.substr(min_start, minWidth);
    }
};

int main()
{
    Solution s1;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    cout << s1.minWindow(s, t) << endl;
    return 0;
}