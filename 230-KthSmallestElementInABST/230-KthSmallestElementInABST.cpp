#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// DFS
// time: O(k)
// space: O(Height)
class Solution1 {
  public:
    int kthSmallest(TreeNode* root, int k) {
        int ans = 0;
        dfs(root, k, ans);
        return ans;
    }
  private:
    void dfs(TreeNode* root, int &k, int &ans) {
        if (!root || k == 0) return;
        dfs(root->left, k, ans);
        if (--k == 0)
            ans = root->val;
        dfs(root->right, k, ans);
    }
};

// Binary Search
// time: O(nlgn)
// space: O(Height)
class Solution {
  public:
    int kthSmallest(TreeNode* root, int k) {
        if (!root) return -1;
        int numOfLeftNodes = getNumOfNodes(root->left);
        // int numOfRightNodes = getNumOfNodes(root->right);
        if (numOfLeftNodes == k - 1)    // 刚好左子树有k-1个数
            return root->val;
        else if (numOfLeftNodes >= k) { // 搜索左子树
            return kthSmallest(root->left, k);
        } else {    // 搜索右子树 -1是去除当前节点个数
            return kthSmallest(root->right, k - numOfLeftNodes - 1);
        }
    }
  private:
    int getNumOfNodes(TreeNode *root) {
        if (!root) return 0;
        return getNumOfNodes(root->left) + getNumOfNodes(root->right) + 1;
    }
};

int main() {
    Solution s;
    TreeNode *root = constructTree(vector<int>() = {5, 3, 6, 2, 4});
    cout << s.kthSmallest(root, 3) << endl;
    return 0;
}