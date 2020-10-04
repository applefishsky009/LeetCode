#include <vector>
#include <unordered_map>
#include <algorithm>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// 考虑使用unordered_map，常数级查找
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
		vector<int> ans(2, 0);
		unordered_map<int, int> iumap;
		for (int i = 0; i < nums.size(); ++i)
			iumap[nums[i]] = i;
		for (int i = 0; i < nums.size(); ++i) {
			if (iumap.count(target - nums[i]) && iumap[target - nums[i]] != i) {
				ans[0] = i;	// 从前往后遍历, 一定是小的下标在前
				ans[1] = iumap[target - nums[i]];
				break;
			}
		}
		// if (ans[0] > ans[1])
			// swap(ans[0], ans[1]);
		return ans;
	}
};

int main() {
    Solution s1;
    vector<int> nums{3, 2, 4};
    int target = 6;
    vector<int> result = s1.twoSum(nums, target);
    show1DVector(result);
    return 0;
}