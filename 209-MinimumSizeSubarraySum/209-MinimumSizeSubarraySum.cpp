#include <vector>
#include <climits>
#include <numeric>
#include <iostream>
#include <E:\\RylModule\\vector.h>
using namespace std;

//O(n) Solution.
class Solution
{
  public:
    int minSubArrayLen(int s, vector<int> &nums)
    {
        int n = nums.size(), start = 0, sum = 0, minlen = INT_MAX; //no tail
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            while (sum >= s)
            {
                minlen = min(minlen, i - start + 1);
                sum -= nums[start++];
            }
        }
        return minlen == INT_MAX ? 0 : minlen;
    }
};

//O(nlog(n) Solution
class Solution1
{
  public:
    int minSubArrayLen(int s, const vector<int> &nums)
    {
        vector<int> sums = accumulateVector(nums);
        const int n = sums.size();
        int minLength = INT_MAX;
        for (int i = 1; i < n; i++)
        {
            if (sums[i] >= s)
            {
                int idex = upperBound(sums, 0, i, sums[i] - s);
                if (idex != -1)
                    minLength = min(minLength, i - idex + 1);
            }
        }
        return minLength == INT_MAX ? 0 : minLength;
    }

  private:
    vector<int> accumulateVector(const vector<int> &nums)
    {
        const int n = nums.size();
        vector<int> sums(n + 1, 0); //防止在upperBound中空指针的const引用，不用写条件判断
        for (int i = 1; i <= n; i++)
            sums[i] = sums[i - 1] + nums[i - 1];
        return sums;
    }
    //note reference binding to null pointer of type 'const value_type'
    int upperBound(const vector<int> &sums, int low, int high, int target)
    {
        while (low < high)
        {
            int m = low + ((high - low) >> 1);
            if (sums[m] > target)
                high = m;
            else
                low = m + 1;
        }
        return sums[high] > target ? high : -1; //不收敛，没有目标值
    }
};

int main()
{
    Solution2 s1;
    vector<int> nums = {1,2,3,4,5};
    int s = 15;
    cout << s1.minSubArrayLen(s, nums) << endl;
    return 0;
}
