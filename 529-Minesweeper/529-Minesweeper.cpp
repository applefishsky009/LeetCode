#include <queue>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dfs
// time: O(n*m)
// space: O(n*m)
class Solution0 {
  public:
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click) {
        int n = board.size(), m = board[0].size();
        int x = click[0], y = click[1];
        if (board[x][y] == 'M') // 规则1 : 是'M'游戏结束
            board[x][y] = 'X';
        else
            dfs(board, x, y, n, m);
        return board;
    }
  private:
    int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
    int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
    void dfs(vector<vector<char>> &board, int x, int y, int n, int m) {
        int countM = 0;
        for (int i = 0; i < 8; ++i) {   // 统计邻域内的M
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
            countM += board[tx][ty] == 'M';
        }
        if (countM > 0) {   // 规则3
            board[x][y] = countM + '0';
        } else {    // 规则2
            board[x][y] = 'B';
            for (int i = 0; i < 8; ++i) {
                int tx = x + dx[i], ty = y + dy[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m || board[tx][ty] != 'E') continue;   // 这个写法没有visited, 重复搜索在这里被终止
                dfs(board, tx, ty, n, m);
            }
        }
    }
};

// bfs
// time: O(n*m)
// space: O(n*m)
class Solution {
  public:
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click) {
        int n = board.size(), m = board[0].size();
        int x = click[0], y = click[1];
        if (board[x][y] == 'M') // 规则1 : 是'M'游戏结束
            board[x][y] = 'X';
        else
            bfs(board, x, y, n, m);
        return board;
    }
  private:
    int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
    int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
    void bfs(vector<vector<char>> &board, int x, int y, int n, int m) {
        queue<pair<int, int>> iq;
        vector<vector<int>> visited(n, vector<int>(m, 0));
        iq.push({x, y});
        visited[x][y] = true;
        while (!iq.empty()) {
            int curX = iq.front().first, curY = iq.front().second, countM = 0;
            iq.pop();
            for (int i = 0; i < 8; ++i) {   // 统计邻域内的M
                int tx = curX + dx[i], ty = curY + dy[i];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
                countM += board[tx][ty] == 'M';
            }
            if (countM > 0) {   // 规则3
                board[curX][curY] = countM + '0';
            } else {    // 规则2
                board[curX][curY] = 'B';
                for (int i = 0; i < 8; ++i) {
                    int tx = curX + dx[i], ty = curY + dy[i];
                    if (tx < 0 || tx >= n || ty < 0 || ty >= m || board[tx][ty] != 'E' || visited[tx][ty]) continue;
                    iq.push({tx, ty});
                    visited[tx][ty] = true;
                }
            }
        }
    }
};

int main() {
    Solution s;
    vector<vector<char>> board = {
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'M', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'}};
    vector<int> click = {3, 0};
    show2DVector(s.updateBoard(board, click));
    return 0;
}