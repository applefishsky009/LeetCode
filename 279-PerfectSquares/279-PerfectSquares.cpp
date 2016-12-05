#include <cmath>
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

//设f[n]就是最少完全平方数，那么
//如果i == x^2 f[n] = 1;
//否则最大的x使得i^2<n，j = [1,i],f[i] = min(1+f[i-j^2]);
//注意带一个缓存,递归函数可以提供二级接口来匹配
class Solution
{
  public:
    int numSquares(int n)
    {
        vector<int> cache(n + 1, -1);
        return calSquares(n, cache);
    }

  private:
    int calSquares(int i, vector<int> &cache)
    {
        if (cache[i] != -1)
            return cache[i];
        int half = sqrt(i);
        if (i == half * half)
        {
            cache[i] = 1;
            return cache[i];
        }
        else
        {
            int min = INT_MAX;
            for (int j = 1; j <= half; ++j)
            {
                if (cache[i - j * j] == -1)
                    cache[i - j * j] = this->calSquares(i - j * j, cache);
                min = cache[i - j * j] + 1 < min ? cache[i - j * j] + 1 : min;
            }
            cache[i] = min;
        }
        return cache[i];
    }
};

int main()
{
    int n = 12;
    Solution s1;
    cout << s1.numSquares(n) << endl;
    return 0;
}