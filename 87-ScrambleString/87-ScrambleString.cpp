#include <string>
#include <vector>
#include <iostream>
using namespace std;

//可以用记忆化搜索，一定可以用DP,
//设状态为f[n][i][j]，表示长度为n，起点为s1[i]和s2[j]两个字符串是否互为scramble
//状态转移方程f[n][i][j]} = (f[k][i][j] && f[n - k][i + k][j + k]) || (f[k][i][j + n - k] && f[n - k][i + k][j])
//原理参考：http://www.cnblogs.com/yuzhangcmu/p/4189152.html
class Solution
{
  public:
    bool isScramble(const string &s1, const string &s2)
    {
		const int N = s1.size();
		if (N != s2.size())
			return false;
		vector<vector<vector<bool>>> f(N + 1, vector<vector<bool>>(N, vector<bool>(N, false)));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				f[1][i][j] = s1[i] == s2[j]; //初始化，字符串长度1相等就是scramble
		for (int n = 2; n <= N; ++n)
		{ //动态规划，字符串长度增加，三维中的每一维，第一平面已经初始化，从第二平面开始
			for (int i = 0; i + n <= N; ++i)
			{ //从i开始索引，长度为n，不能越界
				for (int j = 0; j + n <= N; ++j)
				{
					for (int k = 1; k < n; ++k)
					{ 	//将要比较的字符串从string的k位置劈一刀，看是不是scramble
						//左侧k个char，右侧n-k个char
						//有点像n层神经网络，就是映射函数略难理解，两个条件映射才为true：
						//第一个条件：z轴slice某一点为true且互补平面，偏移原平面高度的点为true
						//第二个条件：z轴slice，y偏移互补平面高度点为true且互补平面x偏移原平面高度点为true
						if ((f[k][i][j] && f[n - k][i + k][j + k]) || //左侧和左侧，右侧和右侧是scramble
							(f[k][i][j + n - k] && f[n - k][i + k][j]))
						{ //右侧和左侧，左侧和右侧是scramble
							f[n][i][j] = true;
							break; //劈开的这一刀是scramble，没必要再劈
						}
					}
				}
			}
		}
		return f[N][0][0]; //长度为n,从s1[0],s2[0]开始
    }
};

int main()
{
    string s1 = "great";
    string s2 = "rgeat";
    Solution s;
    cout << s.isScramble(s1, s2) << endl;
    return 0;
}