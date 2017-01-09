#include <iostream>
using namespace std;

class Solution
{
  public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t ans = 0;
        for (int i = 0; i < 32; i++)
            if ((n >> i) & 0x1)           //get
                ans |= (0x1 << (31 - i)); //set
        return ans;
    }
};

class Solution1
{
  public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t ans = 0;
        for (int i = 0; i < 32; i++)
            ans |= (((n >> i) & 0x1) << (31 - i)); //get and set
        return ans;
    }
};

int main()
{
    Solution1 s1;
    uint32_t n = 43261596;
    cout << s1.reverseBits(n) << endl;
    return 0;
}