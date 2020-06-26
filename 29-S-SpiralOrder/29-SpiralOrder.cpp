#include <vector>
#include <iostream>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// 按层模拟,递归写法
class Solution1 {
  public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
      	if (matrix.empty())
        	return vector<int> {};
      	int t = 0, b = matrix.size(), l = 0, r = 0;
		r = matrix[0].size();
      	vector<int> ans(b * r, 0);
		printMatrix(matrix, ans, l, r, t, b, 0);
      	return ans;
    }
  private:
	void printMatrix(vector<vector<int>>& matrix, vector<int>& ans, int l, int r, int t, int b, int idx) {
		int i = 0;
		for (i = l; i < r; i++)
			ans[idx++] = matrix[t][i];
		for (i = t + 1; i < b; i++)
			ans[idx++] = matrix[i][r - 1];
		if (b > t + 1)	
			for (i = r - 2; i >= l; i--)
				ans[idx++] = matrix[b - 1][i];
		if (r > l + 1)
			for (i = b - 2; i > t; i--) 
				ans[idx++] = matrix[i][l];
		if (r - 1 > l + 1 && b - 1 > t + 1)
			printMatrix(matrix, ans, l + 1, r - 1, t + 1, b - 1, idx);
	}
};

// 迭代写法
class Solution2 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty())
            return vector<int> {};
		int row = 0, column = 0, cur = 0;
        int rows = matrix.size(), columns = matrix[0].size();
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        vector<int> order(rows * columns, 0);
        while (left <= right && top <= bottom) {
            for (column = left; column <= right; column++)
                order[cur++] = matrix[top][column];
            for (row = top + 1; row <= bottom; row++)
                order[cur++] = (matrix[row][right]);
            if (top < bottom)
                for (column = right - 1; column > left; column--)
                    order[cur++] = matrix[bottom][column];
			if (left < right)
                for (row = bottom; row > top; row--)
                    order[cur++] = matrix[row][left];
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};

// 状态机计算坐标
#define within(x, lower, upper) (lower <= x && x <= upper)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) 
			return vector<int> {};
        int n = matrix.size(), m = matrix[0].size();
        int cnt(0), cur(0), cx(0), cy(-1);  // cnt 记录个数, cur 记录当前移动状态
		int tx(0), ty(0);
        vector<int> ans(m * n, 0); 
        while (cnt < m * n){
            tx = cx + dx[cur], ty = cy + dy[cur];
            if (within(tx, 0, n - 1) && within(ty, 0, m - 1) && matrix[tx][ty] != INF) {
                ans[cnt++] = matrix[tx][ty];
                matrix[tx][ty] = INF;
                cx = tx, cy = ty;
            }else {
				cur = (cur + 1) % 4; // 转向
			}
        }
        return ans;
    }
  private:
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	const int INF = -1e8;
};

int main() {
  	Solution s;
  	// vector<vector<int>> matrix = {	{1, 2, 3},
    //                             	{4, 5, 6},
    //                             	{7, 8, 9}};
	vector<vector<int>> matrix = {	{1, 2, 3, 4},
                                	{5, 6, 7, 8},
                                	{9, 10, 11, 12}};
	vector<int> ans = s.spiralOrder(matrix);
  	show1DVector(ans);
  	return 1;
}