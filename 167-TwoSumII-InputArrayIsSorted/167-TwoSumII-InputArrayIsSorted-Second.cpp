#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// TP
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int len = numbers.size(), l = 0, r = len - 1;
        while (l < r) {
            if (numbers[l] + numbers[r] == target)
                return vector<int> {l + 1, r + 1};
            else if (numbers[l] + numbers[r] > target)
                --r;
            else    // (numbers[l] + numbers[r] < target)
                ++l;
        }
        return {};
    }
};

int main() {
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    show1DVector(s.twoSum(nums, 9));
    return 0;
}