#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// HT
// time: O(m + n)
// space: O(m + n)
class Solution {
  public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        unordered_map<int, int> imap;
        vector<int> ans;
        for (auto &x : nums1) imap[x] = 1;
        for (auto &x : nums2)
            if (imap[x]-- > 0)
                ans.push_back(x);
        return ans;
    }
};

int main() {
    Solution s;
    // vector<int> nums1 = {1, 2, 2, 1};
    // vector<int> nums2 = {2, 2};
    vector<int> nums1 = {4, 9, 5};
    vector<int> nums2 = {9, 4, 9, 8, 4};
    show1DVector(s.intersection(nums1, nums2));
    return 0;
}
