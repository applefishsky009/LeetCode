#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
  public:
    string longestCommonPrefix(vector<string>& strs) {
        int len = strs.size(), i = 0, j = 0;
        if (strs.empty())
            return "";
        int sublen = strs[0].size();
        string ans = "";
        for (j = 0; j < sublen; j++) {
            char tmp = strs[0][j];
            int flag = 1;
            for (i = 1; i < len; i++) {
                if (j < strs[i].size() && tmp == strs[i][j]) ;
                else {flag = 0; break;}
            }
            if (flag) ans.push_back(tmp);
            else break;
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<string> strs1 = {"flower", "flow", "flight"};
    vector<string> strs2 = {"dog", "racecar", "car"};
    cout << s.longestCommonPrefix(strs1) << endl;
    cout << s.longestCommonPrefix(strs2) << endl;
    return 1;
}