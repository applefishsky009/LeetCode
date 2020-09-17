#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// BS
// time: O(max(nlgm, nlgn))
// space: O(1)
class Solution0 {
  public:
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        int res = 0;
        int n = heaters.size();
        sort(heaters.begin(), heaters.end());
        for (auto &house : houses) {
            int left = 0, right = n;    // 二分查找不小于house的第一个供暖器
            while (left < right) {  // 左闭右开区间
                int mid = left + ((right - left) >> 1);
                if (house > heaters[mid]) left = mid + 1;   // 供暖器在房屋左侧
                else right = mid;   // 供暖器在房屋右侧
            }
            int dist1 = (right == 0) ? INT_MAX : abs(house - heaters[right - 1]);   // 该房屋距离左侧供暖器的距离
            int dist2 = (right == n) ? INT_MAX : abs(house - heaters[right]);   // 该房屋距离右侧供暖器的距离
            res = max(res, min(dist1, dist2));  // 保证该房屋供暖的最小供暖半径, 保证所有房屋供暖的最小供暖半径
        }
        return res;
    }
};

// BS
// time: O(max(nlgm, nlgn))
// space: O(1)
class Solution {
  public:
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        int res = 0;
        int n = heaters.size();
        sort(heaters.begin(), heaters.end());
        for (auto &house : houses) {
            // auto p = lower_bound(heaters.begin(), heaters.end(), house); //不小于
            auto p = upper_bound(heaters.begin(), heaters.end(), house);    //大于
            int dist1 = (p == heaters.begin()) ? INT_MAX : abs(house - *(p - 1));   // 该房屋距离左侧供暖器的距离
            int dist2 = (p == heaters.end()) ? INT_MAX : abs(house - *p);   // 该房屋距离右侧供暖器的距离
            res = max(res, min(dist1, dist2));  // 保证该房屋供暖的最小供暖半径, 保证所有房屋供暖的最小供暖半径
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> houses0 = {1, 2};
    vector<int> heaters0 = {1, 2};
    vector<int> houses1 = {1, 2, 3, 4};
    vector<int> heaters1 = {1};
    cout << s.findRadius(houses0, heaters0) << endl;  // 0
    cout << s.findRadius(houses1, heaters1) << endl;  // 3
    return 0;
}