#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 高度通过参数传递 - 自顶向下的递归带cache
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    bool isBalanced(TreeNode *root) {
        int h = 0;
        return isBalanced(root, h);
    }
  private:
    bool isBalanced(TreeNode *root, int &height) {
        if (!root) {
            height = 0;
            return true;
        };
        int l = 0, r = 0;
        bool ll = isBalanced(root->left, l), rr = isBalanced(root->right, r);
        height = max(l, r) + 1;
        return ll && rr && abs(l - r) < 2;
    }
};

// 自顶向下的递归 - 不带cache
// time: O(n^2)
// space: O(n)
class Solution1 {
  public:
    bool isBalanced(TreeNode *root) {
        return root ? abs(treeHeight(root->left) - treeHeight(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right) : true;
        // if (!root)
            // return true; // 空节点是平衡树
        // else
            // return abs(treeHeight(root->left) - treeHeight(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right); // 但这里的高度重复计算了
    }
  private:
    int treeHeight(TreeNode *root) {
        return root ? max(treeHeight(root->left), treeHeight(root->right)) + 1 : 0;
        // if (!root)
        //     return 0;
        // else
        //     return max(treeHeight(root->left), treeHeight(root->right)) + 1;
    }
};

// 自底向上的递归 - 带高度 - 非平衡高度置0
// time: O(n)
// space: O(n)
class Solution {
  public:
    bool isBalanced(TreeNode *root) {
        return treeHeight(root) >= 0;
    }
  private:
    int treeHeight(TreeNode *root) {
        if (!root) return 0;
        int l = treeHeight(root->left);
        int r = treeHeight(root->right);
        if (l == -1 || r == -1 || abs(l - r) > 1) return -1;    // 非平衡
        else return max(l, r) + 1;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
    TreeNode *root = constructTree(nums0);
    showTree(root);
    cout << s.isBalanced(root) << endl;
    return 0;
}