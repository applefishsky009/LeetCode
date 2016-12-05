#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <iostream>
#include <E:\RylModule\tree.h>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
		vector<vector<int>> result;
		if (!root)
			return result;
		vector<int> path;
		queue<pair<TreeNode *, int>> q;
		q.push(make_pair(root, 1));
		int step = 1; //记录当前步长用于判断
		while (!q.empty())
		{
			TreeNode *temp = q.front().first;
			int tempStep = q.front().second;
			if (temp->left)
				q.push(make_pair(temp->left, tempStep + 1));
			if (temp->right)
				q.push(make_pair(temp->right, tempStep + 1));
			if (tempStep == step)
			{			//同一层
				if (step & 0x1) //奇数步长
					path.push_back(temp->val);
				else //偶数步长，vector当作stack用
					path.insert(path.begin(), temp->val);
			}
			else
			{
				step++;
				result.push_back(path);
				path.clear();
				path.push_back(temp->val);
			}
			q.pop();
		}
		result.push_back(path); //留在最后一层的数据
		path.clear();
		return result;
    }
};

int main()
{
    TreeNode *root =constructTree(vector<int> () = {3, 9, 20, 15, 7}); 
    Solution s1;
    vector<vector<int>> result = s1.zigzagLevelOrder(root);
	show2DVector(result);
    return 0;
}