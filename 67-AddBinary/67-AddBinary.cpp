#include <stack>
#include <string>
#include <iostream>
using namespace std;

//先计算最后一位借助栈反转
class Solution
{
  public:
    string addBinary(string a, string b)
    {

	int addBit = 0;
	string result = "";
	stack<char> s;
	int i = a.size() - 1;
	int j = b.size() - 1;
	while (i >= 0 || j >= 0)
	{
	    int tempa = i >= 0 ? a[i] - '0' : 0;
	    int tempb = j >= 0 ? b[j] - '0' : 0;
	    int ans = tempa + tempb + addBit;
	    if (ans == 0)
	    {
		addBit = 0;
		s.push('0');
	    }
	    else if (ans == 1)
	    {
		addBit = 0;
		s.push('1');
	    }
	    else if (ans == 2)
	    {
		addBit = 1;
		s.push('0');
	    }
	    else
	    {
		addBit = 1;
		s.push('1');
	    }
	    --i;
	    --j;
	}
	if (addBit == 1)
	    s.push('1');
	while (!s.empty())
	{
	    result.push_back(s.top());
	    s.pop();
	}
	return result;
    }
};

//string可以借用insert()头插
class Solution1
{
  public:
    string addBinary(string a, string b)
	{
		int addBit = 0;
		string result = "";
		int i = a.size() - 1;
		int j = b.size() - 1;
		while (i >= 0 || j >= 0)
		{
			int tempa = i >= 0 ? a[i] - '0' : 0;
			int tempb = j >= 0 ? b[j] - '0' : 0;
			int ans = tempa + tempb + addBit;
			if (ans == 0)
			{
				addBit = 0;
				result.insert(result.begin(), '0');
			}
			else if (ans == 1)
			{
				addBit = 0;
				result.insert(result.begin(), '1');
			}
			else if (ans == 2)
			{
				addBit = 1;
				result.insert(result.begin(), '0');
			}
			else
			{
				addBit = 1;
				result.insert(result.begin(), '1');
			}
			--i;
			--j;
		}
		if (addBit == 1)
			result.insert(result.begin(), '1');
		return result;
    }
};

int main()
{
    string a = "11";
    string b = "1";
    Solution1 s1;
    string result = s1.addBinary(a, b);
    cout << result << endl;
    return 0;
}