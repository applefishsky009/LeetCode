#include <vector>
#include <iostream>
#include <cmath>
// #include <D:\Github\RylModule\tree.h>
using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
      int len = nums.size();
      int max = nums[0];  // 从左往右当前数组的最大值
      int min = nums[len - 1];  // 从右往左当前数组的最小值
      int l = 0, r = -1, i = 0;
      for(i = 0; i < len; i++){
          if(max > nums[i]) { // 说明nums[i]需要排序，更新右边界，更新后表示r右侧的值都比max大。
              r = i;
          }else {
              max = nums[i];
          }
          if(min < nums[len - i - 1]) { // 说明nums[len - i - 1]需要排序，更新左边界，更新后表示l左侧的值都比min小
              l = len - i - 1;
          }else {
              min = nums[len - i - 1];
          }
      }
      return r - l + 1;
    }
};

int main()
{
    Solution s;
    // vector<int> nums = {2, 6, 4, 8, 10, 9, 15}; // 5
    // vector<int> nums = {2, 6, 6, 8, 10, 9, 15}; // 2
    // vector<int> nums = {1, 2, 3, 4};  // 0
    // vector<int> nums = {1, 3, 2, 2, 2};  // 4
    // vector<int> nums = {1, 3, 2, 2, 2, 4, 4, 4, 4};  // 4
    // vector<int> nums = {1, 3, 3, 3, 3, 2};  // 4
    // vector<int> nums = {2, 3, 3, 2, 4};  // 3
    // vector<int> nums = {2, 6, 4, 8, 10, 9, 15};  // 5
    vector<int> nums = {1, 2, 4, 5, 3};  // 3
    cout << s.findUnsortedSubarray(nums) << endl;
    return 0;
}