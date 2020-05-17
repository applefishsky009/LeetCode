#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <D:\Github\RylModule\vector.h>
using namespace std;

//reference to kahn algorithm
class Solution
{
  public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        int i = 0;
        vector<int> course;
        unordered_map<int, int> inDegree = calInDegree(numCourses, prerequisites);
        for (i = 0; i < numCourses; i++)    // O(V), 对于每个顶点，贪心学习尽可能多的可学习课程
            for (auto &x : inDegree)    // O(V), 遍历寻找可学习课程
                if (x.second == 0) {    // inDegree
                    course.push_back(x.first);  // V
                    for (auto &y : prerequisites)   // O(E), 入度维护 
                        if (y[1] == x.first)
                            inDegree[y[0]] --;
                    x.second --;
                }
        return course.size() == numCourses ? course : vector<int> {};
    }
  private:
    unordered_map<int, int> calInDegree(int numCourses, vector<vector<int>> &prerequisites) {
        int i = 0;
        unordered_map<int, int> inDegree;
        for (i = 0; i < numCourses; i++)
            inDegree[i] = 0;
        for (auto &x : prerequisites)
            inDegree[x[0]] ++;
        return inDegree;
    }
};

//BFS Solution， 这个解法的意义在于degree即是BFS中的step
class Solution2
{
  public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> degrees = compute_indegree(graph);
        queue<int> zeros;
        for (int i = 0; i < numCourses; i++)
            if (!degrees[i])
                zeros.push(i);
        vector<int> toposort;
        for (int i = 0; i < numCourses; i++) //O(V)
        {
            if (zeros.empty())
                return {};
            int zero = zeros.front();
            zeros.pop();
            toposort.push_back(zero);
            for (int neigh : graph[zero]) //O(E)
            {
                if (!--degrees[neigh])
                    zeros.push(neigh);
            }
        }
        return toposort;
    }

  private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre[1]].insert(pre[0]);
        return graph;
    }
    vector<int> compute_indegree(vector<unordered_set<int>> &graph)
    {
        vector<int> degrees(graph.size(), 0);
        for (auto neighbors : graph)
            for (int neigh : neighbors)
                degrees[neigh]++;
        return degrees;
    }
};

//DFS Solution
class Solution3
{
  public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> toposort;
        vector<bool> onpath(numCourses, false), visited(numCourses, false); // 表明正在搜索或已经完成搜索
        for (int i = 0; i < numCourses; i++)
            if (!visited[i] && dfs(graph, i, onpath, visited, toposort))    //该节点未访问，且通过该节点搜索到环
                return {};
        reverse(toposort.begin(), toposort.end());
        return toposort;
    }

  private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre[1]].insert(pre[0]);
        return graph;
    }
    // DFS 返回值表示该图中是否有环
    bool dfs(vector<unordered_set<int>> &graph, int node, vector<bool> &onpath, vector<bool> &visited, vector<int> &toposort)
    {
        if (visited[node])
            return false;
        onpath[node] = visited[node] = true;
        for (int neigh : graph[node])
            if (onpath[neigh] || dfs(graph, neigh, onpath, visited, toposort))  // 该节点构成环或者通过该节点搜索到环
                return true;
        toposort.push_back(node);
        return onpath[node] = false;    // 完成搜索，无环，return false
    }
};

int main()
{
    Solution2 s1;
    vector<vector<int>> prerequisites = {   vector<int>{1, 0},
                                            vector<int>{2, 0},
                                            vector<int>{3, 1},
                                            vector<int>{3, 2}};
    int numCourse = 4;
    vector<int> course = s1.findOrder(numCourse, prerequisites);
    cout << course.size() << endl;
    show1DVector(course);
    return 0;
}
