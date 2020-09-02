#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// part
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    bool isNumber(string s) {
        int l = 0, r = s.size() - 1;
        stripNumber(s, l, r);
        if (l > r || s.empty()) return false;   // strip()功能和空串判断
        return (s[l] == '+' || s[l] == '-') ? isNumber(s, l + 1, r) : isNumber(s, l, r);    // 先去除符号位
    }
  private:
    void stripNumber(string s, int &l, int &r) {
        while (l < s.size() && s[l] == ' ') ++l;
        while (r >= 0 && s[r] == ' ') --r;
    }
    bool isNumber(string s, int start, int end) {
        size_t pos = min(s.find_first_of('e'), s.find_first_of('E'));   // 是否找到e, 然后分别判断
        return pos < end ? isPrePartNumber(s, start, pos - 1) && isLastPartNumber(s, pos + 1, end) : isPrePartNumber(s, start, end);
    }
    bool isPrePartNumber(string &s, int start, int end) {  // e之前的数字合理性判断, 小数点在首位末尾都合理
        if (start > end) return false;
        int cnt = 0;
        for (int i = start; i <= end; ++i)
            if ((s[i] == '.' && ++cnt > 1) || (s[i] != '.' && !isdigit(s[i])))
                return false;
        return !(end - start + 1 == cnt);
    }
    bool isLastPartNumber(string &s, int start, int end) {  // e前后复用的判断
        if (start < s.size() && (s[start] == '-' || s[start] == '+')) ++start;   // 跳过第一个符号位
        if (start > end) return false;
        for (int i = start; i <= end; ++i)
            if (!isdigit(s[i]))
                return false;
        return true;
    }
};

// 确定有限状态自动机
// time: O(n)
// space: O(1)
class Solution {
  public:
    bool isNumber(string s) {
        unordered_map<State, unordered_map<CharType, State>> itransfer { // 所有合法状态下一个遇到的字符以及对应的可转移状态
            {
                STATE_INITIAL, {
                    {CHAR_SPACE, STATE_INITIAL},
                    {CHAR_NUMBER, STATE_INTERGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                    {CHAR_SIGN, STATE_INT_SIGN},
                }
            }, {
                STATE_INT_SIGN, {
                    {CHAR_NUMBER, STATE_INTERGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                }
            }, {
                STATE_INTERGER, {
                    {CHAR_NUMBER, STATE_INTERGER},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_POINT, STATE_POINT},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_POINT, {
                    {CHAR_NUMBER, STATE_FRACTION}, 
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_POINT_WITHOUT_INT, {
                    {CHAR_NUMBER, STATE_FRACTION}
                }
            }, {
                STATE_FRACTION, {
                    {CHAR_NUMBER, STATE_FRACTION}, 
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_EXP, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SIGN, STATE_EXP_SIGN},
                }
            }, {
                STATE_EXP_SIGN, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                }
            }, {
                STATE_EXP_NUMBER, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_END, {
                    {CHAR_SPACE, STATE_END},
                }
            }
        };
        int len = s.size();
        State ist = STATE_INITIAL;  // 起始转移状态
        for (int i = 0; i < len; ++i) {
            CharType cur_type = toCharType(s[i]);
            if (itransfer[ist].find(cur_type) == itransfer[ist].end())  // 当前转移状态没有对应字符的转移状态
                return false;
            ist = itransfer[ist][cur_type]; // 状态转移
        }
        return ist == STATE_INTERGER || ist == STATE_POINT || ist == STATE_FRACTION // 合法的结束状态
                || ist == STATE_EXP_NUMBER || ist == STATE_END;
    }
  private:
    enum State {
        STATE_INITIAL,  // 起始状态
        STATE_INT_SIGN,
        STATE_INTERGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION, // 小数
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END,  // 结束状态
    };
    enum CharType {
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_SPACE,
        CHAR_ILLEGAL,   // 非法字符
    };
    CharType toCharType(char ch) {
        if (ch >= '0' && ch <= '9') return CHAR_NUMBER;
        else if (ch == 'e' || ch == 'E') return CHAR_EXP;
        else if (ch == '.') return CHAR_POINT;
        else if (ch == '+' || ch == '-') return CHAR_SIGN;
        else if (ch == ' ') return CHAR_SPACE;
        else return CHAR_ILLEGAL;
    }
};

int main() {
    Solution s;
    cout << s.isNumber("+100") << endl; // 1
    cout << s.isNumber("5e2") << endl;  // 1
    cout << s.isNumber("-123") << endl; // 1
    cout << s.isNumber("3.1416") << endl;   // 1
    cout << s.isNumber("-1E-16") << endl;   // 1
    cout << s.isNumber("0123") << endl; // 1
    cout << s.isNumber("11") << endl;  // 1
    cout << s.isNumber("3.") << endl;  // 1
    cout << s.isNumber(".1") << endl;  // 1
    cout << s.isNumber(".1e2") << endl;  // 1
    cout << s.isNumber("1 ") << endl;  // 1
    cout << "&&&&&&&&&&&&&&&&&&&" << endl;
    cout << s.isNumber(".") << endl;  // 0
    cout << s.isNumber("1e3.") << endl;  // 0
    cout << s.isNumber("1e.1") << endl;  // 0
    cout << s.isNumber("12e") << endl;  // 0
    cout << s.isNumber("1a3.14") << endl;   // 0
    cout << s.isNumber("1.2.3") << endl;    // 0
    cout << s.isNumber("+-5") << endl;  // 0
    cout << s.isNumber("12e+5.4") << endl;  // 0
    return 0;
};