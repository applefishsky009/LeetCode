#include <string>
#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<string>> partition(const string s)
    {
		vector<vector<string>> result; //深搜的结果
		vector<string> path;	   //深搜的路径
		DFS(result, path, s, 0);
		return result;
    }

  private:
    void DFS(vector<vector<string>> &result, vector<string> &path, const string &s, int start)
    {
		if (start == s.size()) //深搜到底，递归出口(return)
		{
			result.push_back(path);
			return;
		}
		for (int i = start; i < s.size(); i++)
		{
			string temp = s.substr(start, i - start + 1); //从start开始取i个深搜
			if (isPalindrome(temp))			  //当前层有符合条件
			{
				path.push_back(temp);	//存路径
				DFS(result, path, s, i + 1); //下一层深搜
				path.pop_back();	     //回溯
			}
		}
	}
	bool isPalindrome(const string &temp)
	{
		int i = 0;
		int j = temp.size() - 1;
		while (i < j && temp[i] == temp[j])
		{
			i++;
			j--;
		}
		return i >= j;
    }
};

int main()
{
    vector<vector<string>> result;
    string stringIn = "aab";
    Solution s1;
    result = s1.partition(stringIn);
    show2DVector(result);
    return 0;
}