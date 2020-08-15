#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

// 哈希表 - 双向映射编码
// time: O(n)
// space: O(n)
class Solution {
  public:
    bool wordPattern(string pattern, string str) {
        int i = 0, cur = 0, pre = 0;
        unordered_map<char, string> iumaps;
        unordered_map<string, char> iumapc;
        str += " ";
        for (i = 0; i < pattern.size(); ++i) {
            while (pre < str.size() && str[pre] != ' ')     // 找单词
                pre++;
            if (pre == cur) // 单个空格分隔, 表示单词已解析完成
                break;
            string word = str.substr(cur, pre - cur);
            pre++;
            cur = pre;
            if (!iumaps.count(pattern[i]) && !iumapc.count(word)) { // 双向映射
                iumaps[pattern[i]] = word;
                iumapc[word] = pattern[i];
            }
            else if (iumaps[pattern[i]] != word || iumapc[word] != pattern[i]) // 不合法
                return false;
        }
        return pre == str.size() && i == pattern.size();    // 完成了双向映射, 单词和字符均解析完成
    }
};

int main() {
    Solution s;
    string pattern0 = "abba";
    string pattern1 = "abba";
    string pattern2 = "aaaa";
    string pattern3 = "abba";
    string pattern4 = "abba";
    string pattern5 = "aaa";
    string pattern6 = "jquery";
    string str0 = "dog cat cat dog";
    string str1 = "dog cat cat fish";
    string str2 = "dog cat cat dog";
    string str3 = "dog dog dog dog";
    string str4 = "    ";
    string str5 = "aa aa aa aa";
    string str6 = "jquery";
    cout << s.wordPattern(pattern0, str0) << endl;  // 1
    cout << s.wordPattern(pattern1, str1) << endl;  // 0
    cout << s.wordPattern(pattern2, str2) << endl;  // 0
    cout << s.wordPattern(pattern3, str3) << endl;  // 0
    cout << s.wordPattern(pattern4, str4) << endl;  // 0
    cout << s.wordPattern(pattern5, str5) << endl;  // 0
    cout << s.wordPattern(pattern6, str6) << endl;  // 0
    return 0;
};