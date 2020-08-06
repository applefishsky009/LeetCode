#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// string_view: O(1)的时间“观测”字符串, 包括查询和遍历, 构造和sub_str
// 哈希表 + 中心扩展法枚举前缀后缀
// time: O(n * m^2)
// space: O(n * m^2)
class Solution {
  public:
    vector<vector<int>> palindromePairs(vector<string> &words) {
        const int n = words.size();
        vector<string> wordsRev;
        unordered_map<string, int> indices;   // string_view是C++17才引入的
        for (const string &word : words) {
            wordsRev.push_back(word);
            reverse(wordsRev.back().begin(), wordsRev.back().end());
        }
        for (int i = 0; i < n; ++i)
            indices.emplace(wordsRev[i], i);
        vector<vector<int>> ret;
        for (int i = 0; i < n; ++i) {
            int m = words[i].size();
            if (!m) continue; // 跳过空字符串
            string wordView(words[i]);    // string_view
            for (int j = 0; j <= m; ++j) {
                if (isPalindrome(wordView, j, m - 1)) { // 回文子串, 判断前缀是否在map中, 因为m=0已经处理掉了, 没有越界
                    int left_id = findWord(wordView, 0, j - 1, indices);
                    if (left_id != -1 && left_id != i)  // 在map中找到了且不是自己(自身是回文串) 
                        ret.push_back({i, left_id});
                }
                if (j && isPalindrome(wordView, 0, j - 1)) {    // 判断后缀是否在map中, j为越界保护
                    int right_id = findWord(wordView, j, m - 1, indices);
                    if (right_id != -1 && right_id != i)
                        ret.push_back({right_id, i});
                }
            }
        }
        return ret;
    }
  private:
    bool isPalindrome(const string &s, int left, int right) {   // string_view
        int len = right - left + 1;
        for (int i = 0; i < len / 2; ++i)
            if (s[left + i] != s[right - i])
                return false;
        return true;
    }
    int findWord(const string &s, int left, int right, unordered_map<string, int> &indices) {    // string_view
        auto iter = indices.find(s.substr(left, right - left + 1));
        return iter == indices.end() ? -1 : iter->second;
    }
};

int main() {
    Solution s;
    vector<string> words0 = {"abcd", "dcba", "lls", "s", "sssll"};
    vector<string> words1 = {"bat", "tab", "cat"};
    show2DVector(s.palindromePairs(words0));
    cout << endl;
    show2DVector(s.palindromePairs(words1));
    return 0;
}