#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 模拟
// time: O(n)
// space: O(1)
class Solution {
  public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        TreeNode *cur = root;
        while(cur) {
            if (val < cur->val) {
                if (cur->left) {
                    cur = cur->left;
                } else {
                    cur->left = new TreeNode(val);
                    break;
                }
            }
            else {
                if (cur->right) {
                    cur = cur->right;
                } else {
                    cur->right = new TreeNode(val);
                    break;
                }
            }
        }
        return root;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {4, 2, 7, 1, 3};
    TreeNode *root = constructTree(nums0);
    showTree(s.insertIntoBST(root, 5));
    return 0;
}