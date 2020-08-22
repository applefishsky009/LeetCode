#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// dfs
// time: O(n)
// space: O(h)
class Solution {
  public:
    int sumOfLeftLeaves(TreeNode *root) {
        if (!root || (!root->left && !root->right)) return 0;   // 单独一个根节点并不算左叶子
        return sumOfLeftLeavesParent(root, nullptr);
    }
  private:
    int sumOfLeftLeavesParent(TreeNode *root, TreeNode *parent) {
        if (!root->left && !root->right && parent && parent->left == root) return root->val;    // 递归终止条件:返回左叶子的值
        int isum = 0;
        if (root->left) isum += sumOfLeftLeavesParent(root->left, root);
        if (root->right) isum += sumOfLeftLeavesParent(root->right, root);
        return isum;    // 递归搜索左右子树的左叶子, 没有就是isum = 0;
    }
};

int main() {
    Solution s;
    // vector<int> nums = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
    vector<int> nums = {1, INT_MIN, 2};
    TreeNode *root = constructTree(nums);
    cout << s.sumOfLeftLeaves(root) << endl;
    return 0;
}