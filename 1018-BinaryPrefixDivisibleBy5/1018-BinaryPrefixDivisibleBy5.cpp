#include <vector>
#include <iostream>
#include <D:/GitHub/RylModule/vector.h>
using namespace std;

// 因式分解, 保留余数部分即可
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        vector<bool> ans;
        int i = 0, prefix = 0;
        for (i = 0; i < A.size(); ++i) {
            prefix = ((prefix << 1) + A[i]) % 5;
            ans.emplace_back(prefix == 0);
        }
        return ans;
    }
};

int main() {
    Solution s1;
    // vector<int> A = {0, 1, 1};   // 100
    // vector<int> A = {1, 1, 1};   // 000
    // vector<int> A = {0, 1, 1, 1, 1, 1}; // 100010
    // vector<int> A = {1, 1, 1, 0, 1};    // 00000
    vector<int> A = {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0};  // 0000010001001000011
    show1DVector(s1.prefixesDivBy5(A));
    return 0;
}