#include <stack>
#include <string>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 递归 - dfs
// time: O(n^2)
// space: O(n^2)
class Solution0 {
  public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        if (!root) return ans;
        string path = "";
        if (root) dfs(ans, root, path);
        return ans;
    }
  private:
    void dfs(vector<string> &ans, TreeNode *root, string path) {
        path += path.size() == 0 ? to_string(root->val) : "->" + to_string(root->val);
        if (!root->left && !root->right) {
            ans.push_back(path);
            return;
        }
        if (root->left)
            dfs(ans, root->left, path);
        if (root->right)
            dfs(ans, root->right, path);
    }
};

// 迭代 - bfs
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        if (!root) return ans;
        string path;
        stack<TreeNode *> istk;
        stack<string> istk_path;
        istk.emplace(root);
        istk_path.emplace("");  // 未加入路径的起始点
        while (!istk.empty()) {
            TreeNode *cur = istk.top(); istk.pop();
            string cur_path = istk_path.top(); istk_path.pop();
            cur_path += to_string(cur->val);
            if (!cur->left && !cur->right)
                ans.push_back(cur_path);
            else {
                cur_path += "->";
                if (cur->left) {istk.push(cur->left); istk_path.push(cur_path);};
                if (cur->right) {istk.push(cur->right); istk_path.push(cur_path);};
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