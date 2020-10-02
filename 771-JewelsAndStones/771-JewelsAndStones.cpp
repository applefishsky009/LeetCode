#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Hash
// time: O(n + m)
// space: O(1)
class Solution {
  public:
    int numJewelsInStones(string J, string S) {
        int ans = 0;
        vector<int> lowc(26, INT_MIN);
        vector<int> larc(26, INT_MIN);
        for (auto &x : J)
            if (x >= 'a' && x <= 'z')
                lowc[x - 'a'] = 0;
            else if (x >= 'A' && x<= 'Z')
                larc[x - 'A'] = 0;
        for (auto &x : S)
            if (x >= 'a' && x <= 'z' && lowc[x - 'a'] == 0)
                ++ans;
            else if (x >= 'A' && x<= 'Z' && larc[x - 'A'] == 0)
                ++ans;
        return ans;
    }
};

int main() {
    Solution s;
    // string J = "aA";
    // string S = "aAAbbbb";
    string J = "z";
    string S = "ZZ";
    cout << s.numJewelsInStones(J, S) << endl;
    return 0;
}