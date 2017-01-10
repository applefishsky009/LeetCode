#include <iostream>
using namespace std;

class Solution
{
  public:
    int hammingWeight(uint32_t n)
    {
        int ans = 0;
        for (int i = 0; i < 32; i++)
            ans += (n >> i) & 0x1;
        return ans;
    }
};

class Solution1
{
  public:
    int hammingWeight(uint32_t n)
    {
        int ans = 0;
        for (int i = 0; i < 32; i++)
            if ((n >> i) & 0x1)
                ++ans;
        return ans;
    }
};

int main()
{
    Solution s1;
    uint32_t n = 11;
    cout << s1.hammingWeight(n) << endl;
    return 0;
}