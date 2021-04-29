#include <stack>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// stack
// time: O(n)
// space: O(1)
class Solution {
  public:
    int minOperations(vector<string> &logs) {
        int i = 0, ans = 0;
        for (i = 0; i < logs.size(); ++i) {
            if (logs[i] == "../" && ans != 0) {
                ans--;
            } else if (logs[i] == "./" || logs[i] == "../") {
                continue;
            } else {
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution s1;
    vector<string> logs = {"d1/","d2/","../","d21/","./"};
    cout << s1.minOperations(logs) << endl;
    return 0;
}