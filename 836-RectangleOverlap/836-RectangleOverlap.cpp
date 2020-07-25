#include <cfloat>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 计算IOU的必备
// time: O(1)
// space: O(1)
class Solution {
  public:
    float isRectangleOverlap(vector<int> &rec1, vector<int> &rec2) {
        int x1 = max(rec1[0], rec2[0]);
        int y1 = max(rec1[1], rec2[1]);
        int x2 = min(rec1[2], rec2[2]);
        int y2 = min(rec1[3], rec2[3]);
        int w = x2 - x1, h = y2 - y1;
        if (w <= 0 || h <= 0)
            return 0;
        return 1;
        // int cross = w * h;
        // int area1 = (rec1[2] - rec1[0]) * (rec1[3] - rec1[1]);
        // int area2 = (rec2[2] - rec2[0]) * (rec2[3] - rec2[1]);
        // float iou = cross / (area1 + area2 - cross + FLT_MIN);
        // return iou; //return int -> float
    }
};

int main() {
    Solution s;
    vector<int> rec1 = {0, 0, 2, 2};
    // vector<int> rec2 = {0, 0, 2, 2};
    vector<int> rec2 = {1, 1, 3, 3};
    cout << s.isRectangleOverlap(rec1, rec2) << endl;
    return 0;
}