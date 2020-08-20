#include <iostream>
#include <unordered_map>
using namespace std;

// HT
// time: O(m + n)
// space: O(1)
class Solution {
  public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<int, int> imap;   // 只包含小写字母可以用数组代替哈希
        for (auto &c : magazine) imap[c]++;
        for (auto &c : ransomNote)
            if (--imap[c] < 0)
                return false;
        return true;
    }
};

int main() {
    Solution s;
    cout << s.canConstruct("a", "b") << endl;
    cout << s.canConstruct("aa", "ab") << endl;
    cout << s.canConstruct("aa", "aab") << endl;
    return 0;
}