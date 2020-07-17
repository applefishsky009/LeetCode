#include <vector>
#include <iostream>
using namespace std;

// 经典二分
class Solution {
  public:
	int searchInsert(vector<int> &nums, int target) {
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = l + ((r - l) >> 1);
			if (nums[mid] < target)
				l = mid + 1;
			else	// 找大于等于target的第一个数
				r = mid;
		}
		return nums[l] >= target ? l : l + 1;	// 是否找到大于等于target的第一个数
	}
};

int main() {
	Solution s;
	vector<int> nums = {1, 3, 5, 6};
	cout << s.searchInsert(nums, 5) << endl;
	cout << s.searchInsert(nums, 2) << endl;
	cout << s.searchInsert(nums, 7) << endl;
	cout << s.searchInsert(nums, 0) << endl;
	return 0;
}