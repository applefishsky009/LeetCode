#include <vector>
#include <E:\RylModule\tree.h>
using namespace std;

//一个函数的递归，可以调用重载函数省略新建结点与指针操作
//不能用中序遍历判断vector是否对称来做，以1233N2N(层次顺序)为例
class Solution
{
  public:
    bool isSymmetric(TreeNode *root)
    {
		if (root == nullptr)
			return true;
		TreeNode *p = root->left;
		TreeNode *q = root->right;
		if (p == nullptr && q == nullptr)
			return true;
		if (p == nullptr || q == nullptr)
			return false;
		TreeNode *rootTempE = new TreeNode(-1);
		rootTempE->left = p->left;
		rootTempE->right = q->right;
		TreeNode *rootTempI = new TreeNode(-1);
		rootTempI->left = p->right;
		rootTempI->right = q->left;
		//以下语句可以简化
		if (p->val == q->val && isSymmetric(rootTempE) && isSymmetric(rootTempI))
			return true;
		return false;
    }
};

//重载
class Solution1
{
  public:
    bool isSymmetric(TreeNode *root)
    {
		if (root == nullptr)
			return true;
		return isSymmetric(root->left, root->right);
    }

  private:
    bool isSymmetric(TreeNode *p, TreeNode *q)
    {
		if (p == nullptr && q == nullptr)
			return true;
		if (p == nullptr || q == nullptr)
			return false;
		return (p->val == q->val && isSymmetric(p->left, q->right) && isSymmetric(p->right, q->left));
    }
};

int main()
{
    TreeNode *root = constructTree(vector<int> () = {1, 2, 2, 3, 4, 4, 3});
    Solution1 s1;
    bool flag = s1.isSymmetric(root);
	cout << flag << endl;
    return 0;
}