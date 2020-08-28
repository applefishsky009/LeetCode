#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
  public:
    bool judgeCircle(string moves) {
        int lr = 0, ud = 0;
        for (auto &c : moves) {
            if (c == 'L') ++lr;
            else if (c == 'R') --lr;
            else if (c == 'U') ++ud;
            else if (c == 'D') --ud;
        }
        return lr == 0 && ud == 0;
    }
};

int main() {
    Solution s;
    cout << s.judgeCircle("UD") << endl;
    cout << s.judgeCircle("LL") << endl;
    return 0;
}