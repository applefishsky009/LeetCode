#include <vector>
#include <iostream>
using namespace std;

//如果没有sorted，需要hashmap来记录出现的次数
class Solution
{
  public:
    int removeDuplicates(vector<int> &nums)
    {
		if (nums.size() <= 2)
			return nums.size();
		int num = 1;
		int i = 0;
		vector<int>::iterator p = nums.begin();
		p++;
		while (i < nums.size() - 1)
		{
			if (nums.at(i + 1) == nums.at(i))
			{
				num++;
				if (num >= 3) //注意擦除一个元素的时候迭代器和下标都是不能变化的，
				{	     //因此--抵消掉变化或者在除去这种情况下的其他情况都执行++
					p = --nums.erase(p);
					--i;
				}
			}
			else
				num = 1;
			i++;
			p++;
		}
		return nums.size();
    }
};

int main()
{
    vector<int> vectorIn = {1, 1, 1, 1, 2, 2, 3};
    Solution s1;
    cout << s1.removeDuplicates(vectorIn) << endl;
    return 0;
}