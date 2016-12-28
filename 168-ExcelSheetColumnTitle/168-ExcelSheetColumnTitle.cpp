#include <cmath>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    string convertToTitle(int n)
    {
        assert(n != 0);
        int i = -1;
        long lowBound = 1;
        do
        {
            i++;
            lowBound *= 26;
        } while (lowBound < n); //calculate the num of the bit.
        string result;
        for (; i >= 0; i--) //
        {
            long bitValue = pow(26, i); //may overflow
            result.push_back(n / bitValue + 'A' - 1);
            n = n % bitValue;
        }
        bool carry = false;
        for (int j = result.size() - 1; j >= 0; j--)
        {
            if (result[j] == 'A' - 1)
            {
                result[j] = 'Z';
                carry = true;
            }
            else if (carry == true)
            {
                result[j]--; //use carry. so set to false.
                carry = false;
                j++; //to judge this bit.
            }
            //no carry. no '@'. nothing to do.
        }
        return carry == true ? result.substr(1) : result;
        //result[0] can't be '@' because we calculate the num of bit.
        //result[0] is 'A' and carry = true. so it set to '@'. and then result[0] = 'Z', carry = true.
    }
};

class Solution1
{
  public:
    string convertToTitle(int n)
    {
        return n == 0 ? "" : convertToTitle(n / 26) + (char)(--n % 26 + 'A'); //--n execute firstly.
    }
};

int main()
{
    Solution1 s1;
    int n = 52;
    cout << s1.convertToTitle(n) << endl;
    return 0;
}