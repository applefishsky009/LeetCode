#include <bitset>
#include <vector>
#include <iostream>
using namespace std;

//count every bit value - more than 50% OR single number II(137)
//if different, delete.
class Solution
{
  public:
    int majorityElement(vector<int> &nums)
    {
        int number = nums[0];
        int count = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] == number)
                count++;
            else if (count == 0)
                number = nums[i];
            else
                count--;
        }
        return number;
    }
};

class Solution1
{
  public:
    int majorityElement(const vector<int> &nums)
    {
        const int threshold = nums.size() / 2;
        vector<int> countBit(32, 0); //note: short will overflow!
        for (auto x : nums)
            for (int i = 0; i < 32; i++)
                if (x & (1 << i)) //count 1 int bit
                    countBit[i]++;
        bitset<32> numBit;
        for (int i = 0; i < 32; i++)
            if (countBit[i] > threshold)
                numBit[i] = 1;
            else
                numBit[i] = 0;
        return (int)(numBit.to_ulong());
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {3, 3, 4};
    cout << s1.majorityElement(nums) << endl;
    return 0;
}