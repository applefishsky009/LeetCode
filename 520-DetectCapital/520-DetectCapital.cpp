#include <string>
#include <iostream>

using namespace std;

// time: O(n)
// space: O(1)
class Solution {
public:
    bool detectCapitalUse(string word) {
        bool flag1 = true, flag2 = true, flag3 = true;
        for (int i = 0; i < word.size(); ++i) {
            if (isupper(word[i])) {
                if (0 == i) flag2 = false;
                else if (0 < i) {
                    if (true == flag3) flag3 = false;
                    if (true == flag2) flag2 = false;
                }
            } else if(islower(word[i])) {
                if (true == flag1) flag1 = false;
            }
        }
        return flag1 | flag2 | flag3;
    }
};

int main() {
    Solution s1;
    string word1 = "USA";
    string word2 = "leetcode";
    string word3 = "Google";
    string word4 = "FlaG";
    cout << s1.detectCapitalUse(word1) << endl;
    cout << s1.detectCapitalUse(word2) << endl;
    cout << s1.detectCapitalUse(word3) << endl;
    cout << s1.detectCapitalUse(word4) << endl;
    return 0;
}
