#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

class Solution {
  public:
    vector<int> sumEvenAfterQueries(vector<int> &A, vector<vector<int>>& queries) {
        vector<int> ans(queries.size(), 0);
        int i = 0, sum = 0;
        for (auto &x : A)
            if (x % 2 == 0)
                sum += x;
        for (auto &x : queries) {
            if (A[x[1]] % 2 == 0) sum -= A[x[1]]; // 原始数据为偶数,更新
            A[x[1]] += x[0];
            if (A[x[1]] % 2 == 0) sum += A[x[1]];
            ans[i++] = sum;
        }
        return ans;
    }
};


int main() {
    Solution s;
    vector<int> A = {1, 2, 3, 4};
    vector<vector<int>> queries = {{1, 0}, {-3, 1}, {-4, 0}, {2, 3}};
    show1DVector(s.sumEvenAfterQueries(A, queries));
    return 1;
}