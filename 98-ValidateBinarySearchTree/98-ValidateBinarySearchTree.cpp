#include <vector>
#include <climits>
#include <iostream>
#include <E:\RylModule\tree.h>
using namespace std;

//O(n^2)暴力破解
class Solution
{
  public:
    bool isValidBST(TreeNode *root)
    {
        if (!root)
            return true;
        if (isLowBST(root->left, root->val) && isHighBST(root->right, root->val) &&
            isValidBST(root->left) && isValidBST(root->right))
            return true;
        return false;
    }

  private:
    bool isLowBST(TreeNode *root, int low)
    {
        if (!root)
            return true;
        if (root->val >= low)
            return false;
        if (isLowBST(root->left, low) && isLowBST(root->right, low))
            return true;
        return false;
    }
    bool isHighBST(TreeNode *root, int high)
    {
        if (!root)
            return true;
        if (root->val <= high)
            return false;
        if (isHighBST(root->left, high) && isHighBST(root->right, high))
            return true;
        return false;
    }
};

//DP思路,从下向上带缓存携带需要的信息。
//时间复杂度O(n)，空间复杂度O(2*n)
class Solution1
{
  public:
    bool isValidBST(TreeNode *root)
    {
        if (!root)
            return true;
        vector<long> l = minMaxCache(root->left);
        vector<long> r = minMaxCache(root->right);
        if (root->val > l[1] && root->val < r[0])
            return true;
        return false;
    }

  private:
    vector<long> minMaxCache(TreeNode *root)
    {
        if (!root)
            return vector<long>{LONG_MAX, LONG_MIN};
        vector<long> result(2, 0); //最小值和最大值
        vector<long> l = minMaxCache(root->left);
        vector<long> r = minMaxCache(root->right);
        if (root->val <= l[1] || root->val >= r[0])
            return vector<long>{LONG_MIN, LONG_MAX};     //当前层不满足要求，返回fail值
        result[0] = l[0] == LONG_MAX ? root->val : l[0]; //找最小值
        result[1] = r[1] == LONG_MIN ? root->val : r[1]; //找最大值
        return result;
    }
};

//传递上下界，分治思想，时间复杂度O(n)，空间复杂度O(logn)
class Solution3
{
  public:
    bool isValidBST(TreeNode *root)
    {
        return isValidBST(root, INT_MIN, INT_MAX);
    }

  private:
    bool isValidBST(TreeNode *root, long lower, long upper)
    {
        if (root == nullptr)
            return true;
        return root->val > lower &&
               root->val < upper &&
               isValidBST(root->left, lower, root->val) &&
               isValidBST(root->right, root->val, upper);
    }
};

int main()
{
    Solution s1;
    TreeNode *root = constructTree(vector<int>() = {10, 5, 15, 2, 9});
    cout << s1.isValidBST(root) << endl;
    return 0;
}