#include <cmath>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 暴力递归-没用到完全二叉树的性质
// time: O(n)
// space: O(h)
class Solution1 {
  public:
    int countNodes(TreeNode* root) {
        // if (!root) return 0;
        // return countNodes(root->left) + countNodes(root->right) + 1;
        return root ? countNodes(root->left) + countNodes(root->right) + 1 : 0;
    }
};

// 二分-搜索最后出现的叶子结点
// time: O(h^2)
// space: O(1)
class Solution2 {
  public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        int depth = computeDepth(root);
        if (depth == 0) return 1;
        int left = 0, right = pow(2, depth);
        while (left < right) {  // 分治的写法
            int mid = left + ((right - left) >> 1); // 左子树最后一个节点
            if (exists(root, depth, mid))   // 分治右子树
                left = mid + 1;
            else
                right = mid;    // 分治左子树
        }
        return left + pow(2, depth) - 1;
    }
  private:
    int computeDepth(TreeNode *root) {
        int depth = 0;
        while (root->left) {
            root = root->left;
            depth++;
        }
        return depth;
    }
    bool exists(TreeNode *root, int depth, int idx) {
        int left = 0, right = pow(2, depth) - 1;
        for (int i = 0; i < depth; i++) {
            int mid = left + ((right - left) >> 1); // mid是左子树最后一个节点
            if (idx <= mid) {   // 走向左子树
                root = root->left;
                right = mid;
            }
            else {  // 走向右子树
                left = mid + 1;
                root = root->right;
            }
        }
        return root != nullptr;
    }
};

// 二分-搜索最后出现的叶子结点-指数优化
// time: O(h^2)
// space: O(1)
class Solution {
  public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        int depth = computeDepth(root);
        if (depth == 0) return 1;
        int record = pow(2, depth);
        int left = 0, right = record;
        while (left < right) {  // 分治的写法
            int mid = left + ((right - left) >> 1); // 左子树最后一个节点
            if (exists(root, depth, mid, record))   // 分治右子树
                left = mid + 1;
            else
                right = mid;    // 分治左子树
        }
        return left + record - 1;
    }
  private:
    int computeDepth(TreeNode *root) {
        int depth = 0;
        while (root->left) {
            root = root->left;
            depth++;
        }
        return depth;
    }
    bool exists(TreeNode *root, int depth, int idx, int record) {
        int left = 0, right = record - 1;
        for (int i = 0; i < depth; i++) {
            int mid = left + ((right - left) >> 1); // mid是左子树最后一个节点
            if (idx <= mid) {   // 走向左子树
                root = root->left;
                right = mid;
            }
            else {  // 走向右子树
                left = mid + 1;
                root = root->right;
            }
        }
        return root != nullptr;
    }
};

int main() {
    Solution s;
    // TreeNode *root = constructTree(vector<int> {1, 2, 3, 4, 5, 6});
    TreeNode *root = constructTree(vector<int> {1, 2});
    showTree(root);
    cout << s.countNodes(root) << endl;
    return 0;
}