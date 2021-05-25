#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

// HT
// time: O(n)
// space: O(n)
class Solution {
  public:
    int distributeCandies(vector<int> &candies) {
        unordered_set<int> iset;
        for (auto &candy : candies) {
            iset.insert(candy);
        }
        return min(iset.size(), candies.size() >> 1);
    }
};

int main() {
    Solution s;
    vector<int> candies = {1, 1, 2, 2, 2, 2};
    cout << s.distributeCandies(candies) << endl;
    return 0;
}