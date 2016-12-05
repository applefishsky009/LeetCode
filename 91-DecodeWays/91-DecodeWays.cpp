#include <string>
#include <iostream>
using namespace std;

//我擦，巨坑，注意0！！！带条件的斐波那契，
//Count[i] = Count[i - 1] + Count[i - 2]，如果i-1可以单独解析，并且i-1,i-2可以连着解析
//当前状态与前两个状态息息相关
class Solution
{
  public:
    int numDecodings(const string &s)
    {
		if (s.empty() || s[0] == '0')
			return 0;
		int prev = 0;
		int cur = 1;
		//长度为n的字符串，n+1个阶梯，第一个即cur=1，后边从1开始需要跳n次
		for (size_t i = 1; i <= s.size(); ++i)
		{
			if (s[i - 1] == '0')
				cur = 0;		      //不能单独解析，最近的跳板不能用
			if (i < 2 || !(s[i - 2] == '1' || //不能连着解析，前一跳板不能用
				(s[i - 2] == '2' && s[i - 1] <= '6')))
				prev = 0;
			int tmp = cur;
			cur = prev + cur;
			prev = tmp;
		}
		return cur;
    }
};

int main()
{
    Solution s1;
    string s = "1203";
    int result = s1.numDecodings(s);
    cout << result << endl;
    return 0;
}