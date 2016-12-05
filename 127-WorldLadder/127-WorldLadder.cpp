#include <queue>
#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution
{
  public:
    int ladderLength(string beginWord, string endWord, unordered_set<string> &wordList)
    {
		if (beginWord == endWord)
			return 1;
		int n = beginWord.size();
		if (n < 1 || n != endWord.size())
			return 0;    //没有字符或者长度不等，走不到
		queue<string> q; //广搜，需要借助队列
		q.push(beginWord);
		wordList.erase(beginWord); //如果表中有start,没有意义，去掉不影响结果
		int length = 2;

		while (!q.empty())
		{
			int size = q.size();
			for (int i = 0; i < size; i++)
			{
				string tepmWord = q.front();
				q.pop();
				for (int j = 0; j < n; j++) //单词长度的遍历
				{
					char tempChar = tepmWord[j];
					for (char k = 'a'; k <= 'z'; k++)
					{
						if (k == tempChar) //这一步没有变化，不需要判断
							continue;
						tepmWord[j] = k;
						if (tepmWord == endWord) //直接找到目标，返回长度
							return length;
						if (wordList.find(tepmWord) != wordList.end()) //注意和string.find()返回值不相同，
						{					       //该单词找到了，说明这一步变化有效，压入队列
							q.push(tepmWord);
							wordList.erase(tepmWord); //这里压入队列之后在字典中擦除了这个元素，因此不需要是否遍历的标识，因为已经遍历过的都不在了
						}
					}
					tepmWord[j] = tempChar;
				}
			} // for size即相同步数的遍历
			length++;
		}
		return 0;
    }
};

int main()
{
    unordered_set<string> set;
    string start = "a";
    string end = "c";
    set.insert("b"); //默认是后插
    set.insert("a");
    set.insert("c");
    Solution s;
    int n = s.ladderLength(start, end, set);
    cout << n << endl;
    return 0;
}