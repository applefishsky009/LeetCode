#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// stack
// 单调栈常用来解决的问题
//      比当前元素更大的下一个元素
//      比当前元素更大的前一个元素
//      比当前元素更小的下一个元素
//      比当前元素更小的前一个元素
// time: O(n + m)
// space: O(n)
// https://coordinate.blog.csdn.net/article/details/86519771?utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~default-1.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~default-1.control
class Solution {
  public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int>& nums2) {
        int i = 0;
        stack<int> istk;    // 注意栈存下标
        vector<int> ans;
        unordered_map<int, int> imap;
        for (i = 0; i < nums2.size(); ++i) {
            while (!istk.empty() && nums2[i] > nums2[istk.top()]) {
                imap[nums2[istk.top()]] = i;   // 下标入栈
                istk.pop();
            }
            istk.push(i);
        }
        for (i = 0; i < nums1.size(); ++i) {
            if (imap.count(nums1[i]) != 0) {
                ans.push_back(nums2[imap[nums1[i]]]);  // 解析下标
            } else {
                ans.push_back(-1);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    // vector<int> nums1 = {4, 1, 2};
    // vector<int> nums2 = {1, 3, 4, 2};
    // vector<int> nums1 = {2, 4};
    // vector<int> nums2 = {1, 2, 3, 4};
    vector<int> nums1 = {1, 3, 5, 2, 4};
    vector<int> nums2 = {5, 4, 3, 2, 1};
    show1DVector(s.nextGreaterElement(nums1, nums2));
    return 0;
}