#include <vector>
#include <cassert>
#include <climits>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//Solution Space Overlap. So time limited.
class Solution
{
  public:
    int calculateMinimumHP(const vector<vector<int>> &dungeon)
    {
        const int m = dungeon.size();
        assert(m);
        const int n = dungeon[0].size();
        int minHP = INT_MIN;
        int singleHP = INT_MAX;
        calculateMinimumHP(dungeon, 0, 0, m, n, singleHP, minHP, 0);
        return minHP < 0 ? -minHP + 1 : 1;
    }

  private:
    void calculateMinimumHP(const vector<vector<int>> &dungeon,
                            int x, int y, const int &m, const int &n,
                            int singleHP, int &minHP, int cur)
    {
        if (x == m || y == n) //out of range
            return;
        int tmpHP = cur + dungeon[x][y];
        singleHP = min(tmpHP, singleHP);
        if (x == m - 1 && y == n - 1)
            minHP = max(minHP, singleHP); //return
        calculateMinimumHP(dungeon, x + 1, y, m, n, singleHP, minHP, tmpHP);
        calculateMinimumHP(dungeon, x, y + 1, m, n, singleHP, minHP, tmpHP);
    }
};

//cache->DP
class Solution1
{
  public:
    int calculateMinimumHP(const vector<vector<int>> &dungeon)
    {
        const int m = dungeon.size();
        //assert(m);
        const int n = dungeon[0].size();
        vector<vector<int>> f(m, vector<int>(n, 1));

        // < 0 means the energy knight will get is enough to conquer the remaining path.
        f[m - 1][n - 1] = dungeon[m - 1][n - 1] > 0 ? 1 : -dungeon[m - 1][n - 1] + 1;
        for (int i = m - 2; i >= 0; i--)
            f[i][n - 1] = f[i + 1][n - 1] - dungeon[i][n - 1] > 0 ? f[i + 1][n - 1] - dungeon[i][n - 1] : 1;
        for (int j = n - 2; j >= 0; j--)
            f[m - 1][j] = f[m - 1][j + 1] - dungeon[m - 1][j] > 0 ? f[m - 1][j + 1] - dungeon[m - 1][j] : 1;

        for (int i = m - 2; i >= 0; i--)
        {
            for (int j = n - 2; j >= 0; j--)
            {
                int a = f[i + 1][j] - dungeon[i][j] > 0 ? f[i + 1][j] - dungeon[i][j] : 1;
                int b = f[i][j + 1] - dungeon[i][j] > 0 ? f[i][j + 1] - dungeon[i][j] : 1;
                f[i][j] = min(a, b);
            }
        }
        return f[0][0];
    }
};

//@sidbai https://discuss.leetcode.com/topic/6912/c-dp-solution
class Solution2
{
  public:
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int M = dungeon.size();
        int N = dungeon[0].size();
        // hp[i][j] represents the min hp needed at position (i, j)
        // Add dummy row and column at bottom and right side
        vector<vector<int>> hp(M + 1, vector<int>(N + 1, INT_MAX));
        hp[M][N - 1] = 1;
        hp[M - 1][N] = 1;
        for (int i = M - 1; i >= 0; i--)
        {
            for (int j = N - 1; j >= 0; j--)
            {
                int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0];
    }
};

int main()
{
    Solution2 s1;
    vector<vector<int>> dungeon =
        {{-2, -3, 3},
         {-5, -10, 1},
         {10, 30, -5}};
    show2DVector(dungeon);
    cout << s1.calculateMinimumHP(dungeon) << endl;
    return 0;
}