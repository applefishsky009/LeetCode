#include <queue>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// dfs
// time: O(min(n, m))
// space: O(1)  // 沒有新建空间
class Solution0 {
  public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
};

// bfs
// time: O(min(n, m))
// space: O(min(n, m))
class Solution {
  public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        TreeNode *merged = new TreeNode(t1->val + t2->val);
        queue<TreeNode*> q, queue1, queue2;
        q.push(merged); queue1.push(t1); queue2.push(t2);
        while (!queue1.empty() && !queue2.empty()) {
            auto node = q.front(), node1 = queue1.front(), node2 = queue2.front();
            q.pop(); queue1.pop(); queue2.pop();
            auto left1 = node1->left, right1 = node1->right, left2 = node2->left, right2 = node2->right;
            if (left1 || left2) {
                if (left1 && left2) {
                    auto left = new TreeNode(left1->val + left2->val);
                    node->left = left;
                    q.push(left); queue1.push(left1); queue2.push(left2);
                } else if (left1) {
                    node->left = left1; // 这里还是利用了原先的子树, 这种写法很不干净, 一部分节点是新建的, 一部分节点共享了原先的子树
                } else if (left2) {
                    node->left = left2; // 如果完全需要新建, 应该copy一个子树出来
                }
            }
            if (right1 || right2) {
                if (right1 && right2) {
                    auto right = new TreeNode(right1->val + right2->val);
                    node->right = right;
                    q.push(right); queue1.push(right1); queue2.push(right2);
                } else if (right1) {
                    node->right = right1;
                } else if (right2) {
                    node->right = right2;
                }
            }
        }
        return merged;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {1, 3, 2, 5};
    vector<int> nums1 = {2, 1, 3, INT_MIN, 4, INT_MIN, 7};
    TreeNode *t1 = constructTree(nums0);
    TreeNode *t2 = constructTree(nums1);
    showTree(s.mergeTrees(t1, t2));
    return 0;
}