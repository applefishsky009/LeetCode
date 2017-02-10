#include <stack>
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_set>
using namespace std;

//undirected graph, but this problem is directed problem.
class Solution0
{
  public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<int> degree(numCourses, 0);
        const int n = prerequisites.size();
        for (int i = 0; i < n; i++)
        {
            degree[prerequisites[i].first]++;
            degree[prerequisites[i].second]++;
        }
        while (true)
        {
            bool hasCircle = false;
            for (int i = 0; i < n; i++)
            {
                if (degree[prerequisites[i].first] == 1 || degree[prerequisites[i].second] == 1)
                {
                    degree[prerequisites[i].first]--;
                    degree[prerequisites[i].second]--;
                    hasCircle = true;
                }
            }
            if (hasCircle == false)
                break;
        }
        for (int i = 0; i < numCourses; i++)
            if (degree[i] > 1)
                return false;
        return true;
    }
};

//directed graph, kahn Algorithm.
class Solution
{
  public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<int> degree(numCourses, 0);
        const int n = prerequisites.size();
        stack<int> vertexZero;
        for (int i = 0; i < n; i++) //only IN degree. O(E)
            degree[prerequisites[i].second]++;
        for (int i = 0; i < numCourses; i++) //O(V)
            if (degree[i] == 0)
                vertexZero.push(i);
        while (!vertexZero.empty()) //O(V)
        {
            int v = vertexZero.top();
            vertexZero.pop();
            for (int i = 0; i < n; i++) //O(E)
                if (prerequisites[i].first == v)
                    if (--degree[prerequisites[i].second] == 0)
                        vertexZero.push(prerequisites[i].second);
        }
        for (int i = 0; i < numCourses; i++) //O(V)
            if (degree[i] > 0)               //vertex remains, has circle.
                return false;
        return true;
    }
};

//DFS Algorithm
class Solution1
{
  public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        n = prerequisites.size();
        visited.resize(numCourses, false);
        onPath.resize(numCourses, false);
        for (int i = 0; i < numCourses; i++)
            if (!visited[i] && dfs(i, prerequisites, n))
                return false;
        return true;
    }

  private:
    vector<bool> visited;
    vector<bool> onPath;
    int n;
    //has circle?
    bool dfs(int thisVertex, vector<pair<int, int>> &prerequisites, const int &n)
    {
        if (visited[thisVertex])
            return false;
        onPath[thisVertex] = visited[thisVertex] = true;
        for (auto pre : prerequisites)
            if (pre.first == thisVertex &&
                (onPath[pre.second] ||
                 dfs(pre.second, prerequisites, n)))
                return true;
        onPath[thisVertex] = false;
        return false;
    }
};

//Graph - Linked List , fastest
class Solution2
{
  public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<bool> onpath(numCourses, false), visited(numCourses, false);
        for (int i = 0; i < numCourses; i++)
            if (!visited[i] && dfs_cycle(graph, i, onpath, visited))
                return false;
        return true;
    }

  private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
        return graph;
    }
    //has circle?
    bool dfs_cycle(vector<unordered_set<int>> &graph, int node, vector<bool> &onpath, vector<bool> &visited)
    {
        if (visited[node])
            return false;
        onpath[node] = visited[node] = true;
        for (int neigh : graph[node])
            if (onpath[neigh] || dfs_cycle(graph, neigh, onpath, visited))
                return true;
        return onpath[node] = false;
    }
};

class Solution3
{
  public:
    bool canFinish(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> degrees = compute_indegree(graph);
        for (int i = 0; i < numCourses; i++) //IN degree MAX = numCourses(Self - referential)
        {
            int j = 0;
            for (; j < numCourses; j++)
                if (!degrees[j])
                    break;
            if (j == numCourses)
                return false;
            degrees[j] = -1;           //find node j whose indegree = zero.
            for (int neigh : graph[j]) //delete node j and decrease indegree.
                degrees[neigh]--;
        }
        return true;
    }

  private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
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

int main()
{
    Solution1 s1;
    int numCourses = 3;
    vector<pair<int, int>> prerequisites = {make_pair(0, 1), make_pair(1, 2), make_pair(0, 2)};
    cout << s1.canFinish(numCourses, prerequisites) << endl;
    return 0;
};
