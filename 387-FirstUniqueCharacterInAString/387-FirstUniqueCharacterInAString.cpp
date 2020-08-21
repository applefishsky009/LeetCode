#include <vector>
#include <limits>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// HT
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    int firstUniqChar(string s) {
        vector<int> char_map(26, 0);
        for (auto &c : s)  ++char_map[c - 'a'];
        for (int i = 0; i < s.size(); ++i)
            if (char_map[s[i] - 'a'] == 1)
                return i;
        return -1;
    }
};

// HT记下标不计次数
// time: O(n)
// space: O(1)
class Solution {
  public:
    int firstUniqChar(string s) {
        vector<int> char_map(26, INT_MAX);
        for (int i = 0; i < s.size(); ++i)
            if (char_map[s[i] - 'a'] != INT_MAX)
                char_map[s[i] - 'a'] = -1;
            else
                char_map[s[i] - 'a'] = i;
        int min_index = INT_MAX;
        for (int i = 0; i < 26; ++i)
            if (char_map[i] != -1)
                min_index = min(min_index, char_map[i]);
        return min_index == INT_MAX ? -1 : min_index;
    }
};

int main() {
    Solution s;
    string str = "leetcode";
    cout << s.firstUniqChar(str) << endl;
    return 0;
}