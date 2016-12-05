#include <cctype>
#include <string> //然而真正对于 operator<<(std::ostream &, const std::string &) 的声明在头文件 string 中. 将 cout 对 string 的重载放在 string 这个头文件中是正确的设计. 这也是本文阐述的主旨.
#include <iostream>
//因此, 让上述代码工作, 仅需要加入#include< string> 头文件.
using namespace std;

//A by leetcode
class Solution
{
  public:
    bool isPalindrome(string s)
    {
		if (s.size() == 0)
			return true;
		int i = 0;
		int j = s.size() - 1;
		while (i < j)
		{
			while (i < s.size() && !isalnum(s[i])) //使用while是为了防止连续的不期望的字符
				i++;
			while (j >= 0 && !isalnum(s[j])) //访问s1[i]前要判断是否越界，如本题中",."的测试用例
				j--;
			if (isdigit(s[i]) && s[i] != s[j])
				return false;
			/*if (isalpha(s[i]) && (s[i] != s[j]) && (abs(s[i]-s1[j]) != abs('a'-'A')))*/
			if (isalpha(s[i]) && tolower(s[i]) != tolower(s[j]))
				return false;
			i++;
			j--;
		}
		return true;
    }
};

int main()
{
    Solution s1;
    string stringIn = ",."; //"A man,a plan,a canal:Panama";//"race a car";
    bool flag = s1.isPalindrome(stringIn);
    cout << flag << endl;
    return 0;
}
