#include <vector>
#include <string>
#include <E:\RylModule\vector.h>
using namespace std;

// LeetCode, Restore IP Addresses
// 时间复杂度 O(n^4)空间复杂度 O(n)
class Solution
{
  public:
    vector<string> restoreIpAddresses(const string &s)
    {
		vector<string> result;
		vector<string> ip; // 存放中间结果
		dfs(s, ip, result, 0);
		return result;
    }
    void dfs(string s, vector<string> &ip, vector<string> &result,
	     size_t start)
    {
		if (ip.size() == 4 && start == s.size())
		{ // 找到一个合法解
			result.push_back(ip[0] + '.' + ip[1] + '.' + ip[2] + '.' + ip[3]);
			return;
		}
		if (s.size() - start > (4 - ip.size()) * 3) //余下字符太多ip越界
			return;				    // 剪枝
		if (s.size() - start < (4 - ip.size()))     //余下字符太少不能填充所有ip
			return;				    // 剪枝
		int num = 0;
		for (size_t i = start; i < start + 3; i++)
		{ //当前步遍历，最多三个可能解
			num = num * 10 + (s[i] - '0');
			if (num < 0 || num > 255)
				continue; // 解范围违规，剪枝
			ip.push_back(s.substr(start, i - start + 1));
			dfs(s, ip, result, i + 1); //
			ip.pop_back();
			if (num == 0)
				break; //如果是单个0,允许dfs一次就退出，总之，允许单个,不允许前缀
		}
    }
};

int main()
{
    Solution s1;
    string s = "010010";
    vector<string> result = s1.restoreIpAddresses(s);
    show1DVector(result);
    return 0;
}