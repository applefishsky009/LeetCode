#include <vector>
#include <iostream>
#include <algorithm>
#include <D:\Github\RylModule\tree.h>
using namespace std;

// 一定要严格注意各个变量的物理含义，防止混用
class Solution
{
  public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }
  private:
    TreeNode *buildTree(vector<int> &preorder, int pre_start, int pre_end, 
                        vector<int> &inorder, int in_start, int in_end) {
        int i = in_start;
        if (pre_start >= pre_end || in_start >= in_end)
            return nullptr;
        TreeNode *head = new TreeNode(preorder[pre_start]);
        for (; i < in_end; i++)
            if (inorder[i] == preorder[pre_start])
                break;
        head->left = buildTree(preorder, pre_start + 1, pre_start + i - in_start + 1, inorder, in_start, i);
        head->right = buildTree(preorder, pre_start + i - in_start + 1, pre_end, inorder, i + 1, in_end);
        return head;
    }
};

int main()
{
    Solution s1;
    // vector<int> preorder{1, 2, 4, 5, 3, 6, 7};
    // vector<int> inorder{4, 2, 5, 1, 6, 3, 7};
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};
    TreeNode *root = s1.buildTree(preorder, inorder);
    showTree(root);
    return 0;
}