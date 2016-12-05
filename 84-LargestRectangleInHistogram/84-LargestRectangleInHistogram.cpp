//注意栈的使用中，尽量不要存值(信息量太小),应该存放能快速访问到值的指针或者索引。
//树和链表的栈的应用，存入栈中的是指向节点的指针，以便回溯路径
//数组的栈的应用，存入栈中的是数组的下标索引，以便回溯节点

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//O(n^2)肯定是不可取
//需要一种特殊的遍历技巧
class Solution
{
  public:
    int largestRectangleArea(vector<int> &heights)
    {
		stack<int> s;
		heights.push_back(0);
		int tempMax = 0;
		for (int i = 0; i < heights.size();)
		{
			if (s.empty() || heights[i] >= heights[s.top()])
			{ //递增序列入栈
				s.push(i++);
				continue;
			}
			else
			{ //出栈并计算面积
				int temp = s.top();
				s.pop();
				//栈为空	之前所有元素大于当前元素，宽度为i
				//栈不空	宽度=i-temp的位置(因为弹出了，所以temp = s.top()+1)
				tempMax = max(tempMax, heights[temp] * (s.empty() ? i : i - s.top() - 1));
			}
		}
		heights.pop_back();
		return tempMax;
    }
};

int main()
{
    vector<int> heights = {10, 2, 1, 2, 6, 2, 3};
    Solution s1;
    cout << s1.largestRectangleArea(heights) << endl;
    return 0;
}