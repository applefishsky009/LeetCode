#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// TP
// time: O(n)
// space: O(1)
class Solution {
  public:
    void reverseString(vector<char> &s) {
        if (s.empty()) return;
        for (int i = 0; i <= ((s.size() - 1) >> 1); ++i)
            swap(s[i], s[s.size() - 1 - i]);
    }
};

int main() {
    Solution s;
    vector<char> s0 = {'h', 'e', 'l', 'k', 'o'};
    vector<char> s1 = {'H', 'a', 'n', 'n', 'a', 'h'};
    vector<char> s2 = {'H'};
    show1DVector(s0);
    s.reverseString(s0);
    show1DVector(s0);
    show1DVector(s1);
    s.reverseString(s1);
    show1DVector(s1);
    show1DVector(s2);
    s.reverseString(s2);
    show1DVector(s2);
    return 0;
 }