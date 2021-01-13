#include <vector>
#include <string>
#include <iostream>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// time: O(n)
// space: O(1)
class Solution1 {
  public:
    vector<string> summaryRanges(vector<int> &nums) {
        vector<string> ans;
        if (nums.empty()) return ans;
        int i = 0, cnt = 0;
        long long pre = nums[0];    // 注意数据溢出
        nums.push_back(INT_MIN);    
        string cur_step = to_string(pre);
        for (i = 1; i < nums.size(); ++i) {
            if (nums[i] != pre + 1) {   // 不连续
                if (!cur_step.empty() && cnt > 0)   // 过去的连续长度大于1
                    cur_step = cur_step + "->" + to_string(pre);
                cnt = 0;    // 重置连续次数
                ans.push_back(cur_step);
                cur_step = to_string(nums[i]);
            } else {    // 统计连续次数
                cnt += 1;
            }
            pre = nums[i];
        }
        return ans;
    }
};

// Two Pointers
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<string> summaryRanges(vector<int> &nums) {
        vector<string> ret;
        int i = 0, n = nums.size();
        while (i < n) {
            int low = i;
            ++i;
            while (i < n && nums[i] == nums[i - 1] + 1) // 这种写法不用担心越界
                ++i;
            int high = i - 1;
            string temp = to_string(nums[low]);
            if (low < high) {
                temp.append("->");
                temp.append(to_string(nums[high]));
            }
            ret.push_back(move(temp));
        }
        return ret;
    }
};

int main() {
    Solution s1;
    // vector<int> nums = {0, 1, 2, 4, 5, 7};
    vector<int> nums = {0, 2, 3, 4, 6, 8, 9};
    // vector<int> nums = {-1};
    // vector<int> nums = {0};
    // vector<int> nums = {};
    show1DVector(s1.summaryRanges(nums));
    return 0;
}