#include <iostream>
#include <algorithm>
#include <E:\RylModule\tree.h>
using namespace std;

//要求O(1)空间复杂度，必须用Moriis遍历法，二叉搜索树用中序遍历得到有序列表
//Morris遍历的核心是使当前结点左孩子的最终右孩子的右指针指向当前结点
//其分为三个阶段，制作指针阶段，回溯阶段，恢复指针阶段
//在回溯阶段(因为是中序，往右走之前遍历当前结点)访问右孩子的右结点，在恢复指针阶段访问当前结点
class Solution
{
  public:
    void recoverTree(TreeNode *root)
    {
		pair<TreeNode *, TreeNode *> misNode(nullptr, nullptr); //使用pair对象存储mistake节点对
		TreeNode *pre = nullptr;
		TreeNode *cur = root;
		while (cur != nullptr)
		{
			if (cur->left != nullptr)
			{ //遍历左孩子
				TreeNode *node = cur->left;
				while (node->right != nullptr && node->right != cur) //找到当前结点的最右节点来判断是指针制作阶段还是遍历阶段
					node = node->right;
				if (node->right == nullptr)
				{ //制作指针阶段
					//cout << "make iterator" << endl;
					node->right = cur;
					cur = cur->left;
				}
				else
				{ //不需要制作指针，这是遍历阶段，恢复二叉树
					//cout << "iterator recovery"<< endl;
					node->right = nullptr;
					//cout << cur->val << endl;
					detect(misNode, pre, cur);
					pre = cur; //使用两个指针遍历
					cur = cur->right;
				}
			}
			else
			{ 	//左孩子遍历完成，回溯一步遍历右孩子(指针已经制作好了)
				//cout << "backtracking" << endl;
				//cout << cur->val << endl;
				detect(misNode, pre, cur);
				pre = cur; //使用两个指针遍历
				cur = cur->right;
			}
		}
		swap(misNode.first->val, misNode.second->val);
    }
    //注意这是怎么检测的，如果两个元素逻辑上相邻，遍历只会出现一次异常，因此第一次异常就要及时更新second
    //如果两个元素逻辑上不相邻，遍历会出现两次异常，在第二次异常要更新second
    //幸运的是，可以根据first是否为空来判断是否是第一次异常来更新first为pre,而显然不管是哪一次异常，second都应该为cur
  private:
    void detect(pair<TreeNode *, TreeNode *> &misNode, TreeNode *pre, TreeNode *cur)
    {
		if (pre != nullptr && pre->val > cur->val)
		{ //异常值
			if (misNode.first == nullptr)
				misNode.first = pre;
			misNode.second = cur;
		}
    }
};

//明白检测错误元素的原理之后，可以使用普通的递归方法投机取巧，逻辑上更简单，但内存并没有节省
//只是将栈变量转化为函数栈

int main()
{
    TreeNode *root = constructTree(vector<int> () = {5, 6, 7, 2, 4, 3, 8}); 
	showTree(root);
    Solution s1;
    s1.recoverTree(root);
	showTree(root);
    return 0;
}