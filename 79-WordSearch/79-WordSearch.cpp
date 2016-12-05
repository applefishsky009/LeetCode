#include <vector>
#include <string>
#include <iostream>
using namespace std;

//有趣的问题，注意要记录遍历的路径
class Solution
{
  public:
    bool exist(const vector<vector<char>> &board, const string word)
    {
        if (board.size() == 0)
            return false;
        if (word.size() == 0)
            return true;
        const int m = board.size();
        const int n = board[0].size();
        vector<vector<bool>> map(m, vector<bool>(n, false)); //用vector模拟哈希表记录遍历路径
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (board[i][j] == word[0])
                    if (dfs(board, word, i, j, map, 0))
                        return true;
        return false;
    }

  private:
    bool dfs(const vector<vector<char>> &board, const string word,
             int row, int col, vector<vector<bool>> &map, int len)
    {
        if (len == word.size())
            return true;
        const int m = board.size();
        const int n = board[0].size();
        if (row < 0 || row >= m || col < 0 || col >= n)
            return false;
        if (word[len] != board[row][col])
            return false;
        if (map[row][col])
            return false;
        map[row][col] = true; //往前走
        bool ret = dfs(board, word, row - 1, col, map, len + 1) || dfs(board, word, row + 1, col, map, len + 1) || dfs(board, word, row, col - 1, map, len + 1) || dfs(board, word, row, col + 1, map, len + 1);
        //回溯
        //if (!ret) map[row][col] = false;  //保留下来的是最终路径，需要判断，比下面慢
        map[row][col] = false; //任何一次DFS最终都DFS成全false
        return ret;
    }
};

int main()
{
    Solution s1;
    vector<vector<char>> board = 
        {{'A', 'B', 'C', 'E'}, 
         {'S', 'F', 'C', 'S'}, 
         {'A', 'D', 'E', 'E'}};
    string word("ABCCFB");
    bool result = s1.exist(board, word);
    cout << result << endl;
    return 0;
}