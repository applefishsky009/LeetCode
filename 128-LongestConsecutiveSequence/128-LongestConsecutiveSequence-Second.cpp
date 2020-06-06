#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// point1:不能使用while搜索左右边界,没有充分利用已存长度信息,超时
// point2:不能使用默认值构造,必须使用find,对key=0会失效
class Solution1 {
  public:
    int longestConsecutive(vector<int>& nums) {
        int max_cnt = 0, i = 0, left = 0, right = 0, search_left = 0, search_right = 0, right_idx = 0;
        unordered_map<int, int> cnt_map;
        for (i = 0; i < nums.size(); i++)  {
            right = left = nums[i];
            if (cnt_map.find(nums[i]) != cnt_map.end())  // 出现过
                continue;
            cnt_map[nums[i]]++;
            search_right = cnt_map.find(++right) != cnt_map.end();
            search_left = cnt_map.find(--left) != cnt_map.end();
            if (search_right) {// 向右搜索
                right_idx = nums[i] + cnt_map[right];
                cnt_map[nums[i]] = cnt_map[nums[i] + cnt_map[right]] = cnt_map[right] + cnt_map[nums[i]];
            }
            if (search_left) // 向左搜索
                cnt_map[nums[i]] = cnt_map[nums[i] - cnt_map[left]] = cnt_map[left] + cnt_map[nums[i]];
            if (search_right && search_left)    // 同时搜索过,更新右边界
                cnt_map[right_idx] = cnt_map[nums[i]];
            max_cnt = max(max_cnt, cnt_map[nums[i]]);
        }
        return max_cnt;
    }
};

class Solution2 {
  public:
    int longestConsecutive(vector<int>& nums) {
        int l = 1, i = 0;
        unordered_map<int, int> cnt_map;
        for (i = 0; i < nums.size(); i++) {
            if (cnt_map.find(nums[i]) != cnt_map.end())
                continue;
            cnt_map[nums[i]] = 1;
            if (cnt_map.find(nums[i] - 1) != cnt_map.end())
                l = max(l, mergeCluster(cnt_map, nums[i] - 1, nums[i]));
            if (cnt_map.find(nums[i] + 1) != cnt_map.end())
                l = max(l, mergeCluster(cnt_map, nums[i], nums[i] + 1));
        }
        return nums.empty() ? 0 : l;
    }
  private:
    int mergeCluster(unordered_map<int, int>& cnt_map, int left, int right) {
        int upper = right + cnt_map[right] - 1;
        int lower = left - cnt_map[left] + 1;
        int length = upper - lower + 1;
        cnt_map[upper] = cnt_map[lower] = length;
        return length;
    }
};

class Solution3 {
public:
    int longestConsecutive(vector<int>& nums) {
        int longestStreak = 0;
        unordered_set<int> num_set;
        for (const int& num : nums)
            num_set.insert(num);
        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;
                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }
                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return longestStreak;           
    }
};

class Solution {
public:
    unordered_map<int,int> a,b;
    int find(int x){
        return a.count(x) ? a[x] = find(a[x]) : x;
    }
    int longestConsecutive(vector<int>& nums) {
        for(auto i: nums)
            a[i] = i + 1;
        int ans = 0;
        for(auto i : nums){
            int y = find(i + 1);
            ans = max(ans, y - i);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};  // 4
    vector<int> nums2 = {}; // 0
    vector<int> nums3 = {4, 7, 9, 5, 8, 6}; // 6
    vector<int> nums4 = {9, 8, 7, 6, 5, 4}; // 6
    vector<int> nums5 = {4, 5, 6, 7, 8, 9}; // 6
    vector<int> nums6 = {0};    // 1
    vector<int> nums7 = {1, 3, 5, 2, 4}; // 5
    vector<int> nums8 = {1, 3, 5, 4, 2}; // 5
    cout << s.longestConsecutive(nums7) << endl;
    cout << s.longestConsecutive(nums1) << endl;
    cout << s.longestConsecutive(nums2) << endl;
    cout << s.longestConsecutive(nums3) << endl;
    cout << s.longestConsecutive(nums4) << endl;
    cout << s.longestConsecutive(nums5) << endl;
    cout << s.longestConsecutive(nums6) << endl;
    cout << s.longestConsecutive(nums8) << endl;
    return 1;
}