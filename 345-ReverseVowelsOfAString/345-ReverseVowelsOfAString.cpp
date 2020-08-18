#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// TP
// time: O(n)
// time: O(1)
class Solution {
  public:
    string reverseVowels(string s) {
        int l = 0; int r = s.size() - 1;
        unordered_set<char> iset{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        while (l < r) {
            while (l < r && iset.count(s[l]) == 0) l++;
            while (l < r && iset.count(s[r]) == 0) r--;
            swap(s[l++], s[r--]);
        }
        return s;
    }
};

int main() {
    Solution s;
    // string s0 = "hello";
    string s0 = "";
    cout << s0 << endl;
    cout << s.reverseVowels(s0) << endl;
    return 0;
}