#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

//按位置遍历的进阶，使用find有选择的压入结果，但是OJ会超时
//随着sums的增长，在最后一步find()方法的复杂度n!增长，耗时太久
//如果在每一步中可以去掉相同的步，可以极大优化算法
class Solution
{
  public:
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
		vector<vector<int>> result;
		vector<int> path;
		dfs(nums, result, path, nums.size());
		return result;
    }

  private:
    void dfs(vector<int> nums, vector<vector<int>> &result, vector<int> path, const int n)
    {
		if (path.size() == n)
		{ //出口
			if (find(result.begin(), result.end(), path) == result.end())
				result.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); ++i)
		{
			vector<int> temp = nums;
			vector<int>::iterator cur = temp.begin() + i;
			path.push_back(*cur);
			temp.erase(cur);		//往前走一步
			dfs(temp, result, path, n); //入口
			path.pop_back();		//回溯
		}
    }
};

//中间步去掉相同步
class Solution1
{
  public:
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
		vector<vector<int>> result;
		vector<int> path;
		dfs(nums, result, path, nums.size());
		return result;
    }

  private:
    void dfs(vector<int> nums, vector<vector<int>> &result, vector<int> path, const int n)
    {
		if (path.size() == n)
		{ //出口
			result.push_back(path);
			return;
		}
		vector<int> tempStep; //判断当前步，不要走重复
		for (int i = 0; i < nums.size(); ++i)
		{
			vector<int> temp = nums; //恢复当前状态
			vector<int>::iterator cur = temp.begin() + i;
			if (find(tempStep.begin(), tempStep.end(), *cur) == tempStep.end())
			{
				tempStep.push_back(*cur);
				path.push_back(*cur);
				temp.erase(cur);	    //往前走一步
				dfs(temp, result, path, n); //入口
				path.pop_back();	    //回溯
			}
		}
    }
};

//不使用位置遍历省略复制操作，速度略有提升
//用hash_map统计出现的次数速度更快，于是用字符次数对来代替原数组(重复字符越多速度提升越明显)
class Solution2
{
  public:
    vector<vector<int>> permuteUnique(vector<int> &num)
    {
		sort(num.begin(), num.end());
		unordered_map<int, int> count_map; //记录每个元素出现的次数
		for_each(num.begin(), num.end(), [&count_map](int e)	//lamada捕获并传参
		{
			if (count_map.find(e) != count_map.end())
				count_map[e]++;
			else
				count_map[e] = 1;
		});
		//将map的pair拷贝到vector里
		vector<pair<int, int>> elems;
		for_each(count_map.begin(), count_map.end(),
		[&elems](const pair<int, int> &e) 
		{
			elems.push_back(e);
		});
		vector<vector<int>> result; //最终结果
		vector<int> p;		    //中间结果
		n = num.size();
		permute(elems.begin(), elems.end(), p, result);
		return result;
    }

  private:
    size_t n;
    typedef vector<pair<int, int>>::const_iterator Iter;
	
    void permute(Iter first, Iter last, vector<int> &p,
		 vector<vector<int>> &result)
    {
		if (n == p.size())	//收敛条件
			result.push_back(p);
		//扩展状态
		for (auto i = first; i != last; i++)
		{
			int count = 0; //统计*i在p中出现的次数
			for (auto j = p.begin(); j != p.end(); j++)
				if (i->first == *j)
					count++;

			if (count < i->second)
			{ //次数小于最大值
				p.push_back(i->first);
				permute(first, last, p, result);
				p.pop_back(); //撤销动作，返回上一层
			}
		}
    }
};

int main()
{
    Solution2 s1;
    vector<vector<int>> result;
    vector<int> nums = {1, 1, 2};
    result = s1.permuteUnique(nums);
	show2DVector(result);
    return 0;
}