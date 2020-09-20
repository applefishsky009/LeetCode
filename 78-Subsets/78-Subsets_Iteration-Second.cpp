#include <vector>
#include <algorithm>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// dfs
// time: O(n * 2^n)
// space: O(n)
class Solution0 {
  public:
    vector<vector<int>> subsets(vector<int> &nums) {
		vector<int> path;
		vector<vector<int>> ans;
		dfs(nums, 0, ans, path);
		return ans;
    }
  private:
	void dfs(vector<int> &nums, int step, vector<vector<int>> &ans, vector<int> &path) {
		if (step == nums.size()) {
			ans.push_back(path);
			return;
		}
		path.push_back(nums[step]);
		dfs(nums, step + 1, ans, path);
		path.pop_back();
		dfs(nums, step + 1, ans, path);
	}
};

// Iteration
// time: O(n * 2^n)
// space: O(n)
class Solution1 {
  public:
    vector<vector<int>> subsets(vector<int> &nums) {
		vector<int> path;
		vector<vector<int>> ans;
		int mask  = 1 << nums.size();
		for (int i = 0; i < mask; ++i)
			mask2path(nums, ans, path, i);
		return ans;
    }
  private:
	void mask2path(vector<int> &nums, vector<vector<int>> &ans, vector<int> &path, int mask) {
		path.clear();
		int in_path = false, idx = 0;
		while (mask) {
			in_path = mask & 1;
			mask >>= 1;
			if (in_path)
				path.push_back(nums[idx]);
			++idx;
		}
		ans.push_back(path);
	}
};

// Iteration
// time: O(n * 2^n)
// space: O(n)
class Solution {
  public:
    vector<vector<int>> subsets(vector<int> &nums) {
		vector<int> path;
		vector<vector<int>> ans;
		for (int mask = 0; mask < (1 << nums.size()); ++mask) {	// 二进制描述
			path.clear();
			for (int i = 0; i < nums.size(); ++i)	// 位数
				if (mask & (1 << i))	// 取当前位
					path.push_back(nums[i]);
			ans.push_back(path);
		}
		return ans;
    }
};

int main() {
    Solution s1;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = s1.subsets(nums); //结果按照二进制排序
    show2DVector(result);
    return 0;
}