#include <vector>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//Time Limited Exceeded, time:O(kn) space:O(1)
class Solution
{
  public:
    void rotate(vector<int> &nums, int k)
    {
        const int n = nums.size();
        int tmp;
        for (int i = 0; i < k; i++)
        {
            tmp = nums[n - 1];
            for (int j = n - 1; j > 0; j--)
                nums[j] = nums[j - 1];
            nums[0] = tmp;
        }
    }
};

//k%n
class Solution1
{
  public:
    void rotate(vector<int> &nums, int k)
    {
        const int n = nums.size();
        k %= n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), next(nums.begin(), k));
        reverse(next(nums.begin(), k), nums.end());
    }
};

class Solution2
{
  public:
    void rotate(vector<int> &nums, int k)
    {
        const int n = nums.size();
        k %= n;
        vector<int> numsCopy(nums);
        for (int i = 0; i < n; i++)
            nums[i] = numsCopy[(i + n - k) % n];
    }
};

//subSwap problem
class Solution3
{
  public:
    void rotate(vector<int> &nums, int k)
    {
        int n = nums.size();
        k %= n;
        if (n == 0 || k == 0)
            return;
        int i = 0;
        for (; k > 0; n -= k, k %= n) //the num need to swap > 0
            for (int j = 0; j < k; j++, i++)
                swap(nums[i], nums[i + n - k]);
    }
};

//3 elements -> 3 swap,confirm n swap.
class Solution4
{
  public:
    void rotate(vector<int> &nums, int k)
    {
        int n = nums.size();
        k %= n;
        if (n == 0 || k == 0)
            return;
        int cntRotate = 0;
        int cur = 0;
        int pre = cur;
        while (cntRotate < n)
        {
            do
            {
                swap(nums[cur], nums[pre]);
                pre = (pre + k) % n;
                cntRotate++;
            } while (pre != cur);
            cur = (cur + 1) % n;
            pre = cur;
        }
    }
};

int main()
{
    Solution4 s1;
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    int k = 4;
    s1.rotate(nums, k);
    show1DVector(nums);
    return 0;
}