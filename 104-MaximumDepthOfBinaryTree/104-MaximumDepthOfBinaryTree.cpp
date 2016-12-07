#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    int maxDepth(TreeNode* root)
    {
        if (!root)
            return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
} ;

int main()
{
    Solution s1;
    TreeNode *root = constructTree();
    showTree(root);
    cout << s1.maxDepth(root) << endl;
    return 0;
}