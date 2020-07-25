#include <vector>
#include <iostream>
#include <algorithm>
#include <D:\Github\RylModule\tree.h>
using namespace std;

// 中序带缓存遍历 - same as 783
// time: O(n)
// space: O(h)
class Solution1 {
  public:
    int getMinimumDifference(TreeNode *root) {
        int pre = INT_MIN, diff = INT_MAX;
        getMinimumDifference(root, pre, diff);
        return diff;
    }
  private:
    void getMinimumDifference(TreeNode *root, int &pre, int &diff) {
        if (!root) return;
        getMinimumDifference(root->left, pre, diff);
        if (pre != INT_MIN)
            diff = min(diff, root->val - pre);
        pre = root->val;
        getMinimumDifference(root->right, pre, diff);
    }
};

// Morris 中序遍历
// time: O(n)
// space: O(1)
class Solution {
  public:
    int getMinimumDifference(TreeNode *root) {
        TreeNode *cur = root, *pre = nullptr, *preceesor = nullptr;
        int diff = INT_MAX;
        while (cur) {
            if (!cur->left) { // 左子树为空, 没有前驱, 直接进入右子树
                if (pre) diff = min(diff, cur->val - pre->val); // custom
                pre = cur;  // custom
                // cout << cur->val << endl;
                cur = cur->right;
            } else {    // 进入左子树, 找到cur的前驱节点
                preceesor = cur->left;
                while (preceesor->right && preceesor->right != cur) // 找前驱
                    preceesor = preceesor->right;
                if (preceesor->right == cur) {  // 前驱已经指向自己了,说明左子树遍历完成, 进入右子树
                    if (pre) diff = min(diff, cur->val - pre->val); // custom
                    pre = cur;  // custom
                    // cout << cur->val << endl;
                    cur = cur->right;
                    preceesor->right = nullptr;
                } else { // 前驱还没有指向自己, 让前驱指向自己, 进入左子树
                    preceesor->right = cur;
                    cur = cur->left;
                }
            }
        }
        return diff;
    }
};

int main() {
    Solution s;
    TreeNode *root1 = constructTree(vector<int> {4, 2, 6, 1, 3});
    TreeNode *root2 = constructTree(vector<int> {1, INT_MIN, 3, INT_MIN, INT_MIN, 2});
    // showTree(root);
    cout << s.getMinimumDifference(root1) << endl;
    cout << s.getMinimumDifference(root2) << endl;
    return 0;
}