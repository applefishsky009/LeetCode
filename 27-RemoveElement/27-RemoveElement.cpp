#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//Two Pointers
class Solution
{
  public:
    int removeElement(vector<int> &nums, int val)
    {
        if (nums.size() == 0)
            return 0;
        int cur = 0, pre = nums.size() - 1;
        while (cur < pre)
        {
            while (nums[pre] == val && pre > 0)
                --pre;
            while (nums[cur] != val && cur < nums.size() - 1)
                ++cur;
            if (cur < pre)
                swap(nums[cur], nums[pre]);
        }
        return (pre == 0 && nums[pre] == val) ? 0 : pre + 1; //pre表示不是val的最后一个元素,被迫中止返回0
    }
};

//Two Poionters
class Solution1
{
  public:
    int removeElement(vector<int> &nums, int target)
    {
        int index = 0;
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] != target)
                nums[index++] = nums[i];
        return index;
    }
};

class Solution2
{
  public:
    int removeElement(vector<int> &nums, int target)
    {
        return distance(nums.begin(), remove(nums.begin(), nums.end(), target)); //remove算法，不调整长度，移动target到末尾并返回新超尾
    }
};

int main()
{
    Solution2 s1;
    vector<int> nums{1, 1, 2, 3, 4, 5, 6, 7, 1, 1};
    show1DVector(nums);
    int val = 1;
    int length = s1.removeElement(nums, val);
    show1DVector(nums);
    cout << length << endl;
    return 0;
}