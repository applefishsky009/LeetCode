#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// BFS
// time: O(n)
// sapce: O(n)
class Solution0 {
  public:
	vector<vector<int>> levelOrderBottom(TreeNode *root) {
		vector<vector<int>> ans;
		if (!root) return ans;
		queue<pair<TreeNode *, int>> iq;
		iq.push({root, 1});
		vector<int> cur_step;
		int pre_step = 1;
		while (!iq.empty()) {
			TreeNode *cur = iq.front().first; 
			int cur_s = iq.front().second;
			iq.pop();
			if (cur_s != pre_step) {	// 脉冲判断
				ans.push_back(cur_step);
				cur_step.clear();
				pre_step = cur_s;
			}
			cur_step.push_back(cur->val);
			if (cur->left) iq.push({cur->left, cur_s + 1});
			if (cur->right) iq.push({cur->right, cur_s + 1});
		}
		if (!cur_step.empty()) ans.push_back(cur_step);	// 补充最后一次脉冲
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

// BFS 不使用pair, 使用size控制步长
// time: O(n)
// sapce: O(n)
class Solution {
  public:
	vector<vector<int>> levelOrderBottom(TreeNode *root) {
		vector<vector<int>> ans;
		if (!root) return ans;
		queue<TreeNode *> iq;
		iq.push(root);
		vector<int> cur_step;
		while (!iq.empty()) {
			int isize = iq.size();
			for (int i = 0; i < isize; ++i) {
				auto node = iq.front(); iq.pop();
				cur_step.push_back(node->val);
				if (node->left) iq.push(node->left);
				if (node->right) iq.push(node->right);
			}
			ans.push_back(cur_step);
			cur_step.clear();
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

int main() {
	Solution s;
	vector<int> nums = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
	TreeNode *root = constructTree(nums);
	auto ans = s.levelOrderBottom(root);
	show2DVector(ans);
	return 0;
}