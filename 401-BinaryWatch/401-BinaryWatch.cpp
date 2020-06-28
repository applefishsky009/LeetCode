#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

class Solution {
  public:
    vector<string> readBinaryWatch(int num) {
        vector<vector<int>> hours(5, vector<int>());
        vector<vector<int>> minutes(7, vector<int>());
        vector<string> ans;
        calBitNums(hours, minutes);
        for (int i = 0; i <= num; i ++) {    // 小时有i位, 分钟为num-i位
            if (i >= hours.size() || hours[i].empty()) continue;
            for (int j = 0; j < hours[i].size(); j++) {
                string ansTmp = intToStr(hours[i][j]);
                ansTmp += ":";
                if (num - i >= minutes.size() || minutes.empty()) continue;
                for (int k = 0; k < minutes[num - i].size(); k++) {
                    string ansTmpM = intToStr(minutes[num - i][k]);
                    if (ansTmpM.size() == 1) ansTmpM = "0" + ansTmpM;
                    ans.push_back(ansTmp + ansTmpM);
                }
            }
        }
        return ans;
    }
  private:
    void calBitNums(vector<vector<int>> &hours, vector<vector<int>> &minutes) {
        for (int i = 0; i < 60; i++) {
            int bitnum = 0, itmp = i;
            while (itmp) {
                if (itmp & 1) bitnum ++;  
                itmp >>= 1;
            }
            minutes[bitnum].push_back(i);
            if (i < 12) hours[bitnum].push_back(i);
        }
    }
    string intToStr(int num) {
        string ans = "";
        while (num) {
            ans.push_back(num % 10 + '0');
            num /= 10;
        }
        reverse(ans.begin(), ans.end());
        return ans.size() == 0 ? "0" : ans;
    }
};

int main() {
    Solution s;
    // vector<string> ans = s.readBinaryWatch(1);
    // vector<string> ans = s.readBinaryWatch(0);
    vector<string> ans = s.readBinaryWatch(7);
    show1DVector(ans);
    return 1;
}