#include <stack>
#include <iostream>
#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
		if (p == nullptr || q == nullptr)
		{
			if (p == nullptr && q == nullptr)
				return true;
			return false;
		}
		if (p->val == q->val)
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		return false;
    }
};

class Solution1
{
  public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
		stack<TreeNode *> s;
		s.push(p);
		s.push(q);
		while (!s.empty())
		{
			p = s.top();
			s.pop();
			q = s.top();
			s.pop();
			if (p == nullptr && q == nullptr)
				continue;
			if (p == nullptr || q == nullptr)
				return false;
			if (p->val != q->val)
				return false;
			s.push(q->left);
			s.push(p->left);
			s.push(q->right);
			s.push(p->right);
		}
		return true;
    }
};

int main()
{
    TreeNode *p = constructTree(vector<int> () = {1, 2, 3});
    TreeNode *q = constructTree(vector<int> () = {1, 2, 3});
    Solution1 s1;
    cout << s1.isSameTree(p, q) << endl;
    return 0;
}