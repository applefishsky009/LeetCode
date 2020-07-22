#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 考虑数组最后一个元素x, 在最小值右侧的元素小于等于x, 在最小值左侧的元素大于等于x, 
// time: O(lgn)
// space: O(1)
class Solution1 {
  public:
    int minArray(vector<int> &numbers) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) { // 左闭右闭区间
            while (l < r && numbers[l] == numbers[l + 1]) l++;  // exclude duplicated nums
            while (l < r && numbers[r] == numbers[r - 1]) r--;  // exclude duplicated nums
            int mid = l + ((r - l) >> 1);
            if (numbers[mid] > numbers[r]) //nums[mid] definitely is not the min
                l = mid + 1;
            else if (numbers[mid] < numbers[l]) { //nums[low] definitely is not the min
                // l++; // 经典二分的优化
                r = mid;
            } else  // mid是中位数则说明l-mid-r有序,返回l
                return numbers[l];
        }
        return numbers[l];
    }
};

// 将最后一个元素作为锚点
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    int minArray(vector<int> &numbers) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) { // 左闭右闭区间
            int mid = l + ((r - l) >> 1);
            if (numbers[mid] > numbers[r]) // 目标在右侧区间
                l = mid + 1;
            else if (numbers[mid] < numbers[r]) // 目标有右侧区间
                r = mid;
            else
                r--;
        }
        return numbers[l];
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 4, 5, 1, 2};    // 1
    vector<int> nums1 = {2, 2, 2, 0, 1};    // 0
    vector<int> nums2 = {2, 0, 1, 1, 1};    // 0
    vector<int> nums3 = {2, 1}; // 1
    vector<int> nums4 = {3, 1, 1};  // 1
    vector<int> nums5 = {4, 5, 6, 7, 0, 1, 2}; // 0
    vector<int> nums6 = {2, 0, 0, 0, 1, 2}; // 0
    vector<int> nums7 = {0, 0, 1, 1, 2, 0}; // 0
    cout << s.minArray(nums0) << endl;
    cout << s.minArray(nums1) << endl;
    cout << s.minArray(nums2) << endl;
    cout << s.minArray(nums3) << endl;
    cout << s.minArray(nums4) << endl;
    cout << s.minArray(nums5) << endl;
    cout << s.minArray(nums6) << endl;
    cout << s.minArray(nums7) << endl;
    return 0;
}
