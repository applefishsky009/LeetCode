#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dfs + 回溯
// time: O(S) 宽松的渐进上界(2^n*n)
// sapce: O(n)
class Solution0 {
  public:
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
		vector<int> path;
		vector<vector<int>> ans;
		sort(candidates.begin(), candidates.end());
		dfs(ans, path, candidates, target, 0);
		return ans;
	}
	void dfs(vector<vector<int>> &ans, vector<int> &path, vector<int> &candidates, int target, int start) {
		if (target == 0) {
			ans.push_back(path);
			return;
		}
		int pre = -1;
		for (int i = start; i < candidates.size(); ++i) {
			if (candidates[i] == pre) continue;	// 去重
			if (candidates[i] > target) break;	// 剪枝, 不用在递归入口处剪了
			pre = candidates[i];	// 记录bfs当前步的值, 当前步不要重复选择即可, 和前后步没有关系
			path.push_back(candidates[i]);
			dfs(ans, path, candidates, target - candidates[i], i + 1);
			path.pop_back();
		}
	}
};

// dfs + 回溯 + 记录
// time: O(S) 宽松的渐进上界(2^n*n)
// sapce: O(n)
class Solution {
  public:
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
		vector<int> path;
		vector<vector<int>> ans;
		vector<pair<int, int>> freq;
		sort(candidates.begin(), candidates.end());
		for (auto &num : candidates) {
			if (freq.empty() || num != freq.back().first)
				freq.emplace_back(num, 1);
			else
				++freq.back().second;
		}
		dfs(ans, path, freq, target, 0);
		return ans;
	}
	void dfs(vector<vector<int>> &ans, vector<int> &path, vector<pair<int, int>> &freq, int target, int start) {
		if (target == 0) {
			ans.push_back(path);
			return;
		}
		if (start >= freq.size() || freq[start].first > target) return;	// 剪枝
		dfs(ans, path, freq, target, start + 1);	// 不选当前数字
		int most = min(target / freq[start].first, freq[start].second);	// 当前数字可选的最大次数
		for (int i = 1; i <= most; ++i) {	// 选择当前数字
			path.push_back(freq[start].first);
			dfs(ans, path, freq, target - i * freq[start].first, start + 1);	// freq已经去重, step + 1即可
		}
		for (int i = 1; i <= most; ++i)
			path.pop_back();
	}
};

int main() {
	Solution s;
	vector<int> nums0 = {10, 1, 2, 7, 6, 1, 5};
	show2DVector(s.combinationSum2(nums0, 8));
	return 0;
}
