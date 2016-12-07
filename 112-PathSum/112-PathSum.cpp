#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        if (!root)
            return false;
        if (!root->left && !root->right) //mind Leaf, must have this two judge
            return sum == root->val ? true : false;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

int main()
{
    Solution s1;
    TreeNode *root = constructTree(vector<int>() = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, -1, -1, 1});
    showTree(root);
    int sum = 22;
    cout << s1.hasPathSum(root, sum) << endl;
    return 0;
}