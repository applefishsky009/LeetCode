#include <queue>
#include <vector>
#include <iterator>
#include <iostream>
#include <E:\RylModule\tree.h>
#include <E:\RylModule\vector.h>
using namespace std;

//BFS,
//头插用insert()，尾插用push_back();
class Solution
{
  public:
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
		vector<vector<int>> result;
		vector<int> path;
		if (root == nullptr)
			return result;
		queue<pair<TreeNode *, int>> q;
		int step = 1;
		q.push(make_pair(root, step));
		while (!q.empty())
		{
			TreeNode *temp = q.front().first;
			if (q.front().second == step)
				path.push_back(temp->val);
			else
			{
				result.insert(result.begin(), path);
				path.clear();
				path.push_back(temp->val);
				++step;
			}
			if (temp->left)
				q.push(make_pair(temp->left, q.front().second + 1));
			if (temp->right)
				q.push(make_pair(temp->right, q.front().second + 1));
			q.pop();
		}
		result.insert(result.begin(), path);
		path.clear();
		return result;
    }
};

int main()
{
    TreeNode *head = constructTree(vector<int> () = {3, 9, 20, 15, 7});
    Solution s1;
    vector<vector<int>> result = s1.levelOrderBottom(head);
	show2DVector(result);
    return 0;
}