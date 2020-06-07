#include <map>
#include <queue>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// 超时
class Solution1 {
  public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		int i = 0, j = 0, step = 1, end_flg = 0, word_len = beginWord.size();
		char c = 'a';
		int list_len = wordList.size();
		queue<pair<string, int>> q;
		vector<vector<string>> ans;
		vector<string> single_ans;
		q.push(pair<string, int>(beginWord, step));
		multimap<string, string> father;	// equal_range必须有序
		vector<int> visited(list_len, INT_MAX);
		for (i = 0; i < list_len; i++)
			visited[i] = (beginWord == wordList[i] ? 1 : INT_MAX);
		while (!q.empty()) {
			string tmp = q.front().first;
			int step = q.front().second;
			q.pop();
			if (end_flg)	// 到达过终点,只需要处理当前层即可
				continue;
			if (tmp == endWord)	{	// 到达搜索终点
				end_flg = 1;
				continue;
			}
			for (i = 0; i < word_len; i++) {	// 当前结点的下一step搜索
				string trans = tmp;
				for (c = 'a'; c <= 'z'; c++) {
					if (c == tmp[i])
						continue; 
					trans[i] = c;	// 字符变换
					for (j = 0; j < list_len; j++) {	// 变换后搜索
						if (wordList[j] == trans && visited[j] >= step) {	// 之前的step没有被搜索过或在当前步长中被搜索过
							q.push(pair<string, int>(trans, step + 1));	// 合规字符入队列
							visited[j] = step;
							int in_father = 0;	// 构造孩子父亲结点，防止重复构造完全相同的结点
							auto pos = father.equal_range(trans);
							while (pos.first != pos.second) {
								if (pos.first->second == tmp)
									in_father = 1;
								pos.first++;
							}
							if (!in_father)
								father.insert(pair<string, string>(trans, tmp));	// 孩子-父亲,多个父亲可能产生一个孩子
						}
					}
				}
			}
		}
		if (end_flg)
			build_path(father, beginWord, endWord, single_ans, ans);
		return ans;
	}
  private:
	void build_path(multimap<string, string>& father, string& start, string& end, vector<string>& CurrPath, vector<vector<string>>& Path) {
		CurrPath.push_back(end);
		if (start == end) {	// 递归终止
			Path.push_back(CurrPath);
			reverse(Path.back().begin(), Path.back().end());
			CurrPath.pop_back();
			return;
		}
		auto pos = father.equal_range(end);	// 有序查找
		while (pos.first != pos.second) {
			build_path(father, start, pos.first->second, CurrPath, Path);
			pos.first++;
		}
		CurrPath.pop_back();
	}
};

// 对wordList进行优化
class Solution2 {
  public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		int i = 0, j = 0, step = 1, end_flg = 0, word_len = beginWord.size();
		char c = 'a';
		queue<pair<string, int>> q;
		vector<vector<string>> ans;
		vector<string> single_ans;
		multimap<string, string> father;	// equal_range必须有序
		unordered_set<string> trueWord;	// 优化wordList
		for (auto &x : wordList)
			if (!trueWord.count(x))
				trueWord.insert(x);
		int list_len = trueWord.size();
		unordered_map<string, int> visited;	// 初始化
		for (auto &x : trueWord)
			visited[x] = INT_MAX;
		visited[beginWord] = 1;
		q.push(pair<string, int>(beginWord, step));	// 队列进行BFS
		while (!q.empty()) {
			string tmp = q.front().first;
			int step = q.front().second;
			q.pop();
			if (end_flg)	// 到达过终点,只需要处理当前层即可
				continue;
			if (tmp == endWord)	{	// 到达搜索终点
				end_flg = 1;
				continue;
			}
			for (i = 0; i < word_len; i++) {	// 当前结点的下一step搜索
				string trans = tmp;
				for (c = 'a'; c <= 'z'; c++) {
					if (c == tmp[i])
						continue; 
					trans[i] = c;	// 字符变换
					for (auto &x : trueWord) {
						if (x == trans && visited[trans] >= step) {	// 之前的step没有被搜索过或在当前步长中被搜索过
							q.push(pair<string, int>(trans, step + 1));	// 合规字符入队列
							visited[trans] = step;
							int in_father = 0;	// 构造孩子父亲结点，防止重复构造完全相同的结点
							auto pos = father.equal_range(trans);
							while (pos.first != pos.second) {
								if (pos.first->second == tmp)
									in_father = 1;
								pos.first++;
							}
							if (!in_father)
								father.insert(pair<string, string>(trans, tmp));	// 孩子-父亲,多个父亲可能产生一个孩子
						}
					}
				}
			}
			int lll = 0;
		}
		if (end_flg)
			build_path(father, beginWord, endWord, single_ans, ans);
		return ans;
	}
  private:
	void build_path(multimap<string, string>& father, string& start, string& end, vector<string>& CurrPath, vector<vector<string>>& Path) {
		CurrPath.push_back(end);
		if (start == end) {	// 递归终止
			Path.push_back(CurrPath);
			reverse(Path.back().begin(), Path.back().end());
			CurrPath.pop_back();
			return;
		}
		auto pos = father.equal_range(end);	// 有序查找
		while (pos.first != pos.second) {
			build_path(father, start, pos.first->second, CurrPath, Path);
			pos.first++;
		}
		CurrPath.pop_back();
	}
};

