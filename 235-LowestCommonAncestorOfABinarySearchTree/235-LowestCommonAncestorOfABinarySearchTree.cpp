#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 递归
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        else if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        else
            return root;
    }  
};

// 迭代
// time: O(n)
// space: O(1)
class Solution {
  public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        while (root) {
            if (p->val > root->val && q->val > root->val)
                root = root->right;
            else if (p->val < root->val && q->val < root->val)
                root = root->left;
            else
                return root;
        }
        return nullptr;
    }  
};

int main() {
    Solution s;
    TreeNode *root = constructTree(vector<int>{6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5});
    // TreeNode *p = root->left;
    // TreeNode *q = root->right;
    TreeNode *p = root->left->left;
    TreeNode *q = root->left->right;
    TreeNode *ans = s.lowestCommonAncestor(root, p, q);
    return 0;
}