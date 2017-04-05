#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <E:\RylModule\vector.h>
using namespace std;

//reference to kahn algorithm
class Solution0
{
  public:
    vector<int> findOrder(int numCourses, const vector<pair<int, int>> &prerequisites)
    {
        unordered_map<int, int> inDegree = calInDegree(numCourses, prerequisites);
        vector<int> course;
        int deleteNum = numCourses;
        for (int i = 0; i < numCourses; i++) //O(V)
            for (auto &x : inDegree)         //O(V)
                if (x.second == 0)           //indegree is 0;
                {
                    course.push_back(x.first);   //delete this node
                    for (auto y : prerequisites) //search edge  //O(E)
                        if (y.second == x.first)
                            inDegree[y.first]--;
                    x.second = -1;
                    deleteNum--;
                }
        return deleteNum == 0 ? course : vector<int>{};
    }

  private:
    unordered_map<int, int> calInDegree(int numCourses, const vector<pair<int, int>> &prerequisites)
    {
        unordered_map<int, int> inDegree;
        for (int i = 0; i < numCourses; i++)
            inDegree[i] = 0;
        for (auto x : prerequisites)
            inDegree[x.first]++;
        return inDegree;
    }
};

//kahn algorithm
class Solution1
{
  public:
    vector<int> findOrder(int numCourses, const vector<pair<int, int>> &prerequisites)
    {
        vector<int> course;
        vector<int> degree(numCourses, 0);
        const int n = prerequisites.size();
        stack<int> vertexZero;
        for (int i = 0; i < n; i++) //only IN degree. O(E)
            degree[prerequisites[i].first]++;
        for (int i = 0; i < numCourses; i++) //O(V)
            if (degree[i] == 0)
                vertexZero.push(i);
        while (!vertexZero.empty()) //O(V)
        {
            int v = vertexZero.top();
            vertexZero.pop();
            course.push_back(v);
            for (int i = 0; i < n; i++) //O(E)
                if (prerequisites[i].second == v)
                    if (--degree[prerequisites[i].first] == 0)
                        vertexZero.push(prerequisites[i].first);
        }
        for (int i = 0; i < numCourses; i++) //O(V)
            if (degree[i] > 0)               //vertex remains, has circle.
                return vector<int>{};
        return course;
    }
};

//BFS Solution
class Solution
{
  public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites)
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

//DFS Solution
class Solution3
{
  public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> toposort;
        vector<bool> onpath(numCourses, false), visited(numCourses, false);
        for (int i = 0; i < numCourses; i++)
            if (!visited[i] && dfs(graph, i, onpath, visited, toposort))    //未访问过且可遍历，说明有环
                return {};
        reverse(toposort.begin(), toposort.end());
        return toposort;
    }

  private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
        return graph;
    }
    bool dfs(vector<unordered_set<int>> &graph, int node, vector<bool> &onpath, vector<bool> &visited, vector<int> &toposort)
    {
        if (visited[node])
            return false;
        onpath[node] = visited[node] = true;
        for (int neigh : graph[node])
            if (onpath[neigh] || dfs(graph, neigh, onpath, visited, toposort))
                return true;
        toposort.push_back(node);
        return onpath[node] = false;
    }
};

int main()
{
    Solution3 s1;
    vector<pair<int, int>> prerequisites = {make_pair(1, 0),
                                            make_pair(2, 0),
                                            make_pair(3, 1),
                                            make_pair(3, 2)};
    int numCourse = 4;
    vector<int> course = s1.findOrder(numCourse, prerequisites);
    //cout << course.size() << endl;
    show1DVector(course);
    return 0;
}
