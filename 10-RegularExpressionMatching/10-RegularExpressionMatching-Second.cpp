#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//.匹配任意字符
//*匹配0个或者多个前个字符 - 重点
//注意当前匹配条件*p == *s || (*p == '.' && *s != '\0')，'.'唯一不能匹配'\0'
class Solution1 {
  public:
    bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
    }
  private:
    bool isMatch(const char *s, const char *p) {
		if (*p == '\0')
			return *s == '\0';
		if (*(p + 1) != '*') { //没有'*'通配符，简单匹配
			if (*p == *s || (*p == '.' && *s != '\0'))	// 匹配
				return isMatch(s + 1, p + 1);
			else
				return false;
		}
		else {
			while (*p == *s || (*p == '.' && *s != '\0')) { //当前字符匹配，判断(可能0个)并往前走一步
				if (isMatch(s, p + 2))
					return true; //当前匹配
				++s;		 //当前位不匹配，尝试匹配0.1.2.3......个前字符
			}
			return isMatch(s, p + 2); //当前不匹配，跳过通配符
		}
    }
};

class Solution {
  public:
	bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
	}
  private:
	bool isMatch(const char *s, const char *p) {
		if (*p == '\0')
			return *s == '\0';
		if (*(p + 1) != '*') {
			if ((*p == *s) || (*p == '.' && *s != '\0'))
				return isMatch(s + 1, p + 1);
			else
				return false;
		} else {
			while((*p == *s) || (*p == '.' && *s != '\0')) {	// 当前位匹配,s偏移
				if (isMatch(s, p + 2))	// *可以是0个
					return true;
				++s;
			}
			return isMatch(s, p + 2);
		}
	}
};

int main()
{
    Solution s1;
    string s = "aab";
    string p = "a*a*b";
    cout << s1.isMatch(s, p) << endl;
    return 0;
}