#include <vector>
#include <string>
#include <E:\RylModule\vector.h>
using namespace std;

//这里不违反每一层一个dfs的要求，因为这道题比较特殊，用if...else...分离了
class Solution
{
  public:
    vector<string> generateParenthesis(int n)
    {
		vector<string> result;
		if (n == 0)
			return result;
		string path;
		dfs(result, path, n, 0, 0);
		return result;
    }

  private:
    void dfs(vector<string> &result, string path, const int n, int leftNum, int rightNum)
    {
		if (leftNum == n && rightNum == n)
		{
			result.push_back(path);
			return;
		}
		if (leftNum == rightNum)
		{ //只能进'('
			path.push_back('(');
			dfs(result, path, n, leftNum + 1, rightNum);
		}
		else
		{
			if (leftNum == n)
			{ //只能进')'
				path.push_back(')');
				dfs(result, path, n, leftNum, rightNum + 1);
			}
			else
			{ //都可以
				path.push_back('(');
				dfs(result, path, n, leftNum + 1, rightNum);
				path.pop_back();
				path.push_back(')');
				dfs(result, path, n, leftNum, rightNum + 1);
			}
		}
    }
};

//提升很小，递归出口时提前减枝的提升
class Solution1
{
  public:
    vector<string> generateParenthesis(int n)
    {
		vector<string> result;
		string path;
		if (n > 0)
			generate(n, path, result, 0, 0);
		return result;
    }
    void generate(int n, string &path, vector<string> &result, int l, int r)
    {
		if (l == n)
		{
			string s(path);
			result.push_back(s.append(n - r, ')')); //需要n-r个右括号
			return;
		}
		path.push_back('(');
		generate(n, path, result, l + 1, r);
		path.pop_back();
		if (l > r)
		{
			path.push_back(')');
			generate(n, path, result, l, r + 1);
			path.pop_back();
		}
    }
};

int main()
{
    Solution s1;
    int n = 3;
    vector<string> result = s1.generateParenthesis(n);
    show1DVector(result);
    return 0;
}