#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dp dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1 if matrix[i][j] == 1
// time: O(mn)
// space: O(mn)
class Solution {
  public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return 0;
        }
        int maxSide = 0;
        int rows = matrix.size(), cols = matrix[0].size();
        vector<vector<int>> idp(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0)
                        idp[i][j] = 1;
                    else
                        idp[i][j] = min(min(idp[i - 1][j], idp[i][j - 1]), idp[i - 1][j - 1]) + 1;  // w h edge
                }
                maxSide = max(maxSide, idp[i][j]);
            }
        }
        return maxSide * maxSide;
    }
};

int main() {
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'},
    };
    Solution s;
    cout << s.maximalSquare(matrix) << endl;
    return 0;
}
