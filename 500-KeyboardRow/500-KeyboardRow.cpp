#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// HT
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<string> findWords(vector<string> &words) {
        int i = 0, j = 0, flag = -1, cur_flag = -1;
        vector<unordered_set<char>> ikey_board = {
            {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
            'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',},
            {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',},
            {'z', 'x', 'c', 'v', 'b', 'n', 'm',
            'Z', 'X', 'C', 'V', 'B', 'N', 'M',},
        };
        vector<string> ans;
        for (i = 0; i < words.size(); ++i) {
            flag = -1;
            for (auto &c : words[i]) {
                cur_flag = -1;
                for (j = 0; j < ikey_board.size(); ++j) {
                    if (ikey_board[j].count(c)) {
                        cur_flag = j;
                        break;
                    }
                }
                if (flag == -1) {
                    flag = cur_flag;
                } else if (flag != cur_flag) {
                    flag = -1;
                    break;
                }
            }
            if (flag != -1) {
                ans.push_back(words[i]);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<string> words = {"Hello", "Alaska", "Dad", "Peace"};
    show1DVector(s.findWords(words));
    return 0;
}