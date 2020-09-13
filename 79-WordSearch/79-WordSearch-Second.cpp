#include <vector>
#include <string>
#include <iostream>
using namespace std;

// dfs 注意隐含的剪枝
// time: O(m * n * 3^L)
// space: O(m * n)
class Solution {
  public:
    bool exist(vector<vector<char>> &board, string word) {
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; ++j)
                if (dfs(board, word, 0, i, j, n, m))
                    return true;
        return false;
    }
  private:
    bool dfs(vector<vector<char>> &board, string &word, int cur, int x, int y, int n, int m) {
        if (cur == word.size()) return true;
        if (x < 0 || x >= n || y < 0 || y >= m || board[x][y] != word[cur]) return false;
        char res = board[x][y];
        board[x][y] = '#';
        bool ans = false;
        // ans = dfs(board, word, cur + 1, x + 1, y, n, m) || dfs(board, word, cur + 1, x, y + 1, n, m) || 
        // dfs(board, word, cur + 1, x - 1, y, n, m) || dfs(board, word, cur + 1, x, y - 1, n, m);  // 这种写法和以下带剪枝的才等价
        for (int k = 0; k < 4; ++k) {
            int tx = x + dx[k], ty = y + dy[k];
            ans |= dfs(board, word, cur + 1, tx, ty, n, m);
            if (ans) return true;
        }
        board[x][y] = res;
        return ans;
    }
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
};

int main() {
    Solution s;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'},
    };
    cout << s.exist(board, "ABCCED") << endl;   // 1
    cout << s.exist(board, "SEE") << endl;  // 1
    cout << s.exist(board, "ABCB") << endl; // 0
    return 0;
} 