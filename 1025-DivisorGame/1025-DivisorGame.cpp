#include <vector>
#include <iostream>
using namespace std;

// dp[i]表示爱丽丝能不能赢
// time: O(n^2)
// space: O(n)
class Solution1 {
  public:
    bool divisorGame(int N) {
        vector<int> idp(N + 1, 0);  // idp[0]无效, idp[1]表示爱丽丝输
        for (int i = 2; i <= N; ++i)
            for (int j = 1; j < i; ++j)
                if (!idp[i] && i % j == 0 && idp[i - j] == 0)
                    idp[i] = 1;
        return idp[N];
    }
};

// N为奇数时爱丽丝必败, N为偶数时爱丽丝必胜, N = 1和N = 2时结论成立. N > 2 时, 假设N ≤ k时该结论成立, 则N = k + 1时：
// 如果k为偶数, 则k + 1为奇数, x是k + 1的因数, 只可能是奇数, 而奇数减去奇数等于偶数, 且k + 1 - x ≤ k, 故轮到Bob的时候都是偶数. 而根据我们的猜想假设N ≤ k的时候偶数的时候先手必胜, 故此时无论Alice拿走什么, Bob都会处于必胜态, 所以Alice处于必败态.
// 如果k为奇数, 则k + 1为偶数, x可以是奇数也可以是偶数, 若Alice减去一个奇数, 那么k + 1 - x是一个小于等于k的奇数, 此时Bob占有它, 处于必败态, 则Alice处于必胜态.
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool divisorGame(int N) {
        // return N % 2 == 0;
        return !(N & 1);
    }
};

int main() {
    Solution s;
    cout << s.divisorGame(2) << endl;
    cout << s.divisorGame(3) << endl;
    return 0;
}