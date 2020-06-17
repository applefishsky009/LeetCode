#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// A[i] + A[j] + i - j拆分为A[i] + i和A[j] - j,然后维护边界
class Solution {
  public:
    int maxScoreSightseeingPair(vector<int> &A) {
        int j = 0, ans = 0, mx = A[0] + 0;
        for (j = 1; j < A.size(); j++) {
            ans = max(ans, mx + A[j] - j);
            mx = max(mx, A[j] + j); // 边界维护
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> A = {8, 1, 5, 2, 6};
    cout << s.maxScoreSightseeingPair(A) << endl;
    return 1;
}