#include <algorithm>
#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    bool isBalanced(TreeNode *root)
    {
		if (root == nullptr)
			return true;
		return abs(balancedHeight(root->left, 1) - balancedHeight(root->right, 1)) <= 1 && //该结点平衡
			isBalanced(root->left) && isBalanced(root->right);			   //递归，左右孩子都平衡
    }

  private:
    int balancedHeight(TreeNode *root, int h)
    { //计算二叉树高度
		if (root == nullptr)
			return h - 1;
		return max(balancedHeight(root->left, h + 1), balancedHeight(root->right, h + 1));
    }
};

//改进，在计算高度时加限制条件
class Solution1
{
  public:
    bool isBalanced(TreeNode *root)
    {
		return balancedHeight(root) >= 0;
    }
    int balancedHeight(TreeNode *root)
    {
		if (root == nullptr)
			return 0; //终止条件
		int left = balancedHeight(root->left);
		int right = balancedHeight(root->right);
		//没有以下语句就是简单的计算二叉树高度的函数
		if (left < 0 || right < 0 || abs(left - right) > 1)
			return -1;		     //限制条件
		return max(left, right) + 1; //向上传递高度
    }
};

int main()
{
    Solution1 s1;
    TreeNode *root = constructTree(vector<int> () = {1, 2, 3, 4}); 
    bool result = s1.isBalanced(root);
	cout << result << endl;
    return 0;
}