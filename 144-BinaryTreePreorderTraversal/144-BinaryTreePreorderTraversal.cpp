#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <E:\RylModule\tree.h>
#include <E:\RylModule\vector.h>
using namespace std;

//A by leetcode
class Solution
{
  public:
    vector<int> preorderTraversal(TreeNode *root)
    {
		vector<int> a;
		stack<TreeNode *> sS1;
		TreeNode *temp = root;
		if (!temp)
			return a;
		while (temp || !sS1.empty())
		{
			while (temp)
			{
				a.push_back(temp->val);
				sS1.push(temp);
				temp = temp->left;
			}
			if (!sS1.empty())
			{
				//cout<<"#";//每次读取栈说明遇到一个空指针
				temp = sS1.top();
				sS1.pop();
				temp = temp->right;
			}
		}
		return a;
    }
};

int main()
{
    TreeNode *root = constructTree(vector<int> () = {1, -1, 2, -1, -1, 3});
	Solution s1;
    vector<int> result = s1.preorderTraversal(root);
    show1DVector(result);
    return 0;
}