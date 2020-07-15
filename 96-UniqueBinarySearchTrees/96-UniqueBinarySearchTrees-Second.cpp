#include <vector>
#include <iostream>
using namespace std;

// 分治 - BST的子树也是BST
// time: O(n^2)
// space: O(n)
class Solution1 {
  public:
    int numTrees(int n) {
        vector<int> idp(n + 1, 0); idp[0] = 1;
        for (int i = 1; i < n + 1; ++i)
            for (int j = 0; j < i; j++)
                idp[i] += idp[j] * idp[i - j - 1];
        return idp[n];
    }
};

// Math 卡塔兰数 Cn+1 = Cn*2(2n+1)/(n+2)
// time: O(n)
// space: O(1)
class Solution {
  public:
    int numTrees(int n) {
        long long C = 1;
        for (int i = 0; i < n; ++i)
            C = C * 2 * (2 * i + 1) / (i + 2);
        return C;
    }
};

int main() {
    Solution s;
    cout << s.numTrees(3) << endl;
    cout << s.numTrees(4) << endl;
    cout << s.numTrees(5) << endl;
    return 0;
}