#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// src
// time: O(N + M)
// space O(N)
class Solution0 {
  public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        unordered_map<int, int> ium;
        for (auto &x : nums1)
            ium[x]++;
        for (auto &x : nums2)
            if (ium[x]-- > 0)
                ans.push_back(x);
        return ans;
    }
};

// 有序
// time: O(N + M)
// space O(K)
class Solution1 {
  public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        for (int i = 0, j = 0; i < nums1.size(); ++i) {
            while (nums2[j] < nums1[i]) // 找到大于i的第一个数
                j++;
            if (j < nums2.size() && nums2[j] == nums1[i])   // 区间寻找
                ans.push_back(nums2[j++]);
        }
        return ans;
    }
};

// nums1远小于nums2 N << M, 如果nums2太大不能一次读入内存只能用哈希表解法
// time: O(N + M)
// space O(N)
class Solution2 {
  public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) return intersect(nums2, nums1);
        vector<int> ans;
        unordered_map<int, int> ium;
        for (auto &x : nums1)
            ium[x]++;
        for (auto &x : nums2)
            if (ium[x]-- > 0)
                ans.push_back(x);
        return ans;
    }
};

// 无序-有序
// time: O(N + M)
// space O(K)
class Solution {
  public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> ans;
        for (int i = 0, j = 0; i < nums1.size(); ++i) {
            while (j < nums2.size() && nums2[j] < nums1[i]) // 找到大于i的第一个数
                j++;
            if (j < nums2.size() && nums2[j] == nums1[i])   // 区间寻找
                ans.push_back(nums2[j++]);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};
    vector<int> nums3 = {4, 9, 5};
    // vector<int> nums3 = {4, 9, 5, 4};
    vector<int> nums4 = {9, 4, 9, 8, 4};
    // vector<int> nums1 = {1, 1, 2, 2};
    // vector<int> nums2 = {2, 2};
    // vector<int> nums3 = {4, 5, 9};
    // vector<int> nums4 = {4, 4, 8, 9, 9};
    show1DVector(s.intersect(nums1, nums2));
    show1DVector(s.intersect(nums3, nums4));
    return 0;
}