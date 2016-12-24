#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

//fraction must be repeating or limited.
class Solution
{
  public:
    string fractionToDecimal(int numerator, int denominator)
    {
        assert(denominator != 0);
        if (!numerator)
            return "0";

        //perfect process about interger
        string res;
        if (numerator < 0 ^ denominator < 0)
            res += '-';
        long numer = numerator < 0 ? (long)numerator * (-1) : (long)numerator;
        long denom = denominator < 0 ? (long)denominator * (-1) : (long)denominator;

        long integral = numer / denom;
        res += to_string(integral); //itoa->to_string is important
        long rmd = numer % denom;
        if (!rmd)
            return res;
        res += '.';
        rmd *= 10;
        unordered_map<long, long> mp;   //record reminder
        while (rmd)
        {
            long quotient = rmd / denom;
            if (mp.find(rmd) != mp.end())
            {
                res.insert(mp[rmd], 1, '(');
                res += ')';
                break;
            }
            mp[rmd] = res.size();
            res += to_string(quotient);
            rmd = (rmd % denom) * 10;
        }
        return res;
    }
};

int main()
{
    Solution s1;
    int numerator = 4;
    int denominator = 233;
    string result = s1.fractionToDecimal(numerator, denominator);
    cout << result << ends << result.size() << endl;
    return 0;
}