#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<vector<int>> result;
        vector<int> path;
        dfs(result, path, k, n, 0);
        return result;
    }

  private:
    void dfs(vector<vector<int>> &result, vector<int> &path,
             int sizeGap, int sumGap, int pre)
    {
        if (sumGap < 0 || sizeGap < 0)
            return;
        if (sizeGap == 0 && sumGap == 0)
        {
            result.push_back(path);
            return;
        }
        for (int i = pre + 1; i < 10; i++)
        {
            path.push_back(i);
            dfs(result, path, sizeGap - 1, sumGap - i, i);
            path.pop_back();
        }
    }
};

int main()
{
    Solution s1;
    int k = 3;
    int n = 9;
    vector<vector<int>> result = s1.combinationSum3(k, n);
    show2DVector(result);
    return 0;
}