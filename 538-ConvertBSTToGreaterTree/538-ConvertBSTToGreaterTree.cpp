#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// inorder
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    TreeNode* convertBST(TreeNode *root) {
        int sum = 0, idx = 0;
        vector<int> nums_inorder;
        inorder(root, nums_inorder);
        for (int i = nums_inorder.size() - 2; i >= 0; --i)
            nums_inorder[i] += nums_inorder[i + 1];
        inorder_sum(root, nums_inorder, idx);
        return root;
    }
  private:
    void inorder(TreeNode *root, vector<int> &nums_inorder) {
        if (!root) return;
        inorder(root->left, nums_inorder);
        nums_inorder.push_back(root->val);
        inorder(root->right, nums_inorder);
    }
    void inorder_sum(TreeNode *root, vector<int> &nums_inorder, int &idx) {
        if (!root) return;
        inorder_sum(root->left, nums_inorder, idx);
        root->val = nums_inorder[idx++];
        inorder_sum(root->right, nums_inorder, idx);
    }
};

// 反序中序遍历
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    TreeNode* convertBST(TreeNode *root) {
        int sum = 0;
        return convertBST(root, sum);
    }
  private:
    TreeNode* convertBST(TreeNode *root, int &sum) {
        if (root) {
            convertBST(root->right, sum);
            sum += root->val;
            root->val = sum;
            convertBST(root->left, sum);
        }
        return root;
    }
};

// Morris
// time: O(n)
// space: O(n)
class Solution {
  public:
    TreeNode* convertBST(TreeNode *root) {
        int sum = 0;
        TreeNode *node = root;
        while (node) {
            if (node->right) {
                TreeNode *successor = node->right;
                while (successor->left && successor->left != node)  // 找前驱
                    successor = successor->left;
                if (!successor->left) { // 还没有进行后序中序遍历
                    successor->left = node;
                    node = node->right; // 后序中序遍历
                } else {    // 已经完成了后序中序遍历
                    successor->left = nullptr;
                    sum += node->val;
                    node->val = sum;
                    node = node->left;  // 后续中序遍历
                }
            } else {
                sum += node->val;
                node->val = sum;
                node = node->left;  // 后续中序遍历
            }
        }
        return root;
    }
};

int main() {
    Solution s;
    vector<int> nums = {5, 2, 13};
    TreeNode *root = constructTree(nums);
    showTree(s.convertBST(root));
    return 0;
}