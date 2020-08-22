#include <vector>
#include <string>
#include <iostream>
using namespace std;

// HT
// time: O(n)
// space: O(s)
class Solution {
  public:
    int longestPalindrome(string s) {
        int ans = 0;
        vector<int> char_map(52, 0);
        for (auto &c : s)
            if ((c >= 'A' && c <= 'Z' && ++char_map[c - 'A' + 26] % 2 == 0) ||
                (c >= 'a' && c <= 'z' && ++char_map[c - 'a'] % 2 == 0))
                ans += 2;
        for (auto &k : char_map) {
            if (k % 2 == 1) {
                ans += 1;
                break;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    string str0 = "abccccdd";
    string str1 = "AAAAAA";
    cout << s.longestPalindrome(str0) << endl;
    cout << s.longestPalindrome(str1) << endl;
    return 0;
}