#include <stack>
#include <vector>
#include <iostream>
#include <E:\RylModule\tree.h>
#include <E:\RylModule\vector.h>
using namespace std;

//对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它。
//或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
//若非上述两种情况，则将P的右孩子和左孩子依次入栈。
//这样就保证了每次取栈顶元素的时候，左孩子和右孩子都在根结点前面被访问。
class Solution
{
  public:
    vector<int> postorderTraversal(TreeNode *root)
    {
		vector<int> outTreeNode;
		stack<TreeNode *> sTreeNode;
		TreeNode *pre = nullptr; //指向之前访问的节点
		if (root)
			sTreeNode.push(root);
		while (!sTreeNode.empty())
		{
			root = sTreeNode.top();
			if ((root->left == nullptr && root->right == nullptr) || (pre != nullptr && (pre == root->left || pre == root->right)))
			{
				outTreeNode.push_back(root->val);
				pre = root;
				sTreeNode.pop();
			}
			else
			{
				if (root->right)
					sTreeNode.push(root->right); //右孩子先入栈，后访问
				if (root->left)
					sTreeNode.push(root->left); //左孩子后入栈，先访问
			}
		}
		return outTreeNode;
    }
};

//左子树->右子树->节点(后序)    《=》    节点->右子树->左子树(前序) 的翻转(栈)
class Solution1
{
  public:
    vector<int> postorderTraversal(TreeNode *root)
    {
		vector<int> outTreeNode;
		stack<TreeNode *> sTreeNode;
		stack<int> sInt;
		while (root || !sTreeNode.empty())
		{
			while (root)
			{
				sInt.push(root->val);
				sTreeNode.push(root);
				root = root->right;
			}
			if (!sTreeNode.empty())
			{
				root = sTreeNode.top();
				sTreeNode.pop();
				root = root->left;
			}
		}
		while (!sInt.empty())
		{
			outTreeNode.push_back(sInt.top());
			sInt.pop();
		}
		return outTreeNode;
    }
};

class Solution2
{
  public:
    void Traversal(TreeNode *root, vector<int> &result)
    {
		if (root == nullptr)
			return;
		//result.push_back(root->val);	//preorderTraversal
		Traversal(root->left, result);
		//result.push_back(root->val);	//inorderTraversal
		Traversal(root->right, result);
		result.push_back(root->val); //postorderTraversal
    }
};

int main()
{
    TreeNode *root = constructTree(vector<int> () = {1, 2, 3});
    vector<int> outPostorderTraversal;
    Solution s1;
    outPostorderTraversal = s1.postorderTraversal(root);
	show1DVector(outPostorderTraversal);
    return 0;
}