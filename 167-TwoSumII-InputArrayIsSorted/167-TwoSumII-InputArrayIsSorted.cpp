#include <vector>
#include <iostream>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

//map
class Solution
{
  public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        const int n = numbers.size() - 1;
        assert(n > 1);
        unordered_map<int, int> numIndexMap;
        bool isEven = ~(target & 1);
        int maxEnd = target - numbers[0];
        int i = 0;
        for (i = 0; i < n; i++)
        {
            if (numbers[i] > maxEnd)
                break;
            if (numIndexMap.find(numbers[i]) == numIndexMap.end())
                numIndexMap[numbers[i]] = i + 1;
            else if (isEven && target >> 1 == numbers[i])
                return vector<int>() = {numIndexMap[numbers[i]], i + 1};
        }
        for (; i > 0; i--)
            if (numIndexMap.find(target - numbers[i]) != numIndexMap.end())
                return vector<int>() = {numIndexMap[target - numbers[i]], i + 1};
        return vector<int>() = {0, 0};
    }
};

//sorted, Two Pointers
class Solution1
{
  public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int low = 0;
        int high = numbers.size() - 1;
        while (high > low)
            if (numbers[high] + numbers[low] > target)
                high--;
            else if (numbers[high] + numbers[low] < target)
                low++;
            else
                return vector<int>() = {low + 1, high + 1};
        return vector<int>() = {0, 0};
    }
};

//sorted, Binary Search
class Solution2
{
  public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int low = 1;
        int high = numbers.size() - 1;
        int fixed = 0;
        while (true)
        {
            //find high that just numbers[fixed] + numbers[high] < target
            if (numbers[fixed] + numbers[fixed + 1] <= target)
            {
                int gap = target - numbers[fixed];
                int temp = binarySrearch(numbers, fixed, high, gap); //or use low, but this is easy to understand
                if (numbers[temp] == gap)
                    return vector<int>() = {fixed + 1, temp + 1};
                fixed = temp; //temp is ), so high = fixed - 1 is ];
                high = fixed - 1;
            }
            //find low that just numbers[low] + numbers[fixed] > target
            if (numbers[fixed] + numbers[fixed - 1] >= target)
            {
                int gap = target - numbers[fixed];
                int temp = binarySrearch(numbers, low, fixed - 1, gap); // or use high
                if (numbers[temp] == gap)
                    return vector<int>() = {temp + 1, fixed + 1};
                fixed = temp + 1; //temp is (, fixed is [. so low = fixed;
                low = fixed;
            }
            else
                break;
        }
        return vector<int>() = {0, 0};
    }

  private:
    //find the index that is just l||e than gap
    int binarySrearch(const vector<int> &numbers, int low, int high, int gap)
    {
        while (high > low + 1)
        {
            int mid = low + (high - low) / 2;
            if (numbers[mid] > gap)
                high = mid - 1;
            else if (numbers[mid] <= gap)
                low = mid;
        }
        return numbers[high] <= gap ? high : low;
    }
};

int main()
{
    Solution2 s1;
    vector<int> numbers =
        {
            12, 13, 23, 28, 43, 44, 59, 60, 61, 68,
            70, 86, 88, 92, 124, 125, 136, 168, 173, 173,
            180, 199, 212, 221, 227, 230, 277, 282, 306, 314,
            316, 321, 325, 328, 336, 337, 363, 365, 368, 370,
            370, 371, 375, 384, 387, 394, 400, 404, 414, 422,
            422, 427, 430, 435, 457, 493, 506, 527, 531, 538,
            541, 546, 568, 583, 585, 587, 650, 652, 677, 691,
            730, 737, 740, 751, 755, 764, 778, 783, 785, 789,
            794, 803, 809, 815, 847, 858, 863, 863, 874, 887,
            896, 916, 920, 926, 927, 930, 933, 957, 981, 997};
    int target = 542; //24,32
    vector<int> coordinate = s1.twoSum(numbers, target);
    show1DVector(coordinate);
    return 0;
}