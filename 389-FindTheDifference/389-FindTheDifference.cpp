#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 将char视为数字, 利用异或找不同
// time: O(n + m)
// space: O(1)
class Solution {
  public:
    char findTheDifference(string s, string t) {
        char ans = 0;
        for (auto &c : s) ans ^= c;
        for (auto &c : t) ans ^= c;
        return ans;
    }
};

int main() {
    Solution s;
    string s1 = "abcd";
    string s2 = "abcde";
    cout << s.findTheDifference(s1, s2) << endl;
    return 0;
}