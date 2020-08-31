#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// dfs - 先序访问
// time: O(n + m)
// space: O(n)
class Solution0 {
  public:
    bool canVisitAllRooms(vector<vector<int>> &rooms) {
        int len = rooms.size(), cnt = 0;
        vector<bool> visited(len, false);
        dfs(rooms, visited, cnt, 0);
        return cnt == len;
    }
  private:
    void dfs(vector<vector<int>> &rooms, vector<bool> &visited, int &cnt, int cur) {
        // if (visited[cur] == true) return;
        visited[cur] = true;
        ++cnt;
        for (int i = 0; i < rooms[cur].size(); ++i)
            if (!visited[rooms[cur][i]])  // 可以放在这里或者dfs入口
                dfs(rooms, visited, cnt, rooms[cur][i]);
    }
};

// bfs
// time: O(n + m)
// space: O(n)
class Solution {
  public:
    bool canVisitAllRooms(vector<vector<int>> &rooms) {
        int len = rooms.size(), cnt = 0;
        vector<bool> visited(len, false);
        queue<int> iq;
        visited[0] = true;
        iq.emplace(0);
        while (!iq.empty()) {
            int cur = iq.front(); iq.pop();
            ++cnt;
            for (auto &next : rooms[cur]) {
                if (!visited[next]) {   // 入队列前标识已访问
                    visited[next] = true;
                    iq.emplace(next);
                }
            }
        }
        return cnt == len;
    }
};

int main() {
    Solution s;
    // vector<vector<int>> rooms = {{1, 3}, {3, 0, 1}, {2}, {0}};   // 0
    vector<vector<int>> rooms = {{1}, {2}, {3}, {}};    // 1
    cout << s.canVisitAllRooms(rooms) << endl;
    return 0;
};