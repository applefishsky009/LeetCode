#include <queue>
#include <vector>
#include <E:\RylModule\vector.h>
#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
		queue<pair<TreeNode *, int>> q;
		vector<vector<int>> result;
		if (!root)
			return result; //空树退出，不能压入<nullptr,1>
		vector<int> temp;
		int step = 1; //步长
		q.push(make_pair(root, step));
		while (!q.empty())
		{
			if (q.front().second == step) //等于步长
			temp.push_back(q.front().first->val);
			else //不等于步长，要存数据及更新步长
			{
				result.push_back(temp);
				temp.clear();
				temp.push_back(q.front().first->val);
				step++; //这是对自己步长的更新
			}
			//孩子步长一定是步长+1
			if (q.front().first->left)
				q.push(make_pair(q.front().first->left, step + 1));
			if (q.front().first->right)
				q.push(make_pair(q.front().first->right, step + 1));
			q.pop();
		}
		result.push_back(temp); //存入留在最后的数据
		return result;
    }
};

int main()
{
    Solution s1;
    TreeNode *root = constructTree(vector<int> () = {1, 2, 3, 4, 5}); 
    vector<vector<int>> result = s1.levelOrder(root);
	show2DVector(result);
    return 0;
}
