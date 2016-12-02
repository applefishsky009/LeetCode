#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//要求是就地算法，自己写的，
//思路是从后往前找第一个违背顺序的位置，然后找后边第一个大于这个数的数字，交换后对之后的数字升序排序
//比如75764321 ->找到5->找到6->互换->原先5的位置现在是6，这个位置后边的元素升序排序
class Solution
{
  public:
    void nextPermutation(vector<int> &nums)
    {
        const int n = nums.size() - 1;
        for (int pre = n - 1, cur = n; pre >= 0; --pre, --cur)
        {
            if (nums[pre] < nums[cur])
            { //找位置
                for (int locate = n; locate >= cur; --locate)
                {
                    if (nums[locate] > nums[pre])
                    { //找交换的元素
                        swap(nums[pre], nums[locate]);
                        auto p = nums.begin() + pre + 1;
                        sort(p, nums.end());
                        return;
                    }
                }
            }
        }
        int i = 0, j = n;
        while (i < j) //本身就是完美降序，返回完美升序
            swap(nums[i++], nums[j--]);
        return;
    }
};

// LeetCode, Next Permutation
// 时间复杂度 O(n) 空间复杂度 O(1)
// 使用迭代器的思路
class Solution1
{
  public:
    void nextPermutation(vector<int> &nums)
    {
        next_permutation(nums.begin(), nums.end());
    }
    template <typename BidiIt>
    bool next_permutation(BidiIt first, BidiIt last)
    {
        // Get a reversed range to simplify reversed traversal.
        const auto rfirst = reverse_iterator<BidiIt>(last); //制作反向迭代器！！！
        const auto rlast = reverse_iterator<BidiIt>(first);
        // Begin from the second last element to the first element.
        auto pivot = next(rfirst);
        // Find `pivot`, which is the first element that is no less than its
        // successor. `Prev` is used since `pivort` is a `reversed_iterator`.
        while (pivot != rlast && *pivot >= *prev(pivot))
            ++pivot;
        // No such elemenet found, current sequence is already the largest
        // permutation, then rearrange to the first permutation and return false.
        if (pivot == rlast)
        {
            reverse(rfirst, rlast);
            return false;
        }
        // Scan from right to left, find the first element that is greater than
        // `pivot`.
        auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
        swap(*change, *pivot);
        reverse(rfirst, pivot);
        return true;
    }
};

int main()
{
    Solution1 s1;
    vector<int> nums{7, 5, 6, 4, 3, 2, 1};
    show1DVector(nums);
    cout << endl;
    s1.nextPermutation(nums);
    show1DVector(nums);
    return 0;
}