#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

// HT
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        unordered_map<char, int> smap;
        unordered_map<char, int> gmap;
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) bulls++;
            else {
                if (smap[guess[i]] != 0) {
                    cows++;
                    smap[guess[i]]--;
                } else {
                    gmap[guess[i]]++;
                }
                if (gmap[secret[i]] != 0) {
                    cows++;
                    gmap[secret[i]]--;
                } else {
                    smap[secret[i]]++;
                }
            }
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};

// HT
// time: O(n)
// space: O(1)
class Solution {
  public:
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        unordered_map<char, int> imap;
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) bulls++;
            else {
                if (imap[secret[i]]++ < 0) ++cows;  // 当前数小于0, 说明在之前的guess中出现过, 和secret当前的数匹配, secret中的数加1
                if (imap[guess[i]]-- > 0) ++cows;   // 当前数大于0, 说明在之前的secret中出现过, 和guess当前的数匹配, guess中的数加1
            }
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};

int main() {
    Solution s;
    string secret0 = "1807";
    string guess0 =  "7810";
    string secret1 = "1123";
    string guess1 =  "0111";
    cout << s.getHint(secret0, guess0) << endl; // 1A3B
    cout << s.getHint(secret1, guess1) << endl; // 1A1B
    return 0;
}
