#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

//我的实现1:注意这不一定是有序的,排序之后逻辑上简单许多，但复杂度太低(这是由于在本数组上操作erase()太耗时)
class Solution
{
  public:
    vector<Interval> merge(vector<Interval> &intervals)
    {
		sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) {return a.start < b.start;});
		int n = intervals.size();
		vector<Interval>::iterator pre = intervals.begin();
		vector<Interval>::iterator end = intervals.end();
		intervals.erase(pre);
		intervals.insert(pre, Interval());
		for (int i = 1; i < n;)
		{
			if (intervals[i].start <= intervals[i - 1].end)
			{						     //重叠，更新当前，删除上一个节点
				intervals[i].start = intervals[i - 1].start; //因为已经排过序了
				intervals[i].end = max(intervals[i - 1].end, intervals[i].end);
				pre = intervals.erase(pre);
				--n; //只能用元素数量，不能用.end()来判断是否结尾，因为.erase()之后尾节点
			}
			else
			{
				++pre;
				++i;
			}
		}
		return intervals;
    }
};

//LeetCode Discuss
class Solution1
{
  public:
    vector<Interval> merge(vector<Interval> &intervals)
    {
		if (intervals.empty())
			return vector<Interval>{};
		vector<Interval> result;
		sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) 
		{ 
			return a.start < b.start; 
		});
		result.push_back(intervals[0]);
		for (int i = 1; i < intervals.size(); i++)
		{ //插入的原理与我的实现相同，但在新容器中操作很简单
			if (result.back().end < intervals[i].start)
				result.push_back(intervals[i]); //不重叠，入栈
			else
				result.back().end = max(result.back().end, intervals[i].end); //重叠更新数据，不入栈
		}
		return result;
    }
};

//Two Pointers-important
class Solution2
{
  public:
    vector<Interval> merge(vector<Interval> &intervals)
    {
		if (intervals.size() < 2)
			return intervals;
		sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) 
		{ 
			return a.start < b.start; 
		});
		vector<Interval>::iterator pre = intervals.begin();
		vector<Interval>::iterator cur = pre + 1;
		while (cur != intervals.end())
		{
			if (cur->start <= pre->end)
			{ //重叠，更新上一个，删除当前节点
				pre->end = max(pre->end, cur->end);
				cur = intervals.erase(cur);
			}
			else
			{
				++pre;
				++cur;
			}
		}
		return intervals;
    }
};

int main()
{
    Solution2 s1;
    vector<Interval> intervals = {Interval(1, 3), Interval(2, 6), Interval(8, 10), Interval(15, 18)};
    intervals = s1.merge(intervals);
    return 0;
}