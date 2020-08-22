#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// bit
// time: O(1)
// sapce: O(1)
class Solution0 {
  public:
    string toHex(int num) {
        string ans;
        for (int i = 0; i < 8; ++i) {
            int cur = num & 0xf;
            ans += iumap[cur];
            num >>= 4;
        }
        reverse(ans.begin(), ans.end());
        size_t pos = ans.find_first_not_of('0');
        return pos == string::npos ? "0" : ans.substr(pos);
    }
  private:
    unordered_map<int, char> iumap = {{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, 
                                     {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, 
                                     {8, '8'}, {9, '9'}, {10, 'a'}, {11, 'b'}, 
                                     {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'}};
};

// bit
// time: O(1)
// sapce: O(1)
class Solution {
  public:
    string toHex(int num) {
        string ans;
        int p = -1;
        string hex[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
        if (num == 0) return "0";
        else if (num < 0) p = 8;   // 负数左移8次
        while (num) {   // 正数左移直到0
            if (p == 0) break;
            int c = 0;
            c = (num & 0xf);
            ans = hex[c] + ans;
            num >>= 4;
            --p;
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.toHex(16) << endl;
    cout << s.toHex(26) << endl;
    cout << s.toHex(-1) << endl;
    return 0;
}