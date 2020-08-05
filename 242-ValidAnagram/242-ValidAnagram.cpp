#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Hash Table - 也可以排序后判断是否相等 - O(n*lgn)
// 进阶 - 使用哈希表而不是数组来进行判断, 使用数组的unicode大小很可能超过100W
// time: O(n)
// space: O(1)
class Solution {
  public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false; // 不等长返回false, 防止Hash Table错位
        vector<int> imap(26, 0);
        for (int i = 0; i < s.size(); ++i)
            ++imap[s[i] - 'a'];
        for (int i = 0; i < t.size(); ++i)
            if (--imap[t[i] - 'a'] < 0)
                return false;
        return true;
    }
};

int main() {
    Solution s;
    string s1 = "anagram";
    string t1 = "nagaram";
    string s2 = "rat";
    string t2 = "car";
    cout << s.isAnagram(s1, t1) << endl;
    cout << s.isAnagram(s2, t2) << endl;
    return 0;
}