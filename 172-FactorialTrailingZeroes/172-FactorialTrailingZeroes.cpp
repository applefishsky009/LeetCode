#include <iostream>
using namespace std;

class Solution
{
  public:
    int trailingZeroes(int n)
    {
        int fiveNum = 0;
        while (n)
        {
            n /= 5;
            fiveNum += n;
        }
        return fiveNum;
    }
};

int main()
{
    Solution s1;
    int n = 103;
    cout << s1.trailingZeroes(n) << endl;
    return 0;
}