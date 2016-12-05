#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

//假设单词长度为k,排序时间复杂度为O(k*log(k))，之前不想排序，因为比较的时间复杂度只有O(k)，但是如此要判断单词排列是否出现就异常困难
//因此考虑每一个单词的最小排序作为key，val是对应的乱序单词组，思路和ip时间窗很相似(ip映射时间队列)

class Solution
{
  public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> sMap;
        for (auto x : strs)
        {
            string tmp = x;
            sort(tmp.begin(), tmp.end());
            sMap[tmp].push_back(x);
        }
        vector<vector<string>> result;
        int count = 0;
        for (auto i = sMap.cbegin(); i != sMap.cend(); ++i)
        {
            result.push_back(vector<string>(i->second.size())); //分配空间才能copy，不然只能用insert
            copy(i->second.begin(), i->second.end(), result[count++].begin());
        }
        return result;
    }
};

//以下算法时我根据上述算法启发得到的算法
class Solution1
{
  public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> result;
        unordered_map<string, int> sMap;
        int i = 0;
        for (auto x : strs)
        {
            string tmp = x;
            sort(tmp.begin(), tmp.end());
            if (!sMap.count(tmp))
            {
                sMap[tmp] = i;
                result.push_back(vector<string>());
                result[i++].push_back(x);
            }
            else
                result[sMap[tmp]].push_back(x);
        }
        return result;
    }
};

int main()
{
    Solution s1;
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result = s1.groupAnagrams(strs);
    show2DVector(result);
    return 0;
}