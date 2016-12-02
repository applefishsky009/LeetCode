#include <stack>
#include <string>
#include <iostream>
using namespace std;

//A by leetcode
class Solution
{
  public:
    bool isValid(string s)
    {
		int i = 0;
		stack<char> sS1;
		while (s[i])
		{
			if (s[i] != '(' && s[i] != '{' && s[i] != '[' && s[i] != ')' && s[i] != '}' && s[i] != ']')
				return false; //不是括号
			if (sS1.empty() && (s[i] == '}' || s[i] == ']' || s[i] == ')'))
				return false; //没有匹配项
			if (s[i] == '(' || s[i] == '{' || s[i] == '[')
				sS1.push(s[i]);
			else if (s[i] - sS1.top() != 1 && s[i] - sS1.top() != 2) //'('=40,')'=41;'['=91,']'=93;'{'=123,'}'=125;
				return false;					     //不匹配
			else if (s[i] - sS1.top() == 1 || s[i] - sS1.top() == 2)
				sS1.pop();
			i++;
		}
		if (sS1.empty())
			return true;
		return false;
    }
};

int main()
{
    string stringIn = "([)]"; //"(()[)]{[()]}";
    Solution s1;
    cout << stringIn << endl;
    cout << s1.isValid(stringIn) << endl;
    return 0;
}