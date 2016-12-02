#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

//A by leetcode
class Solution
{
  public:
    vector<int> searchRange(const vector<int> &range, const int num)
    {
		vector<int> out;
		int i = 0;
		int j = range.size() - 1;
		bool sign = 0;
		sign = MidSearch(i, j, out, range, num);
		if (!sign)
			return vector<int>() = {-1, -1};
		return out;
    }

  private:
    bool MidSearch(const int i, const int j, vector<int> &out, const vector<int> &range, const int num)
    { //二分查找
		if (i > j)
			return false; //递归终止条件
		int mid = (i + j) / 2;
		int temp = mid;
		if (range[temp] == num)
		{
			//往低位找
			while (temp >= 0 && range[temp] == num)
				temp--;
			if (temp < 0)
				out.push_back(0); //目标在0处也有
			else
				out.push_back(temp + 1);
			//往高位找
			temp = mid;
			while (temp <= range.size() - 1 && range[temp] == num)
				temp++;
			if (temp > range.size() - 1)
				out.push_back(range.size() - 1);
			else
				out.push_back(temp - 1);
			return true;
		}
		else
		{
			bool k = MidSearch(i, mid - 1, out, range, num);
			bool l = MidSearch(mid + 1, j, out, range, num);
			return (k || l);
		}
    }
};

int main()
{
    int n = 7;
    vector<int> vectorIn = {1, 3, 3, 4, 7, 7, 7, 7, 7, 8};
    Solution s1;
    show1DVector(s1.searchRange(vectorIn, n));
    return 0;
}
