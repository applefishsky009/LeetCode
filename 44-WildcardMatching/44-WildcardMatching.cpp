#include <string>
#include <iostream>
using namespace std;

//超时。。。和一样，正则匹配原理
class Solution
{
  public:
    bool isMatch(const string s, const string p)
    {
		return isCMatch(s.c_str(), p.c_str());
    }

  private:
    bool isCMatch(const char *s, const char *p)
    {
		if (*s == '\0' && *p == '\0')
			return true;
		if (*s == *p || *p == '?')
			return isCMatch(++s, ++p);
		if (*p == '*')
		{
			while (*p == '*')
				++p; //多个‘*’是无效的
			if (*p == '\0')
				return true;
			while (*(p + 1) != *s)
				++s;
			if (isCMatch(s, ++p))
				return true; //找下一个可能匹配的位置
			++s;
		}
		return false;
    }
};

//Two Pointers
class Solution1
{
  public:
    bool isMatch(const string &s, const string &p)
    {
		return isMatch(s.c_str(), p.c_str());
    }

  private:
    bool isMatch(const char *s, const char *p)
    {
		bool star = false;
		const char *str, *ptr; //str,ptr指针是pre指针，s,p指针是cur指针
		for (str = s, ptr = p; *str != '\0'; str++, ptr++)
		{
			switch (*ptr)
			{
			case '?': //下趟匹配
				break;
			case '*':
				star = true;
				s = str, p = ptr;
				while (*p == '*')
					p++; //skip continuous '*'
				if (*p == '\0')
					return true; //紧跟结束符任意匹配
				//更新字符串
				str = s - 1; //退回一格，抵消for中的自加
				ptr = p - 1;
				break;
			default:
				if (*str != *ptr)
				{ //当前不相等
					// 如果前面没有'*'匹配不成功
					if (!star)
						return false;
					//前面有'*'s++，下一个可能的位置
					s++;	 //字符串往前，这是重点
					str = s - 1; //指针更新(指回去)
					ptr = p - 1;
				}
				//else 即匹配成功，下趟匹配
			}
		}
		//s匹配完了
		while (*ptr == '*')
			ptr++;
		return (*ptr == '\0');
    }
};

int main()
{
    Solution1 s1;
    string s = "aacaaab";
    string p = "a*ab";
    cout << s1.isMatch(s, p) << endl;
    return 0;
}