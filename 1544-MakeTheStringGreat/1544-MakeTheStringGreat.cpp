#include <stack>
#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// stack
// time: O(n)
// space: O(n)
class Solution {
  public:
    string makeGood(string s) {
        int i = 0;
        string ans;
        for (i = 0; i < s.size(); ++i) {
            if ((!ans.empty()) && 
                ((islower(s[i]) && isupper(ans.back()) && s[i] == tolower(ans.back())) || 
                 (isupper(s[i]) && islower(ans.back()) && s[i] == toupper(ans.back())))) {
                ans.pop_back();
            } else {
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};

int main() {
    Solution s1;
    string s = "leEeetcode";
    cout << s1.makeGood(s) << endl;
    return 0;
}