#include <vector>
#include <iostream>
using namespace std;

// Array
// time: O(n)
// space: O(1)
class Solution {
  public:
    int findMaxConsecutiveOnes(vector<int> &nums) {
        int imax = 0;
        int cnt = 0;
        for (auto x : nums) {
            if (x) {
                ++cnt;
            } else {
                imax = max(imax, cnt);
                cnt = 0;
            }
        }
        return max(imax, cnt);
    }
};

int main() {
    Solution s;
    // vector<int> nums = {1, 1, 0, 1, 1, 1};
    vector<int> nums = {1, 0, 1, 1, 0, 1};
    cout << s.findMaxConsecutiveOnes(nums) << endl;
    return 0;
}