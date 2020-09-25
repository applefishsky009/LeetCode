#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:\Github\RylModule\tree.h>
using namespace std;

// 使用迭代器,iterator中的方法
// time: O(n) 
// space: O(logn)
class Solution0 {
  public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return buildTree(begin(inorder), end(inorder), begin(postorder), end(postorder));
    }
  private:
    template <typename BidiIt>
    TreeNode *buildTree(BidiIt in_first, BidiIt in_last, BidiIt post_first, BidiIt post_last) {
        if (in_first == in_last) return nullptr;
        if (post_first == post_last) return nullptr;
        const auto val = *prev(post_last);  // 后序序列的最后一个是根节点
        TreeNode *root = new TreeNode(val); // 构造根节点
        auto in_root_pos = find(in_first, in_last, val);    // 分隔中序序列, 同时是左子树中序的超尾, 下一个节点即右子树的开始
        auto left_size = distance(in_first, in_root_pos);   // 计算左子树的大小
        auto post_left_last = next(post_first, left_size);  // 左子树后序的超尾, 右子树的起始
        root->left = buildTree(in_first, in_root_pos, post_first, post_left_last);  // 构建左子树
        root->right = buildTree(next(in_root_pos), in_last, post_left_last, prev(post_last));   // 构建右子树, 去掉尾(根)节点是右子树超尾
        return root;
    }
};

// stack
// time: O(n) 
// space: O(logn)
class Solution {
  public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (postorder.size() == 0) return nullptr;
        auto root = new TreeNode(postorder[postorder.size() - 1]);
        auto istk = stack<TreeNode*>();
        istk.push(root);
        int inorderIndex = inorder.size() - 1;
        for (int i = int(postorder.size()) - 2; i >= 0; --i) {
            int postorderVal = postorder[i];
            auto node = istk.top();
            if (node->val != inorder[inorderIndex]) {   // 相当于遍历了根节点的右子树, 然后都存在栈中
                node->right = new TreeNode(postorderVal);
                istk.push(node->right); // 子树进行同样处理
            } else {
                while (!istk.empty() && istk.top()->val == inorder[inorderIndex]) { // 弹出并左移index
                    node = istk.top();
                    istk.pop();
                    --inorderIndex;
                }
                node->left = new TreeNode(postorderVal);    // 当前节点是最后弹出节点的左孩子, 因为当前节点出现在了x和x在栈中下个节点的反向中序遍历之间
                istk.push(node->left);  // 子树进行同样处理
            }
        }
        return root;
    }
};

int main() {
    Solution s1;
    vector<int> inorder{4, 2, 5, 7, 1, 3, 6};
    vector<int> postorder{4, 7, 5, 2, 6, 3, 1};
    TreeNode *root = s1.buildTree(inorder, postorder);
    showTree(root);
    return 0;
}