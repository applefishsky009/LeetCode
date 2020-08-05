#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// BFS - 未做散列优化和访问优化 - v是课程数 - e是先修课程的要求数
// time: O(v + v * e)   
// space: O(v + v * e)
class Solution0 {
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        queue<int> iq;
        unordered_map<int, int> imap;
        for (int i = 0; i < numCourses; ++i)    // 入度初始化
            imap[i] = 0;
        for (auto &x: prerequisites)    // 入度计算
            ++imap[x[0]];
        for (auto p = imap.begin(); p != imap.end(); ++p)   // 队列初始化
            if (p->second == 0) 
                iq.push(p->first);
        while (!iq.empty()) {   // bfs
            int cur = iq.front(); iq.pop();
            for (auto &x : prerequisites)
                if (x[1] == cur)
                    if (--imap[x[0]] == 0)
                        iq.push(x[0]);
        }
        for (auto p = imap.begin(); p != imap.end(); ++p)   // 结果计算
            if (p->second != 0)
                return false;
        return true;
    }
};

// BFS - 散列和访问优化 - v是课程数 - e是先修课程的要求数
// time: O(v + e)   
// space: O(v + e)
class Solution1 {
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);   // 入度
        vector<vector<int>> edges(numCourses);  // 边
        for (auto &x: prerequisites) {    // 入度和散列计算
            edges[x[1]].push_back(x[0]);
            ++indegree[x[0]];
        }
        queue<int> iq;
        for (int i = 0; i < numCourses; ++i)    // 队列初始化
            if (indegree[i] == 0)
                iq.push(i);
        int visited = 0;        
        while (!iq.empty()) {   // bfs
            ++visited;
            int cur = iq.front(); iq.pop();
            for (auto &v : edges[cur])  // 散列优化后这里降低了访问消耗
                if (--indegree[v] == 0)
                    iq.push(v);
        }
        return visited == numCourses;
    }
};

// DFS - 可以从非0入度的节点开始, 访问过后, 指向他的节点会被跳过, 不会进行有环判断, 没有散列优化, 超时
// time: O(v + v * e)   
// space: O(v + v * e)
class Solution2 {
  private:
    bool dfs(int thisVertex, vector<vector<int>> &prerequisites, const int &n, vector<bool> &onPath, vector<bool> &visited) {
        if (visited[thisVertex])    // 跳过已访问过的节点
            return false;
        onPath[thisVertex] = visited[thisVertex] = true;   // 未访问过加入路径
        for (auto pre : prerequisites)  // 进行下一步访问
            if (pre[0] == thisVertex && (onPath[pre[1]] || dfs(pre[1], prerequisites, n, onPath, visited)))
                return true;    // 已在路径-有环, 或之后找到环
        onPath[thisVertex] = false; // 恢复路径
        return false;   // 正常完成访问- 无环
    }
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<bool> visited(numCourses, false);
        vector<bool> onPath(numCourses, false);
        for (int i = 0; i < numCourses; ++i)
            if (!visited[i] && dfs(i, prerequisites, n, onPath, visited))    // 从当前课程开始dfs
                return false;   // 未访问过开始访问, 但访问到环
        return true;
    }
};

// DFS - 可以从非0入度的节点开始, 访问过后, 指向他的节点会被跳过, 不会进行有环判断, 散列优化
// time: O(v + e)   
// space: O(v + e)
class Solution3 {
  private:
    bool dfs(int thisVertex, vector<vector<int>> &edges, const int &n, vector<bool> &onPath, vector<bool> &visited) {
        if (visited[thisVertex])    // 跳过已访问过的节点
            return false;
        onPath[thisVertex] = visited[thisVertex] = true;   // 未访问过加入路径
        for (auto pre : edges[thisVertex])  // 进行下一步访问
            if (onPath[pre] || dfs(pre, edges, n, onPath, visited))
                return true;    // 已在路径-有环, 或之后找到环
        onPath[thisVertex] = false; // 恢复路径
        return false;   // 正常完成访问- 无环
    }
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<bool> visited(numCourses, false);
        vector<bool> onPath(numCourses, false);
        vector<vector<int>> edges(numCourses);  // 边
        for (auto &x: prerequisites)    // 散列优化
            edges[x[1]].push_back(x[0]);
        for (int i = 0; i < numCourses; ++i)
            if (!visited[i] && dfs(i, edges, n, onPath, visited))    // 从当前课程开始dfs
                return false;   // 未访问过开始访问, 但访问到环
        return true;
    }
};

// 用栈实现的kahn算法 最快的算法
// time: O(v + e)   
// space: O(v + e)
class Solution {
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);   // 入度
        vector<vector<int>> edges(numCourses);  // 边
        stack<int> vertexZero;
        for (auto &x: prerequisites) {    // 入度和散列计算 O(E)
            edges[x[1]].push_back(x[0]);
            ++indegree[x[0]];
        }
        for(int i = 0; i < numCourses; ++i) // O(V)
            if (indegree[i] == 0)
                vertexZero.push(i);
        int visited = 0;    // 计数
        while (!vertexZero.empty()) {   // O(V)
            ++visited;
            int v = vertexZero.top(); vertexZero.pop();
            for (auto &x : edges[v])
                if (--indegree[x] == 0)
                    vertexZero.push(x);
        }
        return visited == numCourses;
    }
};

// 出度入度计算是否有环 - 超时
// time: O(max(v, e^2)   
// space: O(v)
class Solution5 {
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> degree(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); ++i) {    // O(E)
            ++degree[prerequisites[i][0]];
            ++degree[prerequisites[i][1]];
        }
        while (true) {  // O(E)
            bool deleteNode = false;    // 尝试删除节点
            for (int i = 0; i < prerequisites.size(); ++i) {    // O(E)
                if (degree[prerequisites[i][0]] == 1 || degree[prerequisites[i][1] == 1]) {
                    --degree[prerequisites[i][0]];
                    --degree[prerequisites[i][0]];
                    deleteNode = true;
                }
            }
            if (deleteNode == false)    // 没法删除了
                break;
        }
        for (int i = 0; i < numCourses; ++i)    // O(V)
            if (degree[i] > 1)
                return false;
        return true;
    }
};

int main() {
    Solution s;
    vector<vector<int>> prerequisites0 = {{1, 0}};  // 1
    vector<vector<int>> prerequisites1 = {{1, 0}, {0, 1}};  // 0
    vector<vector<int>> prerequisites2 = {{0, 1}};  // 1
    cout << s.canFinish(2, prerequisites0) << endl;
    cout << s.canFinish(2, prerequisites1) << endl;
    cout << s.canFinish(2, prerequisites2) << endl;
    return 0;
}