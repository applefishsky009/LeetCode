#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//449ms
class Solution
{
  public:
    int countPrimes(int n)
    {
        if (n < 2)
            return 0;
        vector<bool> prime(n, true);
        //prime[0] = false, prime[1] = false;
        //why sqrt(n)? consider that n = 25, for i = 7, 7*7 > 49,
        //but 2*7, 3*7 has already calculate when i = 2,3.so the start number of j is i*i.
        int falseCount = 2;
        for (int i = 2; i < sqrt(n); ++i)
            if (prime[i])
                for (int j = i * i; j < n; j += i)
                {
                    if (prime[j]) //j has not been count.
                        falseCount++;
                    prime[j] = false;
                }
        return n - falseCount;
    }
};

//289ms because lack of prime[j]
class Solution1
{
  public:
    int countPrimes(int n)
    {
        vector<bool> prime(n, true);
        prime[0] = false, prime[1] = false;
        for (int i = 0; i < sqrt(n); ++i)
            if (prime[i])
                for (int j = i * i; j < n; j += i)
                    prime[j] = false;
        return count(prime.begin(), prime.end(), true);
    }
};

//199ms!!
class Solution2
{
  public:
    int countPrimes(int n)
    {
        if (n <= 2)
            return 0;
        vector<bool> passed(n, false);
        int sum = 1;
        int upper = sqrt(n);
        for (int i = 3; i < n; i += 2)
            if (!passed[i])
            {
                sum++;
                if (i > upper) //avoid overflow. continue for count.
                    continue;
                for (int j = i * i; j < n; j += i)
                    passed[j] = true;   //not prime
            }
        return sum;
    }
};

int main()
{
    Solution s1;
    int n = 25;
    cout << s1.countPrimes(n) << endl;
    return 0;
}