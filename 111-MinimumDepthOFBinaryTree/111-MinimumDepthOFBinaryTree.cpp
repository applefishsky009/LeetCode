#include <stack>
#include <vector>
#include <climits>
#include <iostream>
#include <iterator>
#include <E:\RylModule\tree.h>
using namespace std;

//注意必须到叶子结点(左孩子和右孩子都为空才行)
class Solution
{
  public:
    int minDepth(TreeNode *root)
    {
        if (!root)
            return 0; //根结点单独处理，防止递归的时候每次都要判断
        return minDepthExp(root);
    }

  private:
    int minDepthExp(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return 1; //叶子
        if (root->left == nullptr || root->right == nullptr)
            return root->left == nullptr ? 1 + minDepth(root->right) : 1 + minDepth(root->left);
        return 1 + min(minDepth(root->left), minDepth(root->right)); //左右孩子都不为空
    }
};

//感觉逻辑上比上面的要难理解，其实复杂度都一样，但是这个更像DP(带缓存的自下向上的递归)
class Solution1
{
  public:
    int minDepth(const TreeNode *root)
    {
        return minDepth(root, false);
    }

  private:
    int minDepth(const TreeNode *root, bool hasbrother)
    {
        if (!root)
            return hasbrother ? INT_MAX : 0; //root为空，且有兄弟返回INT_MAX,代表此路不通，没有兄弟说明她parent是叶子结点
        return 1 + min(minDepth(root->left, root->right != NULL), minDepth(root->right, root->left != NULL));
    }
};

//递归用栈写成非迭代的
class Solution2
{
  public:
    int minDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        int minDep = INT_MAX;
        stack<pair<TreeNode *, int>> s;
        s.push(make_pair(root, 1));
        while (!s.empty())
        {
            auto tmp = s.top();
            s.pop();
            if (!tmp.first->left && !tmp.first->right) //叶子结点
                minDep = min(minDep, tmp.second);
            else if (tmp.first->left || tmp.first->right)
            { //非叶子结点
                if (tmp.first->left)
                    s.push(make_pair(tmp.first->left, tmp.second + 1));
                if (tmp.first->right)
                    s.push(make_pair(tmp.first->right, tmp.second + 1));
            }
        }
        return minDep;
    }
};

int main()
{
    Solution2 s1;
    TreeNode *root = constructTree(vector<int> () = {1, 2, 3, 4}); 
    cout << s1.minDepth(root) << endl;
    return 0;
}