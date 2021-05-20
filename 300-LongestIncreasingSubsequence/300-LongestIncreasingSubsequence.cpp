#include <vector>
#include <iostream>
using namespace std;

// Greedy + BS 每次在上升子序列中加上的那个数尽可能的小
// time: O(nlgn)
// space: O(n)
class Solution {
  public:
    int lengthOfLIS(vector<int> &nums) {
        int i = 0, left = 0, right = 0, mid = 0;
        vector<int> inum;
        inum.push_back(nums[0]);
        for (i = 1; i < nums.size(); ++i) { // O(n)
            if (nums[i] > inum.back()) {
                inum.push_back(nums[i]);
                continue;
            }
            left = 0, right = inum.size() - 1;
            while (left <= right) { // O(lgn)
                mid = left + ((right - left) >> 1);
                if (nums[i] > inum[mid]) {  // 插入值大于索引值, 插入位置一定在右侧
                    left = mid + 1;
                } else {    // 插入值小于索引值, 插入位置在左侧, 可能在mid位置
                    right = mid - 1;
                }
            }
            inum[left] = nums[i];
        }        
        return inum.size();
    }
};

int main() {
    Solution s;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << s.lengthOfLIS(nums) << endl;
    return 0;
}