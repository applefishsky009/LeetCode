#include <set>
#include <iostream>
using namespace std;

//my Solution, 13.39%
class Solution
{
  public:
    int rangeBitwiseAnd(int m, int n)
    {
        set<char> bitSet;
        for (int i = 0; i < 32; i++)
            if ((m >> i) & 0x1)
                bitSet.insert(i);
        //if i is int, may overflow.
        for (long i = (long)m + (0x1 << (*bitSet.begin())); i <= n;)
        {
            for (auto p = bitSet.begin(); p != bitSet.end();)
            {
                if (((i >> *p) & 0x1) == 0)
                    p = bitSet.erase(p);
                else
                    p++;
            }
            if (bitSet.empty())
                break;
            //cal step to optimal,consider n = 11100100111000011100000000
            //i++ is too slow, so the step can be 000000000000000100000000
            int step = 0;
            while (((i >> step) & 0x1) == 0)
                step++;
            i += (0x1 << step);
        }
        int ans = 0;
        for (auto p = bitSet.begin(); p != bitSet.end(); p++) //set
            ans |= (0x1 << *p);
        return ans;
    }
};

//note that if m != n, there is at least two different continuous numbers, one is odd and one is even.
//so the lowest bit must be zero!
//Iterative
class Solution1
{
  public:
    int rangeBitwiseAnd(int m, int n)
    {
        if (m == 0) //this is not a must.
            return 0;
        int moveFactor = 1;
        while (m != n)
        {
            m >>= 1;
            n >>= 1;
            moveFactor <<= 1;
        }
        return m * moveFactor;
    }
};

//Recursive
class Solution2
{
  public:
    int rangeBitwiseAnd(int m, int n)
    {
        return (n > m) ? (rangeBitwiseAnd(m / 2, n / 2) << 1) : m;
    }
};

int main()
{
    Solution2 s1;
    int m = 2147483646;
    int n = 2147483647;
    cout << s1.rangeBitwiseAnd(m, n) << endl;
    return 0;
}