#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// Backtracking
// time: O(n*n!)
// space: O(n)
class Solution0 {
  public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
		vector<int> path;
		vector<vector<int>> ans;
		unordered_map<int, int> iumap;
		for (auto &x : nums) ++iumap[x];
		dfs(nums, ans, path, iumap);
		return ans;
	}
  private:
	void dfs(vector<int> &nums, vector<vector<int>> &ans, vector<int> &path, unordered_map<int, int> &iumap) {
		if (path.size() == nums.size()) {
			ans.emplace_back(path);
			return;
		}
		for (auto &p : iumap) {
			if (p.second == 0) continue;
			path.push_back(p.first);
			--p.second;
			dfs(nums, ans, path, iumap);
			++p.second;
			path.pop_back();
		}
	}
};

// Backtracking
// [未填入，未填入，未填入] 到 [填入，未填入，未填入]，再到 [填入，填入，未填入]，最后到 [填入，填入，填入] 的过程, 达到去重目的
// time: O(n*n!)
// space: O(n)
class Solution {
  public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
		vector<int> path;
		vector<vector<int>> ans;
		vis.resize(nums.size());
		sort(nums.begin(), nums.end());
		backtrack(nums, ans, 0, path);
		return ans;
	}
  private:
  	vector<int> vis;
	void backtrack(vector<int> &nums, vector<vector<int>> &ans, int idx, vector<int> &path) {
		if (idx == nums.size()) {
			ans.emplace_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); ++i) {
			if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) //剪枝, vis[i]表示这个数字被用过了,
				continue;	// 后面表示对于重复数集合一定是从左往右依次填入, 
			path.emplace_back(nums[i]);
			vis[i] = 1;
			backtrack(nums, ans, idx + 1, path);
			vis[i] = 0;
			path.pop_back();
		}
	}
};

int main() {
    Solution s1;
    vector<vector<int>> result;
    vector<int> nums = {1, 1, 2};
    result = s1.permuteUnique(nums);
	show2DVector(result);
    return 0;
}