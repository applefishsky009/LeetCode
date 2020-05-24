#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    bool lemonadeChange(vector<int>& bills) {
        int i = 0, cnt = 0;
        vector<int> m = {5, 10, 20};
        unordered_map<int, int> money;
        for (auto &x : bills) {
            money[x]++;
            cnt = x - 5;
            if (cnt == 0)    // 不用找零
                continue;
            for (i = m.size() - 1; i >= 0; i--)  // 找零
                while (m[i] <= cnt && money[m[i]] > 0) {
                    cnt -= m[i];
                    money[m[i]] --;
                }
            if (cnt != 0)
                return false;
        }
        return true;
    }
};

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (auto &x : bills) {
            if (x == 5)
                five++;
            else if (x == 10) {
                if (five == 0)
                    return false;
                five--;
                ten++;
            } else {
                if (five > 0 && ten > 0) {
                    five --;
                    ten --;
                }else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s1;
    // vector<int> bills = {5, 5, 5, 10, 20};  // cookies
    // vector<int> bills = {5, 5, 5, 20};  // cookies
    // vector<int> bills = {5, 5, 20};  // cookies
    // vector<int> bills = {20};  // cookies
    vector<int> bills = {5, 10, 10, 20};  // cookies
    cout << s1.lemonadeChange(bills) <<endl;
    return 1;
}