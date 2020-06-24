#include <cmath>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std;

class QuickSort {
  public:
	void quickQort(vector<int> &nums, int start, int end) {
		int q = 0;
		if (start < end) {
			q = partition(nums, start, end);
			quickQort(nums, start, q - 1);
			quickQort(nums, q + 1, end);
		}
	}
	void randomizedQuickSort(vector<int> &nums, int start, int end) {
		int q = 0;
		if (start < end) {
			q = randomizedPartition(nums, start, end);
			randomizedQuickSort(nums, start, q - 1);
			randomizedQuickSort(nums, q + 1, end);
		}
	}
  private:
	int partition(vector<int> &nums, int start, int end) {
		int i = start, j = start - 1;
		for (i = start; i < end; i++)
			if (nums[i] <= nums[end])
				swap(nums[i], nums[++j]);
		swap(nums[++j], nums[end]);
		return j;
	}
	int randomizedPartition(vector<int> &nums, int start, int end) {
		int dice_roll = 0;
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator(seed);
		uniform_int_distribution<int> distribution(start, end);
		dice_roll = distribution(generator);
		swap(nums[dice_roll], nums[end]);
		return partition(nums, start, end);
	}
};

class Solution {
  public:
	int threeSumClosest(vector<int>& nums, int target) {
		long long ans = INT_MAX;
		// sort(nums.begin(), nums.end());
		QuickSort qs;
		qs.randomizedQuickSort(nums, 0, nums.size() - 1);
		// qs.quickQort(nums, 0, nums.size() - 1);
		auto l = nums.begin();
		auto last = nums.end();
		for (l = nums.begin(); l < last - 2; l ++) {
			if (l > nums.begin() && *l == *(l - 1))
				continue;
			auto r = last - 1;
			auto m = l + 1;
			while (m < r) {
				long long x = *l + *m + *r;
				if (x == target)
					return target;
				if (x < target) {
					m++;
					if (abs(target - x) < abs(target - ans)) ans = x;
					while (m < r && *m == *(m - 1)) m++;
				}
				else if (x > target) {
					r--;
					if (abs(target - x) < abs(target - ans)) ans = x;
					while (r > m && *r == *(r + 1)) r--;
				}
			}
		}
		return (int)ans;
	}
};

int main() {
	Solution s;
	vector<int> nums0 = {-1, 2, 1, -4};
	vector<int> nums1 = {0, 2, 1, -3};
	cout << s.threeSumClosest(nums0, 1) << endl;
	cout << s.threeSumClosest(nums1, 1) << endl;
	return 1;
}