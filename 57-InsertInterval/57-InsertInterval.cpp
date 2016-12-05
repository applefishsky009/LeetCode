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

class Solution
{
  public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {
		vector<Interval>::iterator it = intervals.begin();
		while (it != intervals.end())
		{
			if (newInterval.start > it->end)
			{ //继续找
				it++;
				continue;
			}
			else if (newInterval.end < it->start)
			{ //找到位置，插入并返回
				intervals.insert(it, newInterval);
				return intervals;
			}
			else
			{ //区间重叠，做新区间，删除旧区间
				newInterval.start = min(newInterval.start, it->start);
				newInterval.end = max(newInterval.end, it->end);
				it = intervals.erase(it);
			}
		}
		//处理尾部
		intervals.insert(intervals.end(), newInterval);
		return intervals;
    }
};

int main()
{
    Solution s1;
    vector<Interval> intervals = {Interval(1, 2), Interval(3, 5), Interval(6, 7), Interval(8, 10), Interval(12, 16)};
    Interval newIntervals(4, 9);
    vector<Interval> result = s1.insert(intervals, newIntervals);
    return 0;
}