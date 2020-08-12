#include <vector>
#include <iostream>
using namespace std;

bool isBadVersion(int version) {
    return version >= 4;
}

// binary search
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    int firstBadVersion(int n) {
        int l = 1, r = n;
        while (l < r) {
            int mid = l + ((r - l) >> 1);
            if (!isBadVersion(mid))
                l = mid + 1;
            else 
                r = mid;
        }
        return l;
    }  
};

int main() {
    Solution s;
    cout << s.firstBadVersion(5) << endl;
    return 0;
}
