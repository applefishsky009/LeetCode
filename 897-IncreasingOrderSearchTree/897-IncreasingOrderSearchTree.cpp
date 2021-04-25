#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 中序遍历之后生成新的树, 借助vector在遍历的时候就保存连接关系不用多遍历vector
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    TreeNode* increasingBST(TreeNode *root) {
        TreeNode start = TreeNode(0);
        vector<TreeNode *> ans;
        ans.push_back(&start);
        dfs(root, ans);
        return ans[0]->right;
    }
  private:
    void dfs(TreeNode *root, vector<TreeNode *> &ans) {
        if (!root) return;
        dfs(root->left, ans);
        TreeNode *tmp = new TreeNode(root->val);    // 注意使用堆空间不要使用栈空间
        ans.back()->right = tmp;
        ans.push_back(tmp);
        dfs(root->right, ans);
    }
};

// 在遍历的时候就保存连接关系
// time: O(n)
// space: O(n)
class Solution {
  public:
    TreeNode *increasingBST(TreeNode *root) {
        TreeNode *dummyNode = new TreeNode(-1);
        resNode = dummyNode;
        inorder(root);
        return dummyNode->right;
    }
  private:
    TreeNode *resNode;  // 借助全局变量保存pre信息
    void inorder(TreeNode *node) {  // 递归栈保存了节点引用
        if (!node) return;
        inorder(node->left);
        // 在遍历的时候修改节点指向
        resNode->right = node;
        node->left = nullptr;
        resNode = node;
        inorder(node->right);
    }
};

int main() {
    Solution s;
    TreeNode *root = constructTree(vector<int>() = {5, 1, 7});
    showTree(s.increasingBST(root));
    return 0;
}