#include <vector>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int strStr(const string haystack, const string needle)
    {
		if (haystack.size() < needle.size()) //特殊情况1，无法匹配
			return -1;
		if (needle.size() == 0) //特殊情况2,不用计算子串特性nextVal
			return 0;
		vector<int> nextVal(needle.size(), 0);
		calNextVal(nextVal, needle);
		for (int i = 0, k, j; i <= haystack.size() - needle.size();)
		{
			k = i;							 //重置母串下标指针
			j = 0;							 //子串下标指针回溯
			while (haystack[k] && needle[j] && haystack[k] == needle[j]) //匹配，下标指针前移
			{
				j++;
				k++;
			}
			if (j == needle.size()) //匹配完毕，检测是否完全匹配
				return i;
			i = i + j - nextVal[j]; //失配，子串前移
		}
		return -1;
    }

  private:
    void calNextVal(vector<int> &nextVal, const string &needle) //nextVal数组只与子串有关，只传子串
    {
		int i = 0;  //j,偏移指针
		int j = -1; //i,next下标（实际上是要计算的next下标-1,因为是先加后赋值）
		nextVal[0] = j;
		while (i < needle.size() - 1) //注意i少一个值
		{
			if (j == -1 || needle[i] == needle[j]) //前一次失配 或 当前匹配，真前后缀长度加1
			{
				j++;
				i++;			    //下一个字符是否匹配？
				if (needle[i] != needle[j]) //不完全匹配，说明i失配,j不一定失配(还取决于母串)，因此需要判断j
					nextVal[i] = j;	 //j = next[i]即真前后缀的最大长度
				else			    //完全匹配，i与j位置等效,若i失配，j一定失配，因此要回溯
					nextVal[i] = nextVal[j];
			}
			else //不匹配，指针回溯，失配一次就回溯到-1，在if中i,j++才有赋值，这里指针回溯没有赋值
				j = nextVal[j];
		}
    }
};

int main()
{
    Solution s1;
    string haystack = "abcdgt";
    string needle = "bcd";
    cout << s1.strStr(haystack, needle) << endl;
    return 0;
}