#include <stack>
#include <vector>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

//1. stoi->string to int
//2. string::size_type
class Solution
{
  public:
    int evalRPN(vector<string> &tokens)
    {
		if (tokens.size() == 0)
			return 0;
		stack<int> s;
		for (int i = 0; i < tokens.size(); ++i)
		{
			int temp = operatorLoc(tokens[i]);
			if (temp == -1) //是数字
				s.push(stoi(tokens[i]));
			else
			{ //运算符
				int right = s.top();
				s.pop();
				int left = s.top();
				s.pop();
				int result = 0;
				if (temp == 0)
					result = left + right;
				else if (temp == 1)
					result = left - right;
				else if (temp == 2)
					result = left * right;
				else if (temp == 3)
					result = left / right;
				s.push(result);
			}
		}
		return s.top();
    }

  private:
    int operatorLoc(string &s)
    {
		const string operatorLab = "+-*/";
		string::size_type temp = operatorLab.find(s);
		if (temp == string::npos)
			return -1; //if (temp.size() == 1 && temp != string::npos) return temp;
		return temp;   //return -1;
    }
};

int main()
{
    Solution s1;
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    int result = s1.evalRPN(tokens);
    cout << result << endl;
    return 0;
}