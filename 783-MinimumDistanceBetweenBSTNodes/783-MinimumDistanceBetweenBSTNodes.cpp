#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 中序带缓存遍历
// time: O(n)
// space: O(h)
class Solution {
  public:
    int minDiffInBST(TreeNode *root) {
        int pre = INT_MIN, diff = INT_MAX;
        minDiffInBST(root, pre, diff);
        return diff;
    }
  private:
    void minDiffInBST(TreeNode *root, int &pre, int &diff) {
        if (!root) return;
        minDiffInBST(root->left, pre, diff);
        if (pre != INT_MIN)
            diff = min(diff, root->val - pre);
        pre = root->val;
        minDiffInBST(root->right, pre, diff);
    }
};

int main() {
    Solution s;
    // TreeNode *root = constructTree(vector<int> {4, 2, 6, 1, 3});
    TreeNode *root = constructTree(vector<int> {1, INT_MIN, 3, INT_MIN, INT_MIN, 2});
    showTree(root);
    cout << s.minDiffInBST(root) << endl;
    return 0;
}