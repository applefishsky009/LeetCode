#include <iostream>
#include <unordered_set>
using namespace std;

class Solution
{
  public:
    bool isHappy(int n)
    {
        unordered_set<int> numSet;
        do
        {
            if (n == 1)
                return true;
            numSet.insert(n);
            n = segProcess(n);
        } while (numSet.find(n) == numSet.end());
        return false;
    }

  private:
    int segProcess(int n)
    {
        int ans = 0;
        int rmd = 0;
        while (n)
        {
            rmd = n % 10;
            ans += rmd * rmd;
            n /= 10;
        }
        return ans;
    }
};

//two pointers, fast and slow pointers.
class Solution1
{
  public:
    bool isHappy(int n)
    {
        int slow, fast;
        slow = fast = n;
        do
        {
            slow = digitSquareSum(slow);
            fast = digitSquareSum(fast);
            fast = digitSquareSum(fast);
        } while (slow != fast);
        return slow == 1 ? 1 : 0;
    }

  private:
    int digitSquareSum(int n)
    {
        int sum = 0, tmp;
        while (n)
        {
            tmp = n % 10;
            sum += tmp * tmp;
            n /= 10;
        }
        return sum;
    }
};

int main()
{
    Solution s1;
    int n = 19;
    cout << s1.isHappy(n) << endl;
    return 0;
}