#include <climits>
#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    int maxPathSum(TreeNode *root)
    {
        int maxSum = INT_MIN;
        maxPathSumDFS(root, maxSum);
        return maxSum;
    }

  private:
    int maxPathSumDFS(TreeNode *root, int &maxSum)
    {
        if (!root)
            return 0;
        int left = maxPathSumDFS(root->left, maxSum);
        int right = maxPathSumDFS(root->right, maxSum);
        int line = max(root->val, max(root->val + left, root->val + right)); //left? right? or just node?
        int arc = root->val + left + right;
        maxSum = max(maxSum, max(line, arc));
        return line;
    }
};

int main()
{
    TreeNode *root = constructTree(vector<int>() = {1, -2, 3});
    showTree(root);
    Solution s1;
    cout << s1.maxPathSum(root) << endl;
    return 0;
}