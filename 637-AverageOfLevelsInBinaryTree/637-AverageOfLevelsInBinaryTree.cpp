#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// bfs
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    vector<double> averageOfLevels(TreeNode *root) {
        vector<double> ans;
        if (!root) return ans;
        queue<TreeNode *> iq;
        iq.emplace(root);
        double sum = 0, cnt = 0;    // 注意sum不要越界
        while (!iq.empty()) {
            sum = 0;
            cnt = iq.size();
            for (int i = 0; i < cnt; ++i) {
                TreeNode *cur = iq.front(); iq.pop();
                sum += cur->val;
                if (cur->left) iq.emplace(cur->left);
                if (cur->right) iq.emplace(cur->right);
            }
            ans.emplace_back(sum / cnt);
        }
        return ans;
    }
};

// dfs
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<double> averageOfLevels(TreeNode *root) {
        vector<int> counts;
        vector<double> sums;
        dfs(root, 0, counts, sums);
        vector<double> averages;
        for (int i = 0; i < sums.size(); ++i)
            averages.emplace_back(sums[i] / counts[i]);
        return averages;
    }
  private:
    void dfs(TreeNode *root, int level, vector<int> &counts, vector<double> &sums) {
        if (!root) return;
        if (level < sums.size()) {  // 标识是否进入下一层
            sums[level] += root->val;
            counts[level] += 1;
        } else {
            sums.emplace_back(1.0 * root->val);
            counts.emplace_back(1);
        }
        dfs(root->left, level + 1, counts, sums);
        dfs(root->right, level + 1, counts, sums);
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
    TreeNode *root = constructTree(nums0);
    show1DVector(s.averageOfLevels(root));
    return 0;
}