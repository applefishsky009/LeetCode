#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// 排序 + 双指针
// time: O(n^3)
// time: O(lgn)
class Solution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
		vector<vector<int>> ans;
		if (nums.size() < 4) return ans;
		sort(nums.begin(), nums.end());
		int len = nums.size();
		for (int i = 0; i < len - 3; ++i) {
			if (i > 0 && nums[i] == nums[i - 1]) continue;	// 去重
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;	// 剪枝 - 跳出
			if (nums[i] + nums[len - 3] + nums[len - 2] + nums[len - 1] < target) continue;	// 剪枝 - 不跳出
			for (int j = i + 1; j < len - 2; ++j) {
				if (j > i + 1 && nums[j] == nums[j - 1]) continue;	// 去重
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;	// 剪枝 - 跳出
				if (nums[i] + nums[j] + nums[len - 2] + nums[len - 1] < target) continue;	// 剪枝 - 不跳出
				int left = j + 1, right = len - 1;	// 双指针
				while (left < right) {
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum == target) {
						ans.push_back({nums[i], nums[j], nums[left], nums[right]});
						while (left < right && nums[left] == nums[left + 1])	// 去重
							++left;
						++left;
						while (left < right && nums[right] == nums[right - 1])	// 去重
							--right;
						--right;
					} else if (sum < target) {
						++left;
					} else {
						--right;
					}
				}
			}
		}
		return ans;
    }
};

int main() {
    Solution s1;
    // vector<int> num{1, 1, 0, -1, 0, -2, 2, 2};
    vector<int> num{1, 0, -1, 0, -2, 2};
    int target = 0;
    vector<vector<int>> result = s1.fourSum(num, target);
    show2DVector(result);
    return 0;
}