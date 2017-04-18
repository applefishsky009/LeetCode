#include <queue>
#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

//最简单易懂的解法，但是会bad_alloc
class Solution
{
  public:
    vector<pair<int, int>> getSkyline(const vector<vector<int>> &buildings)
    {
        vector<pair<int, int>> keyPoint;
        if (!buildings.size())
            return keyPoint;
        const int n = buildings[buildings.size() - 1][1];
        vector<int> segTree(n + 2, 0);
        for (auto x : buildings)
            for (int i = x[0]; i < x[1]; i++)
                segTree[i] = max(x[2], segTree[i]);
        //show1DVector(segTree);
        for (int i = 1; i < n + 2; i++)
            if (segTree[i] != segTree[i - 1])
                keyPoint.push_back(make_pair(i, segTree[i]));
        return keyPoint;
    }
};

class Solution1
{
  public:
    vector<pair<int, int>> getSkyline(vector<vector<int>> &buildings)
    {
        vector<pair<int, int>> res;
        int cur = 0, cur_X = 0, cur_H = -1, len = buildings.size();
        priority_queue<pair<int, int>> liveBlg; // first: height, second, end time
        while (cur < len || !liveBlg.empty())
        {                                     
            // if either some new building is not processed or live building queue is not empty
            cur_X = liveBlg.empty() ? buildings[cur][0] : liveBlg.top().second; // next timing point to process

            if (cur >= len || buildings[cur][0] > cur_X)
            {   //first check if the current tallest building will end before the next timing point
                // pop up the processed buildings, i.e. those  have height no larger than cur_H and end before the top one
                while (!liveBlg.empty() && (liveBlg.top().second <= cur_X))
                    liveBlg.pop();
            }
            else    //
            { // if the next new building starts before the top one ends, process the new building in the vector
                cur_X = buildings[cur][0];
                while (cur < len && buildings[cur][0] == cur_X) // go through all the new buildings that starts at the same point
                {                                               // just push them in the queue
                    liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
                    cur++;
                }
            }
            cur_H = liveBlg.empty() ? 0 : liveBlg.top().first; // outut the top one
            if (res.empty() || (res.back().second != cur_H))
                res.push_back(make_pair(cur_X, cur_H));
        }
        return res;
    }
};

int main()
{
    Solution1 s1;
    vector<vector<int>> buildings = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    vector<pair<int, int>> skyLine = s1.getSkyline(buildings);
    for (auto x : skyLine)
        cout << x.first << ends << x.second << endl;
    return 0;
}
