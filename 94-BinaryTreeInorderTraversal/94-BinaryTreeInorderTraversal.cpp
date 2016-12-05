#include <stack>
#include <vector>
#include <E:\RylModule\tree.h>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<int> inorderTraversal(TreeNode *root)
    {
		vector<int> result;
		stack<TreeNode *> sS1;
		while (root || !sS1.empty())
		{
			while (root)
			{
				//result.push_back(root->val);	//先序遍历的位置
				sS1.push(root);
				root = root->left;
			}
			if (!sS1.empty())
			{
				root = sS1.top();
				sS1.pop();
				result.push_back(root->val); //中序遍历的位置
				root = root->right;
			}
		}
		return result;
    }
};

int main()
{
    Solution s1;
    vector<int> result;
    TreeNode *root = constructTree(vector<int>() = {0, -1, 2, -1, -1, 5, 6, -1, -1, -1, -1, 11, 12});
	showTree(root);
    result = s1.inorderTraversal(root);
	show1DVector(result);
    return 0;
}