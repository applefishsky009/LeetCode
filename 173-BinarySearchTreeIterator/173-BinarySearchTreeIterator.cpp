#include <stack>
#include <E:\RylModule\tree.h>
using namespace std;

class BSTIterator
{
  public:
    BSTIterator(TreeNode *root)
    {
        findLeft(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext()
    {
        return !minPath.empty();
    }

    /** @return the next smallest number */
    int next()
    {
        TreeNode *target = minPath.top();
        minPath.pop();
        if (target->right)
            findLeft(target->right);
        return target->val;
    }

  private:
    stack<TreeNode *> minPath;
    void findLeft(TreeNode *root)
    {
        TreeNode *pre = root;
        while (pre)
        {
            minPath.push(pre);
            pre = pre->left;
        }
    }
};

int main()
{
    //BSTIterator s1;
    TreeNode *root = constructTree(vector<int>() = {5, 3, 8, 1, 4, 6, 9, -1, 2, -1, -1, -1, 7});
    showTree(root);
    BSTIterator i = BSTIterator(root);
    while (i.hasNext())
        cout << i.next() << ends;
    cout << endl;
    return 0;
}