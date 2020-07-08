#include <cmath>
#include <queue>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// DFS
// time: O(n)
// space: O(h)
class Solution1 {
  public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;    // 递归终止条件
        return (sum == root->val && !root->right && !root->left) ? true : (hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val));    // 递归进行条件
    }
};

// BFS
// time: O(n)
// space: O(n)
class Solution {
  public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;
        queue<TreeNode *> iq;
        queue<int> iq_val;
        iq.push(root);
        iq_val.push(root->val);
        while (!iq.empty()) {
            TreeNode *now = iq.front();iq.pop();
            int tmp = iq_val.front();iq_val.pop();
            if (!now->left && !now->right) {
                if (tmp == sum) return true;
                continue;
            }
            if (now->left) {
                iq.push(now->left);
                iq_val.push(now->left->val + tmp);
            }
            if (now->right) {
                iq.push(now->right);
                iq_val.push(now->right->val + tmp);
            }
        }
        return false;
    }
};

int main () {
    Solution s;
    TreeNode *root = constructTree(vector<int> {5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 1});
    showTree(root);
    cout << s.hasPathSum(root, 22) <<endl;
    cout << s.hasPathSum(root, 9) <<endl;
    return 0;
}