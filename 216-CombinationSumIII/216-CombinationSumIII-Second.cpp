#include <array>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dfs 
// time: O(C_k_m * k)
// space : O(m)
class Solution0 {
  public:
    vector<vector<int>> combinationSum3(int k, int n) {
        array<int, 9> iarr;
        iarr.fill(1);
        for (int i = 1; i < iarr.size(); ++i) iarr[i] = i + 1;
        vector<vector<int>> ans;
        vector<int> path;
        if (n == 0 && k == 0) return ans;
        dfs(ans, path, k, n, iarr, 0);
        return ans;
    }
  private:
    void dfs(vector<vector<int>> &ans, vector<int> &path, int k, int n, array<int, 9> &iarr, int start) {
        if (k == 0 && n == 0) {
            ans.push_back(path);
            return;
        }
        if (k == 0 || n == 0) return;
        if (n > k * 9) return;  // 所需要的数字太大 不能满足
        for (int i = start; i < iarr.size(); ++i) { // bfs的思路
            if (iarr[i] > n) break; // 剪枝 所需要的数字太小 不能满足
            path.push_back(iarr[i]);
            dfs(ans, path, k - 1, n - iarr[i], iarr, i + 1);
            path.pop_back();
        }
    }
};

// dfs
// time: O(C_k_m * k)
// space : O(m)
class Solution1 {
  public:
    vector<vector<int>> combinationSum3(int k, int n) { // k是数字个数, n是sum
        vector<int> path;
        vector<vector<int>> ans;
        if (n == 0 || k == 0) return ans;
        dfs(ans, path, 1, 9, k, n);
        return ans;
    }
  private:
    void dfs(vector<vector<int>> &ans, vector<int> &path, int cur, int n, int k, int sum) { // cur是当前数字, n是上界
        if (path.size() + (n - cur + 1) < k || path.size() > k) return; // 剪枝  - 将剩下的所有数都填进去也不够k个 || 数量越界
        if (path.size() == k && accumulate(path.begin(), path.end(), 0) == sum) {
            ans.push_back(path);
            return;
        }
        path.push_back(cur);
        dfs(ans, path, cur + 1, n, k, sum);
        path.pop_back();
        dfs(ans, path, cur + 1, n, k, sum);
    }
};

// 二进制枚举
// time: O(m * 2^m)
// space : O(m)
class Solution {
  public:
    vector<vector<int>> combinationSum3(int k, int n) { // k是数字个数, n是sum
        vector<int> path;
        vector<vector<int>> ans;
        for (int mask = 0; mask < (1 << 9); ++mask) // 二进制枚举的标准写法
            if (check(path, mask, k, n))
                ans.emplace_back(path);
        return ans;
    }
  private:
    bool check(vector<int> &path, int mask, int k, int n) {   // 数当前数字的二进制位数
        path.clear();
        for (int i = 0; i < 9; ++i) // 位数
            if ((1 << i) & mask)
                path.push_back(i + 1);
        return path.size() == k && accumulate(path.begin(), path.end(), 0) == n;    // 满足要求
    }
};

int main() {
    Solution s;
    // show2DVector(s.combinationSum3(3, 7));
    // cout << ends << endl;
    // show2DVector(s.combinationSum3(3, 9));
    // cout << ends << endl;
    // show2DVector(s.combinationSum3(0, 0));
    // show2DVector(s.combinationSum3(0, 1));
    // show2DVector(s.combinationSum3(3, 100));
    return 0;
}