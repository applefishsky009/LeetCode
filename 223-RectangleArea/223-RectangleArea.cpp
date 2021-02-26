#include <iostream>
#include <algorithm>
using namespace std;

// Math
// time: O(1)
// space: O(1)
class Solution {
  public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int x1 = max(A, E);
        int y1 = max(B, F);
        int x2 = min(C, G);
        int y2 = min(D, H);
        int iarea = (x1 >= x2 || y1 >= y2) ? 0 : (x2 - x1) * (y2 - y1);
        return (C - A) * (D - B) - iarea + (G - E) * (H - F) ; // 防止数值越界
    }
};

int main() {
    Solution s;
    // cout << s.computeArea(-3, 0, 3, 4, 0, -1, 9, 2) << endl;
    cout << s.computeArea(0, 0, 50000, 40000, 0, 0, 50000, 40000) << endl;
    return 0;
}