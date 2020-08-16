#include <queue>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dfs
// time: O(n)
// space: O(n)
class Solution0 {
  public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
        int n = image.size(), m = image[0].size(), oldColor = image[sr][sc];
        vector<vector<int>> visited(n, vector<int>(m, 0));
        dfs(image, visited, sr, sc, newColor, n, m, oldColor);
        return image;
    }
  private:
    void dfs(vector<vector<int>> &image, vector<vector<int>> &visited, int sr, int sc, int newColor, int n, int m, int oldColor) {
        if (sr < 0 || sr >= n || sc < 0 || sc >= m || visited[sr][sc] || image[sr][sc] != oldColor) return;  // 越界或已访问过
        visited[sr][sc] = 1;    // 访问
        image[sr][sc] = newColor;
        dfs(image, visited, sr + 1, sc, newColor, n, m, oldColor);
        dfs(image, visited, sr - 1, sc, newColor, n, m, oldColor);
        dfs(image, visited, sr, sc + 1, newColor, n, m, oldColor);
        dfs(image, visited, sr, sc - 1, newColor, n, m, oldColor);
    }
};

// dfs - 优化
// time: O(n * m)
// space: O(n * m)  主要为栈空间的开销
class Solution1 {
  public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
        int n = image.size(), m = image[0].size(), oldColor = image[sr][sc];
        if (oldColor == newColor) return image;
        dfs(image, sr, sc, newColor, n, m, oldColor);
        return image;
    }
  private:
    void dfs(vector<vector<int>> &image, int sr, int sc, int newColor, int n, int m, int oldColor) {
        if (sr < 0 || sr >= n || sc < 0 || sc >= m || image[sr][sc] != oldColor) return;
        image[sr][sc] = newColor;
        dfs(image, sr + 1, sc, newColor, n, m, oldColor);
        dfs(image, sr - 1, sc, newColor, n, m, oldColor);
        dfs(image, sr, sc + 1, newColor, n, m, oldColor);
        dfs(image, sr, sc - 1, newColor, n, m, oldColor);
    }
};

// bfs
// time: O(n * m)
// space: O(n * m)  主要为队列的开销
class Solution {
  public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor) {
        int n = image.size(), m = image[0].size(), oldColor = image[sr][sc];
        if (oldColor == newColor) return image;
        queue<pair<int, int>> iq;
        iq.emplace(sr, sc);
        image[sr][sc] = newColor;
        while (!iq.empty()) {
            int x = iq.front().first, y = iq.front().second; iq.pop();
            for (int i = 0; i < 4; ++i) {
                int mx = x + dx[i], my = y + dy[i];
                if (mx < 0 || mx >= n || my <0 || my >= m || image[mx][my] != oldColor) continue;
                image[mx][my] = newColor;
                iq.emplace(mx, my);
            }
        }
        return image;
    }
  private:
    const int dx[4] = {1, 0, 0, -1};
    const int dy[4] = {0, 1, -1, 0};
};

int main() {
    Solution s;
    vector<vector<int>> image0 = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    vector<vector<int>> image1 = {{0, 0, 0}, {0, 1, 1}};
    show2DVector(s.floodFill(image0, 1, 1, 2));
    show2DVector(s.floodFill(image1, 1, 1, 1));
    return 0;
}