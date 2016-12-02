#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//递归版本比较简单，掌握四要素：1.递归出口；2.传递当前步数；3.当前步数可能值循环；4.回溯(因为是按值传递path)
class Solution
{
  private:
    const vector<string> digitMap{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void dfs(const string &digits, int cur, string path, vector<string> &result)
    {
		if (cur == digits.size())
		{
			result.push_back(path);
			return;
		}
		for (int i = 0; i < digitMap[digits[cur] - '0'].size(); ++i)
		{
			path.push_back(digitMap[digits[cur] - '0'][i]);
			dfs(digits, cur + 1, path, result);
			path.pop_back();
		}
    }
  public:
    vector<string> letterCombinations(const string &digits)
    {
		vector<string> result;
		string path;
		if (digits.empty())
			return result;
		dfs(digits, 0, path, result);
		return result;
    }
};

class Solution1
{
  private:
    const vector<string> digitMap{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  public:
    vector<string> letterCombinations(const string &digits)
    {
		if (digits.empty())
			return vector<string>();
		vector<string> result(1, "");
		for (auto d : digits)
		{
			const int n = result.size();
			const int m = digitMap[d - '0'].size();

			//重新分配足够的空间并复制正确的头
			result.resize(n * m);						  //当前数字步长m，一定扩容到m倍
			for (int i = 1; i < m; ++i)						  //第一个位置是原有合理位置，不用重新扩充
				copy(result.begin(), result.begin() + n, result.begin() + n * i); //扩充一倍
			//为当前步赋合理值
			for (int i = 0; i < m; ++i)
				{ //扩充的倍数循环
				auto begin = result.begin();
				//每一倍中填入相同新值
				for_each(begin + n * i, begin + n * (i + 1), [&](string &s) { s += digitMap[d - '0'][i]; });
			}
		}
		return result;
    }
};

int main()
{
    Solution1 s1;
    string digits = "23";
    vector<string> result = s1.letterCombinations(digits);
    show1DVector(result);
    return 0;
}