#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    int sumNumbers(TreeNode *root)
    {
        int sum = 0;
        sumNumbersDFS(root, sum, 0);
        return sum;
    }

  private:
    void sumNumbersDFS(TreeNode *root, int &sum, int cur)
    {
        if (!root)
            return;
        if (!root->left && !root->right)
        {
            sum += cur * 10 + root->val;
            return;
        }
        sumNumbersDFS(root->left, sum, cur * 10 + root->val);
        sumNumbersDFS(root->right, sum, cur * 10 + root->val);
        return;
    }
};

int main()
{
    TreeNode *root = constructTree(vector<int>() = {1, 2, 3});
    showTree(root);
    Solution s1;
    cout << s1.sumNumbers(root) << endl;
    return 0;
}