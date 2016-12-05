#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm> //vector的sort要用
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> subsets(vector<int> &S)
    {
		sort(S.begin(), S.end()); //输出要求有序
		vector<vector<int>> result;
		vector<int> path;
		subsets(S, path, 0, result);
		return result;
    }

  private:
    static void subsets(const vector<int> &S, vector<int> &path, int step,
			vector<vector<int>> &result)
    {
		if (step == S.size())
		{
			result.push_back(path);
			return;
		}
		//不??? S[step]
		subsets(S, path, step + 1, result);
		//??? S[step]
		path.push_back(S[step]);
		subsets(S, path, step + 1, result);
		path.pop_back();
    }
};

class Solution1
{
  public:
    vector<vector<int>> subsets(vector<int> &S)
    {
		sort(S.begin(), S.end()); //输出要求有序
		vector<vector<int>> result;
		vector<bool> selected(S.size(), false);
		subsets(S, selected, 0, result);
		return result;
    }

  private:
    static void subsets(const vector<int> &S, vector<bool> &selected, int step,
			vector<vector<int>> &result)
    {
		if (step == S.size())
		{
			vector<int> subset;
			for (int i = 0; i < S.size(); i++)
				if (selected[i])
					subset.push_back(S[i]);
			result.push_back(subset);
			return;
		}
		//??? S[step]
		selected[step] = false;
		subsets(S, selected, step + 1, result);
		//不??? S[step]
		selected[step] = true;
		subsets(S, selected, step + 1, result);
    }
};

int main()
{
	cout << "hello world" << endl;
    int idex = 0;
    const int num = 3;
    while (1)
	{
		cout << "there is two recursion method, please choose one of them." << endl;
		cout << "1. Increment Construction Method." << endl;
		cout << "2. Bit Vector Method." << endl;
		cout << "which one would you choose?   ";
		while (!(cin >> idex))
		{
			cin.clear();
			while (!cin.get() != '\n')
				continue;
			cout << "请重新输入：" << endl;
		}
		switch (idex)
		{
		case 1:
		{	//在代码块内初始化局部变???
			vector<int> sIn1 = {1, 2, 3};
			vector<vector<int>> sOut1(pow(num, 2), vector<int>(num, 0));
			Solution x;
			sOut1 = x.subsets(sIn1);
			show2DVector(sOut1);
		}
			break;
		case 2:
		{
			vector<int> sIn2 = {1, 2, 3};
			vector<vector<int>> sOut2(pow(num, 2), vector<int>(num, 0));
			Solution1 x1;
			sOut2 = x1.subsets(sIn2);
			show2DVector(sOut2);
		}
			break;
		default:
			cout << endl;
			break;
		}
		cout << endl;
    }
    return 0;
}