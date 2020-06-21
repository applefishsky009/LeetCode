#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 这是一个二叉搜索树
class Solution1 {
  public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (!root) return nullptr;
        if (root->val == val) return root;
        TreeNode *l = searchBST(root->left, val);
        TreeNode *r = searchBST(root->right, val);
        if (l) return l;
        if (r) return r;
        return nullptr;
    }
};

// 二叉搜索树,递归
class Solution2 {
  public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (!root) return nullptr;
        if (root->val == val) return root;
        return root->val > val ? searchBST(root->left, val) : searchBST(root->right, val);
    }
};

// 二叉搜索树,迭代
class Solution {
  public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root && val != root->val)
            root = root->val > val ? root->left : root->right;
        return root;
    }
};

int main() {
    Solution s;
    TreeNode *root = constructTree(vector<int> () = {4, 2, 7, 1, 3});
    showTree(root);
    showTree(s.searchBST(root, 3));
    showTree(s.searchBST(root, 2));
    // showTree(s.searchBST(root, 5));
    return 1;
}