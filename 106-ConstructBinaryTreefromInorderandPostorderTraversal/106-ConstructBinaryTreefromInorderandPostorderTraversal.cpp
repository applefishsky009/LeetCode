#include <vector>
#include <iostream>
#include <E:\RylModule\tree.h>
using namespace std;

//传递上下标，注意传引用，不然内存超限制'
class Solution
{
  public:
    TreeNode *buildTree(const vector<int> &inorder, const vector<int> &postorder)
    {
        return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

  private:
    TreeNode *buildTree(const vector<int> &inorder, int inStart, int inEnd, 
                        const vector<int> &postorder, int postStart, int postEnd)
    {
        if (inStart > inEnd)
            return nullptr;
        TreeNode *root = new TreeNode(postorder[postEnd]);
        int leftNum = 0;
        int key = 0;
        for (int i = inStart; i <= inEnd; ++i)
        {
            if (inorder[i] == postorder[postEnd])
            {
                key = i;
                break;
            }
            ++leftNum;
        }
        root->right = buildTree(inorder, key + 1, inEnd, postorder, postStart + leftNum, postEnd - 1);
        root->left = buildTree(inorder, inStart, key - 1, postorder, postStart, postStart + leftNum - 1);
        return root;
    }
};

//使用迭代器,iterator中的方法
// LeetCode, Construct Binary Tree from Inorder and Postorder Traversal
// 时间复杂度 O(n) 空间复杂度 O(logn)
class Solution1
{
  public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return buildTree(begin(inorder), end(inorder), begin(postorder), end(postorder));
    }

  private:
    template <typename BidiIt>
    TreeNode *buildTree(BidiIt in_first, BidiIt in_last, BidiIt post_first, BidiIt post_last)
    {
        if (in_first == in_last)
            return nullptr;
        if (post_first == post_last)
            return nullptr;
        const auto val = *prev(post_last);
        TreeNode *root = new TreeNode(val);
        auto in_root_pos = find(in_first, in_last, val);
        auto left_size = distance(in_first, in_root_pos);
        auto post_left_last = next(post_first, left_size);
        root->left = buildTree(in_first, in_root_pos, post_first, post_left_last);
        root->right = buildTree(next(in_root_pos), in_last, post_left_last,
                                prev(post_last));
        return root;
    }
};

int main()
{
    Solution s1;
    vector<int> inorder{4, 2, 5, 7, 1, 3, 6};
    vector<int> postorder{4, 7, 5, 2, 6, 3, 1};
    TreeNode *root = s1.buildTree(inorder, postorder);
    showTree(root);
    return 0;
}