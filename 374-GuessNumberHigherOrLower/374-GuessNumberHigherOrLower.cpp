#include <iostream>
using namespace std;

int pick = 4;

int guess(int num) {
    if (num == pick) return 0;
    else if (num < pick) return 1;
    else return -1;
}

// BS
// time: O(lgn)
// space: O(1)
class Solution0 {
  public:
    int guessNumber(int n) {
        int l = 1, r = n;
        while (l <= r) {    // 左闭右闭区间, 等于
            int mid = l + ((r - l) >> 1);
            int res = guess(mid);
            if (res == 0) return mid;
            else if (res == -1) r = mid - 1;
            else l = mid + 1;
        }
        return -1;  // 搜索完成还没找到-越界
    }
};

// TS
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    int guessNumber(int n) {
        int l = 1, r = n;
        while (l <= r) {    // 左闭右闭区间, 等于
            int mid1 = l + ((r - l) / 3);
            int mid2 = r - ((r - l) / 3);
            int res1 = guess(mid1);
            int res2 = guess(mid2);
            if (res1 == 0) return mid1;
            if(res2 == 0) return mid2;
            else if (res1 == -1) r = mid1 - 1;
            else if (res2 == 1) l = mid2 + 1;
            else {
                l = mid1 + 1;
                r = mid2 - 1;
            }
        }
        return -1;  // 搜索完成还没找到-越界
    }
};

int main() {
    Solution s;
    cout << s.guessNumber(4) << endl;
    return 0;
}