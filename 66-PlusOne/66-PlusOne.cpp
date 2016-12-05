#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//其实头插不一定比反转慢
class Solution
{
  public:
    vector<int> plusOne(vector<int> &digits)
    {
        int carry = 1; //这是plus的1
        reverse(digits);
        for (int i = 0; i < digits.size(); i++)
        {
            digits[i] = digits[i] + carry;
            if (digits[i] == 10)
            {
                digits[i] = 0;
                carry = 1;
            }
            else
                carry = 0;
        }
        if (carry == 1)
            digits.push_back(1);
        reverse(digits);
        return digits;
    }

  private:
    void reverse(vector<int> &digits)
    {
        for (int i = 0; i < digits.size() / 2; i++)
            swap(digits[i], digits[digits.size() - 1 - i]);
    }
};

int main()
{
    vector<int> digits{1, 0, 0};
    Solution s1;
    s1.plusOne(digits);
    show1DVector(digits);
    return 0;
}