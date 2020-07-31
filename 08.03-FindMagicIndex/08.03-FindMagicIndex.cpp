#include <vector>
#include <iostream>
using namespace std;

// 朴素解法
// time: O(n)
// space: O(1)
class Solution1 {
  public:
    int findMagicIndex(vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i)
            if (i == nums[i])
                return i;
        return -1;
    }
};

// 分治 - 向右侧收敛
// time: O(n)
// space: O(n)
class Solution {
  private:
    int getAnswer(vector<int> &nums, int left, int right) {
        if (left > right) return -1;
        int mid = left + ((right - left) >> 1);
        int leftAnswer = getAnswer(nums, left, mid - 1);
        if (leftAnswer != -1) 
            return leftAnswer;
        else if (nums[mid] == mid)
            return mid;
        return getAnswer(nums, mid + 1, right);
    }
  public:
    int findMagicIndex(vector<int> &nums) {
        return getAnswer(nums, 0, (int)nums.size() - 1);
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {0, 2, 3, 4, 5};
    vector<int> nums1 = {1, 1, 1};
    cout << s.findMagicIndex(nums0) << endl;
    cout << s.findMagicIndex(nums1) << endl;
    return 0;
}
