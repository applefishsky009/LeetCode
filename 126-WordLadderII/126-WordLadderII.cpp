#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <D:\Github\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict)
    {
		vector<vector<string>> Path;
		vector<string> CurrPath;
		unordered_set<string> visited;
		queue<pair<string, int>> CurrCandidate; //队列，存储路径字符和步长
		multimap<string, string> father;	//哈希表，根据key value排序;存储路径字符的孩子和父亲，第一个是key，第二个是value
		bool finded = false;
		int curr_step = 0;
		int WordSize = start.size();
		if (start.empty() || end.empty())
			return Path; //空路径
		if (start == end)
		{
			CurrPath.push_back(start);
			Path.push_back(CurrPath);
		}
		if (dict.count(start))
			dict.erase(start); //从wordList删除开始字符
		if (dict.count(end))
			dict.erase(end);			 //从wordList删除结束字符
		CurrCandidate.push(make_pair(start, 1)); //开始字符入队列
		visited.insert(start);			 //路径中已经访问过的字符
		while (!CurrCandidate.empty())
		{
			pair<string, int> CurrWord(CurrCandidate.front()); //队列首
			CurrCandidate.pop();			       //出队列
			if (curr_step < CurrWord.second)
			{ //新的步长来临，清空已访问队列
				if (finded)
					break; //判断是否找到的标识位
				unordered_set<string>::iterator iter;
				for (iter = visited.begin(); iter != visited.end(); iter++)	//删除旧步长中字典中已经访问过的字符，
					dict.erase(*iter); //因为在更多的步长中如果还需要访问说明不是最优解
				curr_step = CurrWord.second;
				visited.clear(); //清空已访问集合
			}
			for (int i = 0; i < WordSize; i++)
			{ //对字符逐位替换
				for (char c = 'a'; c <= 'z'; c++)
				{ //对每一个位置逐个字母替换
					if (c == CurrWord.first[i])
						continue;		//原字符，不用替换
					swap(c, CurrWord.first[i]); //替换
					if (CurrWord.first == end)
					{ //找到目标字符
						finded = true;
						string temp = CurrWord.first;
						swap(c, CurrWord.first[i]);
						father.insert(make_pair(end, CurrWord.first));
						break;
					}
					if (!finded && dict.count(CurrWord.first))
					{ //没找到但字典中存在，说明可能是路径
						if (visited.count(CurrWord.first) == 0)
						{									//之前没有访问过这个字符
							CurrCandidate.push(make_pair(CurrWord.first, CurrWord.second + 1)); //路径字符入队列
							visited.insert(CurrWord.first);					//加入已经访问的哈希表
						}
						string temp = CurrWord.first;
						swap(c, CurrWord.first[i]);
						father.insert(make_pair(temp, CurrWord.first)); //孩子和父亲入表
						continue;					//不会交换两次
					}
					swap(c, CurrWord.first[i]); //交换回来
				}
			}
		}
		if (finded == true)	//由父亲孩子表来制造路径路径
			build_path(father, start, end, CurrPath, Path); //DFS重建路径
		return Path;
    }

  private:
    void build_path(multimap<string, string> father, string start, string end, vector<string> &CurrPath, vector<vector<string>> &Path)
    {
		CurrPath.push_back(end);
		if (start == end)
		{ //递归终止条件，DFS到底
			Path.push_back(CurrPath);
			reverse(Path.back().begin(), Path.back().end()); //从尾到头重建的路径需要反转
			CurrPath.pop_back();
			return;
		}
		//用两个指针来判断同一步是否重复，第一个指针指向end key，第二个指针指向下一个key，用来判断当前链表是否遍历完了
		pair<multimap<string, string>::iterator, multimap<string, string>::iterator> pos = father.equal_range(end);
		while (pos.first != pos.second)
		{
			build_path(father, start, pos.first->second, CurrPath, Path); //尾指针end往前回溯
			pos.first++;						  //每一个key是一个链表，这里是链表的遍历,链表结束时first.key=seconde.key
		}
		CurrPath.pop_back(); //每遍历完一个链表向上回溯一次路径
    }
};

int main()
{
    Solution s1;
    string beginWord = "hit";
    string endWord = "cog";
    unordered_set<string> wordList;
    wordList.insert("hot");
    wordList.insert("dot");
    wordList.insert("dog");
    wordList.insert("lot");
    wordList.insert("log");
    vector<vector<string>> result;
    result = s1.findLadders(beginWord, endWord, wordList);
	show2DVector(result);
    return 0;
}