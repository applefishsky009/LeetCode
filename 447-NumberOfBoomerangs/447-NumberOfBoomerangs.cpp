#include <cmath>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// 二维矩阵 - cache - 用cache预计算
// time: O(n^2)
// space: O(n^2)
class Solution {
  public:
    int numberOfBoomerangs(vector<vector<int>> &points) {
        int n = points.size();
        vector<int> array_cache(n + 1, 0);
        for (int i = 2; i < n + 1; ++i) array_cache[i] = i * (i - 1);
        vector<vector<int>> dis_map(n, vector<int> (n, 0));
        for (int i = 0; i < n; ++i)
          	for (int j = i + 1; j < n; ++j)
				dis_map[i][j] = dis_map[j][i] = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			unordered_map<int, int> iumap;
			for (int j = 0; j < n; ++j) iumap[dis_map[i][j]]++;
			for (auto &x : iumap) ans += array_cache[x.second];
		}
		return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> points = {{0, 0}, {1, 0}, {2, 0}};
	cout << s.numberOfBoomerangs(points) << endl;
    return 0;
}