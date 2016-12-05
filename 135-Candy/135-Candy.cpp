#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>

class Solution
{
  public:
    int candy(vector<int> &ratings)
    {
        int candyNum = 0;
        const int n = ratings.size();
        vector<int> forwardCandyNum(n, 1);
        for (int i = 0; i < n - 1; i++)
            if (ratings[i + 1] > ratings[i])
                forwardCandyNum[i + 1] = forwardCandyNum[i] + 1;

        vector<int> backwardCandyNum(n, 1);
        for (int i = n - 1; i > 0; i--)
            if (ratings[i] < ratings[i - 1])
                backwardCandyNum[i - 1] = backwardCandyNum[i] + 1;

        for (int i = 0; i < n; i++)
            candyNum += max(forwardCandyNum[i], backwardCandyNum[i]);
        return candyNum;
    }
};

int main()
{
    Solution s1;
    vector<int> ratings{1, 2, 3, 5, 4, 3, 2, 1};
    show1DVector(ratings);
    cout << s1.candy(ratings) << endl;
    return 0;
}