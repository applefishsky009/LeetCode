#include <string>
#include <cctype>
#include <iostream>
using namespace std;

//这种题看似简单，但是坑巨多无比
//完成' '的strip功能
//.1，01,2e10，3.(指数),-1.,1.e3,7e+6这种输入是合理的
//1.e,1e.,.e1,6e6.5这种输入非法

//可以用e将数字分为两部分，判断每部分是否为数字，右侧不能是小数。如下：
class Solution
{
  public:
    bool isNumber(string s)
    {
		//strip()
		size_t first = s.find_first_not_of(' ');
		size_t last = s.find_last_not_of(' ');
		if (first == string::npos)
			return false; //注意find_first_not_of返回值
		string sTemp(s, first, last - first + 1);

		size_t pivkey = sTemp.find_first_of('e');
		if (pivkey == string::npos)
			return isNumberD(sTemp);
		else
		{
			string s1(sTemp, 0, pivkey);
			string s2(sTemp, pivkey + 1);
			return (isNumberD(s1) && isNumberI(s2));
		}
    }

  private:
    bool isNumberD(string s1)
    {
		if (s1.size() == 0)
			return false;
		int pointFlag = false;
		//去掉+-号
		if ((s1[0] == '+' || s1[0] == '-') && (s1[1] != '+' || s1[1] != '-'))
		{
			string sTemp(s1, 1);
			return isNumberD(sTemp);
		}
		//判断是否合理的小数
		if (s1[0] == '.' && s1[1] == '\0')
			return false; //"."不合理
		for (int i = 0; i < s1.size(); ++i)
		{
			if (s1[i] == '.')
			{
				if (pointFlag)
					return false;
				pointFlag = true;
				continue;
			}
			if (!isdigit(s1[i]))
				return false;
		}
		return true;
    }
    bool isNumberI(string s2)
    {
		if (s2.size() == 0)
			return false;
		//去掉+-号
		if ((s2[0] == '+' || s2[0] == '-') && (s2[1] != '+' || s2[1] != '-'))
		{
			string sTemp(s2, 1);
			return isNumberI(sTemp);
		}
		//判断是否合理的整数
		for (int i = 0; i < s2.size(); ++i)
			if (!isdigit(s2[i]))
				return false;
		return true;
    }
};

//神一般的有限自动机
//http://blog.csdn.net/suwei19870312/article/details/12094233
class Solution1
{
  public:
    bool isNumber(const string &s)
    {
		enum InputType
		{
			INVALID,   // 0
			SPACE,     // 1
			SIGN,      // 2
			DIGIT,     // 3
			DOT,       // 4
			EXPONENT,  // 5
			NUM_INPUTS // 6
		};
		const int transitionTable[][NUM_INPUTS] = 
		{
			-1, 0, 3, 1, 2, -1,    // next states for state 0
			-1, 8, -1, 1, 4, 5,    // next states for state 1
			-1, -1, -1, 4, -1, -1, // next states for state 2
			-1, -1, -1, 1, 2, -1,  // next states for state 3
			-1, 8, -1, 4, -1, 5,   // next states for state 4
			-1, -1, 6, 7, -1, -1,  // next states for state 5
			-1, -1, -1, 7, -1, -1, // next states for state 6
			-1, 8, -1, 7, -1, -1,  // next states for state 7
			-1, 8, -1, -1, -1, -1, // next states for state 8
		};
		int state = 0;
		for (auto ch : s)
		{
			InputType inputType = INVALID;
			if (isspace(ch))
				inputType = SPACE;
			else if (ch == '+' || ch == '-')
				inputType = SIGN;
			else if (isdigit(ch))
				inputType = DIGIT;
			else if (ch == '.')
				inputType = DOT;
			else if (ch == 'e' || ch == 'E')
				inputType = EXPONENT;
			// Get next state from current state and input symbol
			state = transitionTable[state][inputType];
			// Invalid input
			if (state == -1)
				return false;
		}
		// If the current state belongs to one of the accepting (final) states,
		// then the number is valid
		return state == 1 || state == 4 || state == 7 || state == 8;
    }
};

int main()
{
    Solution s1;
    string s = "2e0";
    bool result = s1.isNumber(s);
	cout << result << endl;
    return 0;
}