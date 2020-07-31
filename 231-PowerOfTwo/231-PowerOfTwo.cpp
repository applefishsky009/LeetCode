#include <iostream>
using namespace std;

// Bit Manipulation
// time: O(1)
// space: O(1)
class Solution1 {
  public:
    bool isPowerOfTwo(int n) {
        for (int i = 0; i < 31; ++i)    // 最多在31位置, 即向右移动30位
            if ((1 << i) == n)
                return true;
        return false;
    }
};

// lowBit
// time: O(1)
// space: O(1)
class Solution2 {
  public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return lowBit(n) == n;
    }
  private:
    int lowBit(int x) {
        return x & (-x);
    }
};

// lowSet
// time: O(1)
// space: O(1)
class Solution {
  public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return lowSet(n) == 0;
    }
    int lowSet(int x) {
        return x & (x - 1);
    }
};

int main() {
    Solution s;
    cout << s.isPowerOfTwo(0) << endl;
    cout << s.isPowerOfTwo(1) << endl;
    cout << s.isPowerOfTwo(16) << endl;
    cout << s.isPowerOfTwo(218) << endl;
    cout << s.isPowerOfTwo(-2147483648) << endl;
    return 0;
}