// 官方题解，图
const int INF = 1 << 20;
class Solution {
private:
    unordered_map<string, int> wordId;
    vector<string> idWord;
    vector<vector<int>> edges;
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int id = 0;
        for (const string& word : wordList)	// 对单词编号
            if (!wordId.count(word)) {
                wordId[word] = id++;
                idWord.push_back(word);
            }
        if (!wordId.count(endWord))	// 直接找到，不需要路径
            return {};
        if (!wordId.count(beginWord)) {	// 初始字符编号
            wordId[beginWord] = id++;
            idWord.push_back(beginWord);
        }
        edges.resize(idWord.size());	//	构边
        for (int i = 0; i < idWord.size(); i++)
            for (int j = i + 1; j < idWord.size(); j++)
                if (transformCheck(idWord[i], idWord[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
        const int dest = wordId[endWord];
        vector<vector<string>> res;
        queue<vector<int>> q;
        vector<int> cost(id, INF);	// 初始化
        q.push(vector<int>{wordId[beginWord]});
        cost[wordId[beginWord]] = 0;
        while (!q.empty()) {
            vector<int> now = q.front();
            q.pop();
            int last = now.back();
            if (last == dest) {	// 找到, 从id映射到string
                vector<string> tmp;
                for (int index : now)
                    tmp.push_back(idWord[index]);
                res.push_back(tmp);
            } else {	// 未找到
                for (int i = 0; i < edges[last].size(); i++) {	// 找下一步所有边
                    int to = edges[last][i];	// 边
                    if (cost[last] + 1 <= cost[to]) {	// 第一次到达所在step
                        cost[to] = cost[last] + 1;	// 更新step
                        vector<int> tmp(now);
                        tmp.push_back(to);
                        q.push(tmp);	// 入队列携带所有路径
                    }
                }
            }
        }
        return res;
    }

    bool transformCheck(const string& str1, const string& str2) {
        int differences = 0;
        for (int i = 0; i < str1.size() && differences < 2; i++)
            if (str1[i] != str2[i])
                ++differences;
        return differences == 1;
    }
};

int main() {
	Solution s;
	string beginWord = "hit";
	string endWord = "cog";
	vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
	// string beginWord = "red";
	// string endWord = "tax";
	// vector<string> wordList = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
	// string beginWord = "hot";
	// string endWord = "dog";
	// vector<string> wordList = {"hot", "dog"};
	// string beginWord = "cet";
	// string endWord = "ism";
	// vector<string> wordList = {	"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay",
	// 							"sip","kay","per","val","mes","ohs","now","boa","cet","pal",
	// 							"bar","die","war","hay","eco","pub","lob","rue","fry","lit",
	// 							"rex","jan","cot","bid","ali","pay","col","gum","ger","row",
	// 							"won","dan","rum","fad","tut","sag","yip","sui","ark","has",
	// 							"zip","fez","own","ump","dis","ads","max","jaw","out","btu",
	// 							"ana","gap","cry","led","abe","box","ore","pig","fie","toy",
	// 							"fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply",
	// 							"awe","pry","tit","tie","yet","too","tax","jim","san","pan",
	// 							"map","ski","ova","wed","non","wac","nut","why","bye","lye",
	// 							"oct","old","fin","feb","chi","sap","owl","log","tod","dot",
	// 							"bow","fob","for","joe","ivy","fan","age","fax","hip","jib",
	// 							"mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm",
	// 							"lot","tom","sax","tex","yum","pei","wen","wry","ire","irk",
	// 							"far","mew","wit","doe","gas","rte","ian","pot","ask","wag",
	// 							"hag","amy","nag","ron","soy","gin","don","tug","fay","vic",
	// 							"boo","nam","ave","buy","sop","but","orb","fen","paw","his",
	// 							"sub","bob","yea","oft","inn","rod","yam","pew","web","hod",
	// 							"hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib",
	// 							"rub","ere","dig","era","cat","fox","bee","mod","day","apr",
	// 							"vie","nev","jam","pam","new","aye","ani","and","ibm","yap",
	// 							"can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx",
	// 							"jog","nun","par","wan","fey","bus","oak","bad","ats","set",
	// 							"qom","vat","eat","pus","rev","axe","ion","six","ila","lao",
	// 							"mom","mas","pro","few","opt","poe","art","ash","oar","cap",
	// 							"lop","may","shy","rid","bat","sum","rim","fee","bmw","sky",
	// 							"maj","hue","thy","ava","rap","den","fla","auk","cox","ibo",
	// 							"hey","saw","vim","sec","ltd","you","its","tat","dew","eva",
	// 							"tog","ram","let","see","zit","maw","nix","ate","gig","rep",
	// 							"owe","ind","hog","eve","sam","zoo","any","dow","cod","bed",
	// 							"vet","ham","sis","hex","via","fir","nod","mao","aug","mum",
	// 							"hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem",
	// 							"who","bet","gos","son","ear","spy","kit","boy","due","sen",
	// 							"oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit",
	// 							"fix","sad","rib","eye","hop","haw","wax","mid","tad","ken",
	// 							"wad","rye","pap","bog","gut","ito","woe","our","ado","sin",
	// 							"mad","ray","hon","roy","dip","hen","iva","lug","asp","hui",
	// 							"yak","bay","poi","yep","bun","try","lad","elm","nat","wyo",
	// 							"gym","dug","toe","dee","wig","sly","rip","geo","cog","pas",
	// 							"zen","odd","nan","lay","pod","fit","hem","joy","bum","rio",
	// 							"yon","dec","leg","put","sue","dim","pet","yaw","nub","bit",
	// 							"bur","sid","sun","oil","red","doc","moe","caw","eel","dix",
	// 							"cub","end","gem","off","yew","hug","pop","tub","sgt","lid",
	// 							"pun","ton","sol","din","yup","jab","pea","bug","gag","mil",
	// 							"jig","hub","low","did","tin","get","gte","sox","lei","mig",
	// 							"fig","lon","use","ban","flo","nov","jut","bag","mir","sty",
	// 							"lap","two","ins","con","ant","net","tux","ode","stu","mug",
	// 							"cad","nap","gun","fop","tot","sow","sal","sic","ted","wot",
	// 							"del","imp","cob","way","ann","tan","mci","job","wet","ism",
	// 							"err","him","all","pad","hah","hie","aim","ike","jed","ego",
	// 							"mac","baa","min","com","ill","was","cab","ago","ina","big",
	// 							"ilk","gal","tap","duh","ola","ran","lab","top","gob","hot",
	// 							"ora","tia","kip","han","met","hut","she","sac","fed","goo",
	// 							"tee","ell","not","act","gil","rut","ala","ape","rig","cid",
	// 							"god","duo","lin","aid","gel","awl","lag","elf","liz","ref",
	// 							"aha","fib","oho","tho","her","nor","ace","adz","fun","ned",
	// 							"coo","win","tao","coy","van","man","pit","guy","foe","hid",
	// 							"mai","sup","jay","hob","mow","jot","are","pol","arc","lax",
	// 							"aft","alb","len","air","pug","pox","vow","got","meg","zoe",
	// 							"amp","ale","bud","gee","pin","dun","pat","ten","mob"};
	vector<vector<string>> ans = s.findLadders(beginWord, endWord, wordList);
	show2DVector(ans);
	return 1;
} 