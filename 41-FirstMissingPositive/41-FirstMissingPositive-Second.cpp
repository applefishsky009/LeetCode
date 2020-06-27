#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 桶排序, 原地交换
class Solution {
  public:
	int firstMissingPositive(vector<int>& nums) {
		const int len = nums.size();
		for (int i = 0; i < len; i++) {
			while (nums[i] != i + 1) { // 需要排序, 把当前的nums[i]放在他应该在的位置上
				if (nums[i] < 1 || nums[i] > len || nums[i] == nums[nums[i] - 1])
					break;
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for (int i = 0; i < len; i++)
			if (nums[i] != i + 1)
				return i + 1;
		return len + 1;
	}
};

int main() {
	Solution s;
	vector<int> nums0 = {1, 2, 0};	// 3
	vector<int> nums1 = {3, 4, -1, 1};	// 2
	vector<int> nums2 = {7, 8, 9, 11, 12};	// 1
	vector<int> nums3 = {1, 2, 3, 5, 8};	// 4
	cout << s.firstMissingPositive(nums0) << endl;
	cout << s.firstMissingPositive(nums1) << endl;
	cout << s.firstMissingPositive(nums2) << endl;
	cout << s.firstMissingPositive(nums3) << endl;
	return 1;
}
