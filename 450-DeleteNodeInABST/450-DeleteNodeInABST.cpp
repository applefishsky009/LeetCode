#include <cmath>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

class Solution {
  public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;  // 空树
        pair<TreeNode*, TreeNode*> ans = searchBST(root, key);  // 搜索父亲-孩子节点对
        if (!ans.second) return root;   // 没找到
        if (!ans.second->right) // 左右子树有一个为空, 直接替换
            transPlant(root, ans.first, ans.second, ans.second->left);
        else if (!ans.second->left)
            transPlant(root, ans.first, ans.second, ans.second->right);
        else {  // 均不为空, 需要找前驱或者后继, 下面的实现为找后继, 必然在右子树中
            pair<TreeNode*, TreeNode*> imin = treeMinimum(ans.second, ans.second->right);   // 后继的父亲-孩子节点对
            if (imin.second != ans.second->right) { // 将后继构造为右子树根节点
                transPlant(root, imin.first, imin.second, imin.second->right);
                imin.second->right = ans.second->right;
            }
            transPlant(root, ans.first, ans.second, imin.second);   // 子树替换
            imin.second->left = ans.second->left;
        }
        return root;
    }
  private:
    pair<TreeNode*, TreeNode*> searchBST(TreeNode* root, int key) {
        pair<TreeNode*, TreeNode*> ans(nullptr, nullptr);
        do {
            if (root->val == key) {
                ans.second = root;
                return ans;
            }
            ans.first = root;   // 更新父节点
            if (root->val > key)
                root = root->left;
            else
                root = root->right;
        } while (root);
        return ans;
    }
    void transPlant(TreeNode* &root, TreeNode* parent, TreeNode* u, TreeNode* v) {  // 必须传入root引用,因为root可能发生改变
        if (!parent)
            root = v;
        else if (parent->right == u)
            parent->right = v;
        else
            parent->left = v;
    }
    pair<TreeNode*, TreeNode*> treeMinimum(TreeNode* parentRoot, TreeNode* root) {
        pair<TreeNode*, TreeNode*> ans(parentRoot, nullptr);
        if (!root) return ans;
        while (root->left) {
            ans.first = root;
            root = root->left;
        }
        ans.second = root;
        return ans;
    }
};

int main() {
    Solution s;
    // TreeNode *root0 = constructTree(vector<int> () = {5, 3, 6, 2, 4, INT_MIN, 7});
    // TreeNode *root1 = constructTree(vector<int> () = {0});
    TreeNode *root2 = constructTree(vector<int> () = {
    2, 
    0, 33, 
    INT_MIN, 1, 25, 40, 
    INT_MIN, INT_MIN, INT_MIN, INT_MIN, 11, 31, 34, 45});
    // INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 10, 18, 29, 32, INT_MIN, 36, 43, 46});
    // 4,INT_MIN,12,24,26,30,INT_MIN,INT_MIN,35,39,42,44,INT_MIN,48,3,9,INT_MIN,14,22,INT_MIN,INT_MIN,27,INT_MIN,INT_MIN,INT_MIN,INT_MIN,38,INT_MIN,41,INT_MIN,INT_MIN,INT_MIN,47,49,INT_MIN,INT_MIN,5,INT_MIN,13,15,21,23,INT_MIN,28,37,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,8,INT_MIN,INT_MIN,INT_MIN,17,19,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,7,INT_MIN,16,INT_MIN,INT_MIN,20,6});
    // showTree(root0);
    // showTree(root1);
    showTree(root2);
    // showTree(s.deleteNode(root1, 0));
    // showTree(s.deleteNode(root0, 3));
    showTree(s.deleteNode(root2, 33));
    return 1;
}