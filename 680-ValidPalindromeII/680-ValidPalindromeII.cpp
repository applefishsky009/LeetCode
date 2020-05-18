#include <vector>
#include <iostream>
#include <cmath>
#include <string>
// #include <D:\Github\RylModule\tree.h>
using namespace std;

class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[right] == s[left]) {
                left ++;
                right --;
            } else {
                return (isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1));
            }
        }
        return true;
    }
private:
    bool isPalindrome(string &s, int left, int right) {
        while (left < right)
            if (s[left++] != s[right--]) {return false;}
        return true;
    }
};

int main()
{
    Solution s;
    // string str = "abca"; // 1
    // string str = "ececabbacec"; // 1
    // string str = "ebcbbececabbacecbbcbe";    // 1
    // string str = "abcba";   // 1
    // string str = "abcca";   // 1
    string str = "abccbe";  //0
    cout << s.validPalindrome(str) << endl;
    return 0;
}