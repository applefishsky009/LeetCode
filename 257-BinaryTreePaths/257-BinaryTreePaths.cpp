#include <stack>
#include <string>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 递归
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        string path;
        dfs(ans, root, path);
        return ans;
    }
  private:
    void dfs(vector<string> &ans, TreeNode *root, string path) {
        if (!root) return;
        path += to_string(root->val);
        if (!root->left && !root->right)
            ans.push_back(path);
        else {
            path += "->";
            dfs(ans, root->left, path);
            dfs(ans, root->right, path);
        }
    }
};

// 迭代
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        if (!root) return ans;
        stack<TreeNode *> node_stack;
        stack<string> path_stack;   // 记录当前节点的时候顺便记录路径
        node_stack.push(root);
        path_stack.push(to_string(root->val));
        TreeNode *node = nullptr;
        string path;
        while (!node_stack.empty()) {
            node = node_stack.top(); node_stack.pop();
            path = path_stack.top(); path_stack.pop();
            if (!node->left && !node->right)
                ans.push_back(path);
            if (node->left) {
                node_stack.push(node->left);
                path_stack.push(path + "->" + to_string(node->left->val));  // 构造新路径
            }
            if (node->right) {
                node_stack.push(node->right);
                path_stack.push(path + "->" + to_string(node->right->val)); // 构造新路径
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> num = {1, 2, 3, INT_MIN, 5};
    TreeNode *root = constructTree(num);
    showTree(root);
    show1DVector(s.binaryTreePaths(root));
    return 0;
}