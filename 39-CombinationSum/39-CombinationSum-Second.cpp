#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 搜索回溯
// time: O(S)	所有可行解的长度之和
// space: O(target)	递归的栈深度, 最差为target
class Solution0 {
  public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
		vector<int> path;
		vector<vector<int>> ans;
		sort(candidates.begin(), candidates.end());
		dfs(candidates, target, ans, path);
		return ans;
	}
  private:
	void dfs(vector<int> &candidates, int target, vector<vector<int>> &ans, vector<int> &path) {
		if (target == 0) {
			ans.emplace_back(path);
			return;
		}
		for (int i = 0; i < candidates.size(); ++i) {
			if (target - candidates[i] < 0) break;	// 剪枝
			if (!path.empty() && candidates[i] < path.back()) continue;	// 剪枝
			path.emplace_back(candidates[i]);
			dfs(candidates, target - candidates[i], ans, path);
			path.pop_back();	// 回溯
		}
	}
};

// 搜索回溯 - 朴素解法 - 选或者不选当前数
// time: O(S)	所有可行解的长度之和
// space: O(target)	递归的栈深度, 最差为target
class Solution {
  public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
		vector<int> path;
		vector<vector<int>> ans;
		sort(candidates.begin(), candidates.end());
		dfs(candidates, target, ans, path, 0);
		return ans;
	}
  private:
	void dfs(vector<int> &candidates, int target, vector<vector<int>> &ans, vector<int> &path, int idx) {
		if (idx == candidates.size()) return;
		if (target == 0) {
			ans.emplace_back(path);
			return;
		}
		dfs(candidates, target, ans, path, idx + 1);	// 直接跳过
		if (target - candidates[idx] >= 0) {	// 选择当前数
			path.emplace_back(candidates[idx]);
			dfs(candidates, target - candidates[idx], ans, path, idx);
			path.pop_back();
		}
	}
};

int main() {
	Solution s;
	vector<int> candidates0 = {2, 3, 6, 7};
	vector<int> candidates1 = {2, 3, 5};
	show2DVector(s.combinationSum(candidates0, 7));
	cout << ends << endl;
	show2DVector(s.combinationSum(candidates1, 8));
	return 0;
}