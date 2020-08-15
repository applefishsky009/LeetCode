#include <vector>
#include <iostream>
using namespace std;

// 1-3是必胜态, 则4是必输态, 5-7可以转移到4让对手处于必输态, 即自己是必胜态, 那么只有4的倍数是必输态, 4的倍数返回0
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool canWinNim(int n) {
        // return !(n % 4 == 0);
        // return (n % 4 != 0);
        return n % 4;
    }
};

// dp idp[i - 1] idp[i - 2] idp[i - 3]有一个必输态0, 转移使对手处于这个状态就能赢1. 否则自己处于必输态.
// f(i) = any(f(i - 1), f(i - 2), f(i - 3)) == 0; 但超时了
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    bool canWinNim(int n) {
        if (n < 4) return 1;
        vector<bool> idp(n + 1, 0);
        idp[1] = 1;
        idp[2] = 1;
        idp[3] = 1;
        for (int i = 4; i <= n; ++i)
            // idp[i] = (!idp[i - 1] || !idp[i - 2] || !idp[i - 3]);
            idp[i] = (idp[i - 1] == 0 || idp[i - 2] == 0 || idp[i - 3] == 0);
        return idp[n];
    }
};

int main() {
    Solution s;
    cout << s.canWinNim(4) << endl;
    cout << s.canWinNim(5) << endl;
    cout << s.canWinNim(6) << endl;
    cout << s.canWinNim(7) << endl;
    cout << s.canWinNim(8) << endl;
    cout << s.canWinNim(9) << endl;
    cout << s.canWinNim(10) << endl;
    cout << s.canWinNim(11) << endl;
    return 0;
}