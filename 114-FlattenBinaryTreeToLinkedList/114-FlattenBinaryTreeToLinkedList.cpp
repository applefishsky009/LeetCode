#include <E:\RylModule\tree.h>
using namespace std;

//http://mp.weixin.qq.com/s?__biz=MzI1MTIzMzI2MA==&mid=2650560140&idx=1&sn=9a8884a2282b51906733c9c149c6db3c&scene=23&srcid=0728pEPY9XPc8RYKpUQF6lfn#rd
//参考以上第四张动图思路,
//注意有左节点需要调整，没有要进一步判断
//对链表而言，要注意调整时要不要置空
class Solution
{
  public:
    void flatten(TreeNode *root)
    {
		if (root == nullptr)
			return;
		TreeNode *temp = root;
		while (temp)
		{
			if (temp->left)
			{
				TreeNode *p = temp->right; //记录右孩子
				TreeNode *q = temp->left;
				while (q->right)
					q = q->right; //找左孩子的最右结点，是右孩子的父结点
				q->right = p;
				temp->right = temp->left;
				temp->left = nullptr; //左节点置空
				temp = temp->right;
			}
			else //继续找
				temp = temp->right;
		}
		return;
    }
};

int main()
{
    Solution s1;
    TreeNode *root = constructTree(vector<int>() = {1, -1, 2, -1, -1, 3});
    showTree(root);
    s1.flatten(root);
    showTree(root);
    return 0;
}