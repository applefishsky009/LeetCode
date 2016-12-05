#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <E:\RylModule\vector.h>
using namespace std;

//除了最后一行，字符串按位数均匀分布(两个字符串之间至少有一个空格)，注意如果只有一个单词要补充足够的空格
//最后一行单词左排列就行(依然至少一个空格)，要补充足够的空格'
class Solution
{
  public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        vector<string> result;
        auto cur = words.begin();
        auto pre = words.begin();
        //除了最后一行其他数据
        while (1)
        {
            int sum = 0;
            cur = pre;
            while (pre != words.end() && (sum + (*pre).size() <= maxWidth))
            {
                sum += (*pre++).size();
                ++sum;
            }
            if (pre == words.end())
                break;               //必须使用超尾迭代器来区分是否达到了最后一串，
            sum = sum - (pre - cur); //减去添加的空格数就是字符串总长度
            result.push_back(makeString(words, cur, pre, maxWidth, sum));
        }
        //处理最后的数据
        string tmp;
        for (auto p = cur; p != words.end(); ++p)
        {
            tmp += *p;
            tmp.push_back(' ');
        }
        tmp.pop_back();
        while (tmp.size() < maxWidth)
            tmp.push_back(' ');

        result.push_back(tmp);
        return result;
    }

  private:
    string makeString(vector<string> &words, vector<string>::iterator start, vector<string>::iterator end, int maxWidth, int sum)
    {
        string tmp = *start;
        int extra = maxWidth - sum;
        //只有一个单词补充足够的空格
        if (start + 1 == end)
        {
            while (tmp.size() < maxWidth)
                tmp.push_back(' ');
            return tmp;
        }
        //在间隙补充空格
        int num = end - start - 1; //单词空隙个数
        int average = extra / num;
        int addOneNum = extra % num;
        int extraCharCount = 0; //计算多余的空格添加了多少个
        for (auto i = start + 1; i < end; ++i)
        {
            for (int j = 0; j < average; ++j)
                tmp.push_back(' ');
            ++extraCharCount;
            if (extraCharCount < addOneNum + 1)
                tmp.push_back(' '); //压入多余的空格
            tmp += *i;
        }
        return tmp; //返回拼接的字符串
    }
};

int main()
{
    Solution s1;
    //vector<string> word = {"This", "is", "an", "example", "of", "text", "justification."};
    vector<string> word = {"aaa", "bbb", "ccc", "dddd"};
    show1DVector(word);
    int maxWidth = 10;
    vector<string> result = s1.fullJustify(word, maxWidth);
    show1DVector(result);
    return 0;
}