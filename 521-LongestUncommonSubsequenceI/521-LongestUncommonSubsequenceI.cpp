#include <string>
#include <iostream>
using namespace std;

// time: O(n)
// space: O(1)
class Solution {
public:
    int findLUSlength(string a, string b) {
        return a != b ? max(a.size(), b.size()) : -1;
    }
};

int main() {
    Solution s;
    string a = "aba";
    string b = "cdc";
    cout << s.findLUSlength(a, b);
    return 0;
}