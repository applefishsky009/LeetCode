#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// DP
// f(n) = max(f(n - 1), val + f(n - 2))
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    int rob(TreeNode *root) {
        vector<int> ans = robCache(root);
        return max(ans[0], ans[1]);
    }
  private:
    vector<int> robCache(TreeNode *root) {
        if (!root) return {0, 0};
        vector<int> ans(2, 0);
        vector<int> left = robCache(root->left);
        vector<int> right = robCache(root->right);
        ans[0] = max(left[1] + right[1], left[0] + right[0]);    // 不打劫当前节点, 打劫子节点 - 可能包含子节点或不包含子节点
        // ans[0] = max(left[0], left[1]) + max(right[0], right[1]);    // 打劫h + 1层
        ans[1] = max(root->val + left[0] + right[0], left[1] + right[1]);    // 打劫当前节点, 可能包含或不包含当前节点
        // ans[1] = root->val + left[0] + right[0]; // 打劫h + 2层
        return ans;
    }
};

// DP - 使用map节约重复搜索时间
// f(n) = max(f(n - 1), val + f(n - 2))
// time: O(n)
// space: O(n)
class Solution2 {
  public:
    unordered_map<TreeNode *, int> f, g;    // f-打劫h-2层, g-打劫h-1层
    void dfs(TreeNode *root) {
        if (!root) return;
        dfs(root->left);
        dfs(root->right);
        f[root] = root->val + g[root->left] + g[root->right];
        g[root] = max(f[root->left], g[root->left]) + max(f[root->right], g[root->right]);
    }
    int rob(TreeNode *root) {
        dfs(root);
        return max(f[root], g[root]);
    }
};

// DP - 结构体比vector更快
// f(n) = max(f(n - 1), val + f(n - 2))
// time: O(n)
// space: O(n)
class Solution {
  public:
    int rob(TreeNode *root) {
        auto rootStatus = dfs(root);
        return max(rootStatus.selected, rootStatus.notSelected);
    }
  private:
    struct SubtreeStatus {
        int selected;
        int notSelected;
    };
    SubtreeStatus dfs(TreeNode *root) {
        if (!root) return {0, 0};
        auto l = dfs(root->left);
        auto r = dfs(root->right);
        int selected = root->val + l.notSelected + r.notSelected;
        int notSelected = max(l.selected, l.notSelected) + max(r.selected, r.notSelected);
        return {selected, notSelected};
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 2, 3, INT_MIN, 3, INT_MIN, 1};
    vector<int> nums1 = {3, 4, 5, 1, 3, INT_MIN, 1};
    vector<int> nums2 = {4, 1, INT_MIN, 2, INT_MIN, INT_MIN, INT_MIN, 3};
    vector<int> nums3 = {2, 1, 3, INT_MIN, 4};
    TreeNode *root0 = constructTree(nums0);
    TreeNode *root1 = constructTree(nums1);
    TreeNode *root2 = constructTree(nums2);
    TreeNode *root3 = constructTree(nums3);
    cout << s.rob(root0) << endl;   // 7
    cout << s.rob(root1) << endl;   // 9
    cout << s.rob(root2) << endl;   // 7
    cout << s.rob(root3) << endl;   // 7
    return 0;
}
