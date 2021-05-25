#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// DP BitM
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<int> countBits(int n) {
        vector<int> bits(n + 1);
        for (int i = 1; i <= n; ++i) {
            bits[i] = bits[i & (i - 1)] + 1;    // i & (i + 1)可将最低位设置为0
            // bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }
};

int main() {
    Solution s;
    show1DVector(s.countBits(5));
    return 0;
}