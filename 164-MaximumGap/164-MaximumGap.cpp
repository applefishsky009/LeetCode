#include <set>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

//use set to sort
class Solution
{
  public:
    int maximumGap(vector<int> &nums)
    {
        if (nums.size() < 2) //notice nums.empty()
            return 0;
        set<int> numSet;
        for_each(nums.begin(), nums.end(), [&numSet](int x) { numSet.insert(x); }); //Lambda capture
        int maxGap = 0;
        for (auto p = next(numSet.begin()); p != numSet.end(); p++)
            maxGap = max(maxGap, *p - *prev(p));
        return maxGap;
    }
};

//bucket sort
class Solution1
{
  public:
    int maximumGap(vector<int> &num)
    {
        int sSize = num.size();
        int i = 0;
        int minV = 0, maxV = 0;
        int bucket_size, bucket_num, bucket_id;
        int maxGap = INT_MIN;
        int last_max;

        if (sSize > 1)
        {
            //cal max and min
            minV = maxV = num[0];
            for (i = 1; i < sSize; i++)
            {
                if (minV > num[i])
                    minV = num[i];
                else if (maxV < num[i])
                    maxV = num[i];
            }

            // the lower bound of the gap is (maxV - minV ) / (sSize - 1) in average.
            bucket_size = max(1, (maxV - minV) / (sSize - 1));
            bucket_num = (maxV - minV) / bucket_size + 1; //allocate one more bucket than bucket_size

            if (bucket_num <= 1) //all the nums is in one bucket. this almost means maxV = minV
                return (maxV - minV);   //so return 0; is also ok.
            vector<int> bucket_max(bucket_num, INT_MIN);
            vector<int> bucket_min(bucket_num, INT_MAX);
            vector<int> bucket_count(bucket_num, 0);

            //cal min and max in every bucket
            for (i = 0; i < sSize; i++)
            {
                bucket_id = (num[i] - minV) / bucket_size;
                bucket_count[bucket_id]++;
                bucket_min[bucket_id] = bucket_min[bucket_id] > num[i] ? num[i] : bucket_min[bucket_id];
                bucket_max[bucket_id] = bucket_max[bucket_id] < num[i] ? num[i] : bucket_max[bucket_id];
            }

            //maxGap must between two buckets, because there must be a gap larger than bucket_size
            last_max = minV;
            for (i = 0; i < bucket_num; i++)
            {
                if (bucket_count[i] > 0)
                {
                    maxGap = max(maxGap, bucket_min[i] - last_max);
                    last_max = bucket_max[i];
                }
            }
            return maxGap;
        }
        return 0;
    }
};

int main()
{
    Solution1 s1;
    vector<int> nums = {4, 5, 18, 7, 0, 1, 4};
    cout << s1.maximumGap(nums) << endl;
    return 0;
}