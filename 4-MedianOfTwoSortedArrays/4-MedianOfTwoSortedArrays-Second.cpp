#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

// 要求O(log(m+n))二分搜索
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int i = 0, j = 0, left = 0, right = m;   // left, right表示划分小数组的idx
        int nums_im1 = 0, nums_i = 0, nums_jm1 = 0, nums_j = 0; // nums_im1, nums_i, nums_jm1, nums_j 分别表示 nums1[i-1], nums1[i], nums2[j-1], nums2[j]
        int median1 = 0, median2 = 0, total_left = (m + n + 1) / 2;   // median1：前一部分的最大值, median2：后一部分的最小值
        if (m > n)
            return findMedianSortedArrays(nums2, nums1);    // 确保nums2数组长度小于nums1,这样数组划分才不会过界
        while (left <= right) { // 前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1], 后一部分包含 nums1[i .. m-1] 和 nums2[j .. n-1]
            i = (left + right) / 2; // 先划分nums1小数组，确保划分后左右不为空
            j = total_left - i;    // 划分nums2,这里规定分割线左边元素多一个，奇偶表达式统一。
            nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);   // 在分割线左边
            nums_i = (i == m ? INT_MAX : nums1[i]); // 分割线右边
            nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
            nums_j = (j == n ? INT_MAX : nums2[j]);
            if (nums_im1 <= nums_j) { // 交叉满足,这里是否有等号无所谓
                left = i + 1;   // 分割线右移
                median1 = max(nums_im1, nums_jm1);  // 记录两个值
                median2 = min(nums_i, nums_j);
            }
            else  // nums1太大，分割线左移。
                right = i - 1;  // 注意二分查找的通用写法,计算Mid不+1,left必须+1,否则死循环
        }
        return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
    }
};

int main()
{
    Solution s1;
    // vector<int> nums1 = {};
    // vector<int> nums2 = {8};
    // vector<int> nums1 = {1, 3};
    // vector<int> nums2 = {2};
    // vector<int> nums1 = {1, 2, 4, 5};
    vector<int> nums2 = {3};
    vector<int> nums1 = {1, 2, 5, 6};
    // vector<int> nums2 = {3, 4};
    // vector<int> nums1 = {};
    // vector<int> nums2 = {2, 3};
    // vector<int> nums1 = {1, 2};
    // vector<int> nums2 = {3, 4};
    // vector<int> nums1 = {1, 2, 3};
    // vector<int> nums2 = {1, 2, 2};
    // vector<int> nums1 = {1, 2, 5};
    // vector<int> nums2 = {3, 4, 6, 7, 8, 9, 10};
    // vector<int> nums1 = {3};
    // vector<int> nums2 = {-2, -1};
    cout << s1.findMedianSortedArrays(nums1, nums2) << endl;
    return 0;
}