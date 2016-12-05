#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

#define NUM 3

class Solution
{
  public:
    vector<int> grayCode(int n)
    {
        if (n <= 0)
            return vector<int>(1, 0);
        int totleNum = pow(2, n);
        vector<int> allNum(totleNum, 0);
        for (int startCopy = 1; startCopy <= n; startCopy++)
        {
            int lastEnd = pow(2, startCopy - 1) - 1;
            //注意各种Copy方法传递的是超尾,与容器是不是就地没有关系
            reverse_copy(allNum.begin(), allNum.begin() + lastEnd + 1, allNum.begin() + lastEnd + 1);
            for (int addHighBit = lastEnd + 1; addHighBit <= lastEnd + lastEnd + 1; addHighBit++)
                allNum[addHighBit] += pow(2, startCopy - 1);
        }
        return allNum;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = s1.grayCode(NUM);
    show1DVector(nums);
    return 0;
}