#include <stack>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//栈压入下标更有意义，因为入栈只能是'('
class Solution
{
  public:
    int longestValidParentheses(const string s)
    {
		int tempMax = 0;
		int last = -1;  //下一个的可能匹配开始点	// the position of the last ')'
		stack<int> sS1; // keep track of the positions of non-matching '('s
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == '(')
				sS1.push(i);
			else //s[i]==')'
			{
				if (sS1.empty()) //栈为空再来一个)，绝对无法匹配，更新匹配点	// no matching left
					last = i;
				else // find a matching pair
				{
					sS1.pop();
					if (sS1.empty()) //栈空，与之前有联系。用到匹配点。"()(())"
						tempMax = tempMax > i - last ? tempMax : i - last;
					else //栈不空，与之前无联系。用到栈顶。"()())" "(()())"
						tempMax = tempMax > i - sS1.top() ? tempMax : i - sS1.top();
				}
			}
		}
		return tempMax;
    }
};

class Solution1
{
  public:
    int longestValidParentheses(const string &s)
    {
		vector<int> f(s.size(), 0); //记录i位置的匹配长度
		int ret = 0;
		for (int i = s.size() - 2; i >= 0; --i)
		{
			int match = i + f[i + 1] + 1; //i位置可能的匹配位置
			// case: "((...))"
			if (s[i] == '(' && match < s.size() && s[match] == ')')
			{
				f[i] = f[i + 1] + 2; //正确匹配
				// if a valid sequence exist afterwards "((...))()"
				if (match + 1 < s.size())
					f[i] += f[match + 1]; //与之前有联系，更新匹配数
			}
			ret = max(ret, f[i]);
		}
		return ret;
    }
};

int main()
{
    string stringIn = "()(())(()";
    Solution s1;
    cout << s1.longestValidParentheses(stringIn) << endl;
    return 0;
}