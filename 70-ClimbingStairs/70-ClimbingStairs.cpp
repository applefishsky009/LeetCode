#include <vector>
#include <iostream>
using namespace std;

//斐波那契，注意消除重复
class Solution
{
  public:
    int climbStairs(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        vector<int> stepCache(n + 1, 0);
        stepCache[0] = 1;
        stepCache[1] = 1;
        for (int i = 2; i <= n; i++)
            stepCache[i] = stepCache[i - 1] + stepCache[i - 2];
        return stepCache[n];
    }
};

int main()
{
    Solution s1;
    cout << s1.climbStairs(3) << endl;
    return 0;
}