#include <cmath>
#include <vector>
#include <Algorithm>
#include <D:\Github\RylModule\vector.h>
using namespace std;

class Solution {
  public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int candies_max = 0, i = 0, len = candies.size();
        vector<bool> ans(len, 0);
        // for (auto &x : candies)
        //     candies_max = max(candies_max, x);
        candies_max = *max_element(candies.begin(), candies.end());
        for (i = 0; i < len; i++)
            ans[i] = candies[i] + extraCandies >= candies_max;
        return ans;
    }
};

int main() {
    Solution s;
    // int extraCandies = 3;
    // vector<int> candies = {2, 3, 5, 1, 3};  // 11101
    // int extraCandies = 1;
    // vector<int> candies = {4, 2, 1, 1, 2};  // 10000
    int extraCandies = 10;
    vector<int> candies = {12, 1, 12};  // 101
    show1DVector(s.kidsWithCandies(candies, extraCandies));
    return 1;
}