#include <vector>
#include <cassert>
#include <E:\RylModule\vector.h>
using namespace std;

//recursive
class Solution
{
  public:
    int numIslands(vector<vector<char>> &grid)
    {
        assert(!grid.empty());
        const int n = grid.size();
        const int m = grid[0].size();
        vector<vector<bool>> mask(n, vector<bool>(m, 0));
        int area = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == '1' && mask[i][j] == false)
                {
                    dfs(grid, mask, i, j, n, m);
                    area++;
                }
        return area;
    }

  private:
    void dfs(const vector<vector<char>> &grid, vector<vector<bool>> &mask,
             int x, int y, const int &n, const int &m)
    {
        if (x >= n || x < 0 || y >= m || y < 0)
            return;
        if (grid[x][y] == '0' || mask[x][y] == true)
            return;
        mask[x][y] = true;
        dfs(grid, mask, x, y - 1, n, m);
        dfs(grid, mask, x, y + 1, n, m);
        dfs(grid, mask, x - 1, y, n, m);
        dfs(grid, mask, x + 1, y, n, m);
    }
};

//advice using global variable when nacessary.
//but this solution change grid! this is also recursive.
class Solution1
{
  public:
    int numIslands(vector<vector<char>> &grid)
    {
        if (grid.empty())
            return 0;
        n = grid.size();
        m = grid[0].size();
        int area = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == '1')
                {
                    dfs(grid, i, j);
                    area++;
                }
        return area;
    }

  private:
    int n;
    int m;
    void dfs(vector<vector<char>> &grid, int x, int y)
    {
        if (x >= n || x < 0 || y >= m || y < 0 || grid[x][y] == '0')
            return;
        grid[x][y] = '0';
        dfs(grid, x, y - 1);
        dfs(grid, x, y + 1);
        dfs(grid, x - 1, y);
        dfs(grid, x + 1, y);
    }
};

class Solution2
{
  public:
    int numIslands(const vector<vector<char>> &grid)
    {
        n = grid.size();
        if (n == 0)
            return 0;
        m = grid[0].size();

        vector<vector<int>> copyGrid(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i < n + 1; i++)
            for (int j = 1; j < m + 1; j++)
                copyGrid[i][j] = grid[i - 1][j - 1] - '0';

        onePass(copyGrid);
        parent.resize(numSet + 1, 0);
        nRank.resize(numSet + 1, 0);

        makeSet();
        int i = 0;
        while (i < edge.size())
        {
            int u = edge[i++];
            int v = edge[i++];

            u = findParent(u);
            v = findParent(v);
            if (u != v)
            {
                unionSet(u, v);
                numSet--;
            }
        }

        return numSet;
    }

  private:
    int n;
    int m;
    int numSet; //num of tree node
    vector<int> edge;
    vector<int> parent;
    vector<int> nRank;
    void onePass(vector<vector<int>> &copyGrid)
    {
        numSet = 0;
        for (int i = 1; i < n + 1; i++)
            for (int j = 1; j < m + 1; j++)
            {
                if (copyGrid[i][j] != 0)
                {
                    if (copyGrid[i][j - 1] != 0 || copyGrid[i - 1][j] != 0)
                    {
                        if (copyGrid[i][j - 1] != 0 && copyGrid[i - 1][j] != 0)
                        {
                            copyGrid[i][j] = min(copyGrid[i][j - 1], copyGrid[i - 1][j]);
                            if (copyGrid[i][j - 1] != copyGrid[i - 1][j]) //find edge
                            {
                                edge.push_back(copyGrid[i - 1][j]);
                                edge.push_back(copyGrid[i][j - 1]);
                            }
                        }
                        else
                            copyGrid[i][j] = copyGrid[i - 1][j] == 0 ? copyGrid[i][j - 1] : copyGrid[i - 1][j];
                    }
                    else
                        copyGrid[i][j] = ++numSet;
                }
            }
    }

    void makeSet()
    {
        for (int i = 1; i < numSet + 1; i++)
            parent[i] = i;
    }

    int findParent(int n) //path compression
    {
        if (parent[n] != n)
            parent[n] = findParent(parent[n]);
        return parent[n];
    }

    void unionSet(int parentX, int parentY) //union by rank
    {
        if (nRank[parentX] < nRank[parentY])
            parent[parentX] = parentY;
        else
        {
            parent[parentY] = parentX;
            if (nRank[parentX] == nRank[parentY])
                nRank[parentX]++;
        }
    }
};

int main()
{
    Solution2 s1;
    vector<vector<char>> grid =
        {{'1', '1', '1', '1', '1', '1', '1'},
         {'0', '0', '0', '0', '0', '0', '1'},
         {'1', '1', '1', '1', '1', '0', '1'},
         {'1', '0', '0', '0', '1', '0', '1'},
         {'1', '0', '1', '0', '1', '0', '1'},
         {'1', '0', '1', '1', '1', '0', '1'},
         {'1', '1', '1', '1', '1', '1', '1'}};
    cout << s1.numIslands(grid) << endl;
    return 0;
}