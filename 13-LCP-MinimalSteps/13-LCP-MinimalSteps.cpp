#include <queue>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 状态压缩DP - 计算所有特殊点(MOST)互相之间的最短距离 - d(j, i)可以O(1)查询
// d[i][j]表示第i个M到第j个M经过某一个O的最短距离, M的数量小于16, 使用一个16位的二进制数表示状态mask, 分为已触发集合和未触发集合
// m = 16, mask = 0000 1100 0001 0001的已触发集合为[1, 5, 11, 12]剩下的元素即为未触发集合, f(mask, i)表示在当前第i个M处, 触发状态为mask的最小步数
// 状态转移方程: f(mask, i) = min(f(mask xor 2exp(i), j) + d(j, i))  j 为已触发集合, j != i.
// 状态转移方程2: f(mask|2exp(i), j) = min{f(mask, i) + d(i, j)}    j 为已触发集合, j != i.
class Solution {
  public:
    int minimalSteps(vector<string> maze) {
        n = maze.size(), m = maze[0].size();
        vector<pair<int, int>> buttons, stones; // 机关, 石头
        int sx = 0, sy = 0, tx = 0, ty = 0; // 起点, 终点
        for (int i = 0; i < n; ++i) {   // 点初始化
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == 'M') buttons.push_back({i, j});
                if (maze[i][j] == 'O') stones.push_back({i, j});
                if (maze[i][j] == 'S') {sx = i; sy = j;}
                if (maze[i][j] == 'T') {tx = i; ty = j;}
            }
        }
        int nb = buttons.size(), ns = stones.size();
        vector<vector<int>> start_dist = bfs(sx, sy, maze);   // 从起点出发到特殊点的最短距离
        if (nb == 0) return start_dist[tx][ty]; // 没有机关, 直接从起点走到终点
        vector<vector<int>> dist(nb, vector<int>(nb + 2, -1));  // 从某个机关到其他机关 / 起点到终点的最短距离 (0, nb - 1)表示机关点之间的距离, (nb)表示该机关点到石头的距离, (nb + 1)表示从某个机关点到终点的距离
        vector<vector<vector<int>>> dd(nb); // 中间结果
        for (int i = 0; i < nb; ++i) {  // 从机关出发到特殊点的最短距离
            vector<vector<int>> d = bfs(buttons[i].first, buttons[i].second, maze);
            dd[i] = d;
            dist[i][nb + 1] = d[tx][ty]; // 从某个机关点到终点不需要拿石头的距离 
        }
        for (int i = 0; i < nb; ++i) {
            int tmp = -1;
            for (int k = 0; k < ns; ++k) {  // 从出发点到石头到机关点
                int mid_x = stones[k].first, mid_y = stones[k].second;
                if (dd[i][mid_x][mid_y] != -1 && start_dist[mid_x][mid_y] != -1)
                    if (tmp == -1 || tmp > dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y])  // 没到达过或不是最优, 更新最短距离
                        tmp = dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y];
            }
            dist[i][nb] = tmp;  // 从出发点到机关点的最短距离 - 包含拿石头
            for (int j = i + 1; j < nb; ++j) {  // 机关点之间的距离 - 途径石头
                int mn = -1;
                for (int k = 0; k < ns; ++k) {  // 遍历途径的所有石头
                    int mid_x = stones[k].first, mid_y = stones[k].second;
                    if (dd[i][mid_x][mid_y] != -1 && dd[j][mid_x][mid_y] != -1)
                        if (mn == -1 || mn > dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y]) // 没到达过或不是最优, 更新最短距离
                            mn = dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y];
                }
                dist[i][j] = dist[j][i] = mn;   // 机关点之间的距离 - 途径石头
            }
        }
        for (int i = 0; i < nb; ++i)    // 无法到达
            if (dist[i][nb] == -1 || dist[i][nb + 1] == -1)
                return -1;
        vector<vector<int>> idp(1 << nb, vector<int> (nb, -1)); // dp数组, -1代表没有遍历到, 状态机
        for (int i = 0; i < nb; ++i)    // 初始化, 从起点到第一个机关
            idp[1 << i][i] = dist[i][nb];
        for (int mask = 1; mask < (1 << nb); ++mask) {  // 机关点之间的状态转移
            for (int i = 0; i < nb; ++i) {  // 起始态
                if (mask & (1 << i)) {   // 当前dp合法
                    for (int j = 0; j < nb; ++j) {
                        if (!(mask & (1 << j))) {   // j不在mask里, 表示该状态未发生过, 进行转移
                            int next = mask | (1 << j); // 转移
                            if (idp[next][j] == -1 || idp[next][j] > idp[mask][i] + dist[i][j]) // 没到达过或非最优
                                idp[next][j] = idp[mask][i] + dist[i][j];
                        }
                    }
                }
            }
        }
        int ret = -1;
        int final_mask = (1 << nb) - 1; // 转移的最终态
        for (int i = 0; i < nb; ++i)    // 所有机关都要转移
            if (ret == -1 || ret > idp[final_mask][i] + dist[i][nb + 1])
                ret = idp[final_mask][i] + dist[i][nb + 1]; // 转移到最后一个机关, 从最后一个机关到达终点
        return ret;
    }
  private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int n, m;
    vector<vector<int>> bfs(int x, int y, vector<string> &maze) {   // 从(x, y)出发到所有特殊点的距离
        vector<vector<int>> ret(n, vector<int>(m, -1));
        ret[x][y] = 0;
        queue<pair<int, int>> iq;
        iq.push({x, y});
        while (!iq.empty()) {
            auto p = iq.front(); iq.pop();
            int x = p.first, y = p.second;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (inBound(nx, ny) && maze[nx][ny] != '#' && ret[nx][ny] == -1) {  // 没到达过
                    ret[nx][ny] = ret[x][y] + 1;
                    iq.push({nx, ny});       
                }
            }
        }
        return ret;
    }
    bool inBound(int x, int y) {    // 越界判断
        return x >= 0 && x < n && y >= 0 && y < m;
    }
};

int main() {
    Solution s;
    vector<string> maze0 = {"S#O", "M.#", "M.T"};
    vector<string> maze1 = {"S#O", "M.T", "M.."};
    // cout << s.minimalSteps(maze0) << endl;
    cout << s.minimalSteps(maze1) << endl;
    return 0;
}