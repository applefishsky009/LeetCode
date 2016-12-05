#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    vector<TreeNode *> generateTrees(int n)
    {
        if (0 == n)
            return vector<TreeNode *>(); //注意匿名对象的写法，而且n=0时不是返回nullptr而是空容器
        return generateTrees(1, n + 1);
    }

  private:
    vector<TreeNode *> generateTrees(int start, int end)
    {
        if (start == end)
            return vector<TreeNode *>{nullptr};
        vector<TreeNode *> result;
        for (int i = start; i < end; ++i)
        {
            vector<TreeNode *> left = generateTrees(start, i);
            vector<TreeNode *> right = generateTrees(i + 1, end);
            for (auto j : left)
            {
                for (auto k : right)
                {
                    TreeNode *tmp = new TreeNode(i);
                    tmp->left = j;
                    tmp->right = k;
                    result.push_back(tmp);
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution s1;
    int n = 3;
    vector<TreeNode*> rootVector = s1.generateTrees(n);
    for (int i = 0;i < rootVector.size(); i++)
        showTree(rootVector[i]);
    return 0;
}