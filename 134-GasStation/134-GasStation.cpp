#include <vector>
#include <climits>
#include <cassert>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        assert(!gas.empty());
        const int n = gas.size();
        int locate = 0;
        bool canArri = true;
        int sum = 0;
        int minSum = 0;
        for (int i = 0; i < n; i++)
        {
            int curCost = gas[i] - cost[i];
            sum += curCost;
            locate = sum < minSum ? (i + 1) % n : locate;   //the most possible location is next the min sum
            minSum = sum < minSum ? sum : minSum;
        }
        if (sum < 0)    //total gas is less
            canArri = false;
        return canArri ? locate : -1;
    }
};

int main()
{
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 2, 1};
    Solution s1;
    cout << s1.canCompleteCircuit(gas, cost) << endl;
    return 0;
}