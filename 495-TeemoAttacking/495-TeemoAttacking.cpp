#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int findPoisonedDuration(vector<int> &timeSeries, int duration) {
        int ans = 0;
        int pre = -duration;
        for (auto &x : timeSeries) {
            if (x > pre + duration) {
                ans += duration;
            } else {
                ans += x - pre;
            }
            pre = x;
        }
        return ans;
    }
};

int main() {
    vector<int> timeSeries1 = {1, 4};
    vector<int> timeSeries2 = {1, 2};
    Solution s;
    cout << s.findPoisonedDuration(timeSeries1, 2) << endl;
    cout << s.findPoisonedDuration(timeSeries2, 2) << endl;
    return 0;
}