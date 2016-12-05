#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\tree.h>
using namespace std;

//递归，传递数组下标(头和尾)，注意计算下标
class Solution
{
  public:
    TreeNode *buildTree(const vector<int> &preorder, const vector<int> &inorder)
    {
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

  private:
    TreeNode *buildTree(const vector<int> &preorder, int start1, int end1, const vector<int> &inorder, int start2, int end2)
    {
        if (end1 < start1)
            return nullptr;
        TreeNode *root = new TreeNode(preorder[start1]);
        int i = start2;
        for (; i <= end2; ++i)
            if (inorder[i] == preorder[start1])
                break;
        root->left = buildTree(preorder, start1 + 1, start1 + i - start2, inorder, start2, i - 1); //i = start2时下次递归start1会越界返回nullptr
        root->right = buildTree(preorder, start1 + 1 + i - start2, end1, inorder, i + 1, end2);
        return root;
    }
};

//用迭代器方法，传递头和超尾
class Solution1
{
  public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return buildTree(begin(preorder), end(preorder), begin(inorder), end(inorder));
    }

  private:
    template <typename InputIterator>
    TreeNode *buildTree(InputIterator pre_first, InputIterator pre_last, InputIterator in_first, InputIterator in_last)
    {
        if (pre_first == pre_last)
            return nullptr;
        if (in_first == in_last)
            return nullptr;
        auto root = new TreeNode(*pre_first);
        auto inRootPos = find(in_first, in_last, *pre_first);
        auto leftSize = distance(in_first, inRootPos);
        root->left = buildTree(next(pre_first), next(pre_first, leftSize + 1), in_first, next(in_first, leftSize));
        root->right = buildTree(next(pre_first, leftSize + 1), pre_last, next(inRootPos), in_last);
        return root;
    }
};

int main()
{
    Solution1 s1;
    vector<int> preorder{1, 2, 4, 5, 3, 6, 7};
    vector<int> inorder{4, 2, 5, 1, 6, 3, 7};
    TreeNode *root = s1.buildTree(preorder, inorder);
    showTree(root);
    return 0;
}