#include <string>
#include <iostream>
using namespace std;

// 原地计数
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    int countSegments(string s) {
        int word_len = 0, word_cnt = 0;
        for (auto &c : s) {
            if (c != ' ') ++word_len;
            else {
                word_cnt += word_len != 0;
                word_len = 0;
            }
        }
        return word_cnt + (word_len != 0);
    }
};

// 原地计数 - 空格+非空格的脉冲计数
// time: O(n)
// space: O(1)
class Solution {
  public:
    int countSegments(string s) {
        int segmentCount = 0;
        for (int i = 0; i < s.size(); ++i)
            if ((i == 0 || s[i - 1] == ' ') && s[i] != ' ') // 在遇见空格前就必然是一个单词, 遇见空格和字符的连续组合则进行新的计数
                ++segmentCount;
        return segmentCount;
    }
};

int main() {
    Solution s;
    string str0 = "Hello, my name is John"; // 5
    string str1 = "Hello";  // 1
    string str2 = "love live! mu'sic forever";  // 4
    string str3 = "";   // 0
    cout << s.countSegments(str0) << endl;
    cout << s.countSegments(str1) << endl;
    cout << s.countSegments(str2) << endl;
    cout << s.countSegments(str3) << endl;
    return 0;
}