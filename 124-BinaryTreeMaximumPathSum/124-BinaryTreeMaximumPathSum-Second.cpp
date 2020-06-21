#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

class Solution {
  public:
    int maxPathSum(TreeNode* root) {
        int path_dis = 0;
        return dfs(root, path_dis);
    }
  private:
    int dfs(TreeNode* root, int &path_dis) {    // path_dis为根节点在路径中的最大路径,返回值为根节点不在路径中的最大路径+根节点在路径中的最大路径
        int path_dis_l = 0, path_dis_r = 0;
        int l = root->left ? dfs(root->left, path_dis_l) : INT_MIN;
        int r = root->right ? dfs(root->right, path_dis_r) : INT_MIN;
        path_dis = max(max(path_dis_l + root->val, path_dis_r + root->val), root->val);  // 包含根节点路径的最大路径
        return max(max(max(path_dis_l + root->val + path_dis_r, l), r), path_dis);  // 最大路径的子树，不包含根节点路径+包含根节点路径
    }
};

int main() {
    Solution s;
    TreeNode *root0 = constructTree(vector<int> () = {-10, 9, 20, -1, -1, 15, 7});  // 42
    TreeNode *root1 = constructTree(vector<int> () = {1, 2, 3});    // 6
    TreeNode *root2 = constructTree(vector<int> () = {-3}); // -3
    TreeNode *root3 = constructTree(vector<int> () = {-3, -5}); // -3
    TreeNode *root4 = constructTree(vector<int> () = {1, -2, -3, 1, 3, -2, INT_MIN, -1}); // 3
    TreeNode *root5 = constructTree(vector<int> () = {-2, 6, INT_MIN, 0, -6}); // 6
    showTree(root0);
    showTree(root1);
    showTree(root2);
    showTree(root3);
    showTree(root4);
    showTree(root5);
    cout << s.maxPathSum(root0) << endl;
    cout << s.maxPathSum(root1) << endl;
    cout << s.maxPathSum(root2) << endl;
    cout << s.maxPathSum(root3) << endl;
    cout << s.maxPathSum(root4) << endl;
    cout << s.maxPathSum(root5) << endl;
    return 1;
}