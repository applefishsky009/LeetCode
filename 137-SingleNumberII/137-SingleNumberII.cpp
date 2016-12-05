#include <bitset>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    int singleNumber(vector<int> &nums)
    {
        assert(nums.size() != 0);
        vector<short> countBit(32, 0);
        for (auto x : nums)
            for (int i = 0; i < 32; i++)
                if (x & 1 << i)
                    countBit[i]++; //前边是低位，和数字反过来了
        for (auto &x : countBit)
            x %= 3;

        bitset<32> numBit;
        for (int i = 0; i < 32; i++) //bitset依然保持前边是低位
            numBit[i] = countBit[i];
        //cout << numBit << endl; //在cout和to_ulong的时候位会反
        int result = (int)(numBit.to_ulong());
        return result;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {1, 1, 1, 2, 2, 2, 3, 3, 3, 12, 12, 12, 76};
    cout << s1.singleNumber(nums) << endl;
    return 0;
}