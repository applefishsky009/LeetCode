#include <vector>
#include <iostream>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// dfs
// time: O(C_n—k*k)
// space: O(n)
class Solution0 {
  public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> ans;
		if (n < k) return ans;
		vector<int> path;
		dfs(ans, path, 1, 0, n, k);
		return ans;
	}
  private:
	void dfs(vector<vector<int>> &ans, vector<int> path, int start, int cur, int n, int k) {
		if (path.size() + n - start + 1 < k) return;	// 剪枝, 已有的数字和剩余的数字小于k个
		if (cur == k) {
			ans.push_back(path);
			return;
		}
		for (int i = start; i <= n; ++i) {	// 当前步选择哪一个数字, bfs的写法
			path.push_back(i);
			dfs(ans, path, i + 1, cur + 1, n, k);
			path.pop_back();
		}
	}
};

// dfs
// time: O(C_n—k*k)
// space: O(n)
class Solution1 {
  public:
	vector<vector<int>> combine(int n, int k) {
		vector<int> path;
		vector<vector<int>> ans;
		dfs(ans, path, 1, n, k);
		return ans;
	}
  private:
	void dfs(vector<vector<int>> &ans, vector<int> path, int cur, int n, int k) {
		if (path.size() + (n - cur + 1) < k) return;	// 剪枝, 已有的数字和剩余的数字小于k个
		if (cur == k) {
			ans.push_back(path);
			return;
		}
		path.push_back(cur);
		dfs(ans, path, cur + 1, n, k);	// 选择当前位置
		path.pop_back();	// 回溯
		dfs(ans, path, cur + 1, n, k);	// 不选择当前位置
	}
};

// 字典序法获得组合型枚举
// 康拓编码中取有k个1的编码, 可以获得两个规则, 则可以使用迭代的方式获得next
// 规则1: x的最低位为1, 如果末尾是t个连续的1, 则直接将倒数第t为的1和倒数第t + 1位的0替换即得到next(x)
// 规则2: x的最低位为0, 末尾有t个连续的0, 这t个连续的0之前有m个连续的1, 将倒数t + m位置的1和倒数t + m + 1位置的0对换, 然后将倒数t + 1到倒数t + m - 1位的1移动到最低位
// 但在工程实现中我们模拟了二进制1的移位方式获得next, 其实规则1是规则2在t=0时的特殊情况
// time: O(C_n—k*k)
// space: O(k)
class Solution {
  public:
	vector<vector<int>> combine(int n, int k) {
		vector<int> path;
		vector<vector<int>> ans;
		for (int i = 1; i <= k; ++i)	// 初始化为[1, k]
			path.push_back(i);
		path.push_back(n + 1);	// 哨兵
		int j = 0;
		while (j < k) {
			ans.emplace_back(path.begin(), path.begin() + k);
			j = 0;	// 实现规则2
			while (j < k && path[j] + 1 == path[j + 1]) {	// 寻找第一个path[j] + 1 != path[j + 1]的位置t
				path[j] = j + 1;	// 将[0, t - 1]区间内的每个位置重置为[1, t], 为最高位的1以为做准备
				++j;
			}
			++path[j];	// j是第一个path[j] + 1 != path[j + 1]的位置, 有gap的1移位, 走一步得到了next 
		}
		return ans;
	}
};

int main() {
	Solution s;
	show2DVector(s.combine(4, 2));
	return 0;
}
