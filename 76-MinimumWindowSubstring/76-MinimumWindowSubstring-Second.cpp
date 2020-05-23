#include <string>
#include <climits>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 使用map减法来做，优势在于非T字符为负，可以用数量标识是否向左更新
class Solution {
  public:
	string minWindow(string S, string T) {
		unordered_map<char, int> map;
		string ans = "";
		int s_len = S.size(), t_len = T.size();
		int i = 0, left = 0, cnt = 0, len = INT_MAX;
		for (auto &c : T) 
			map[c] ++;
		for (i = 0; i < s_len; i++) {
			if (--map[S[i]] >= 0) 	// 向右扫描，非T中字符为负
				++cnt;
			while(cnt == t_len) {	// 向左扫描
				if (len > i - left + 1) {	// 更新子串
					len = i - left + 1;
					ans = S.substr(left, len);
				}
				if (++map[S[left++]] > 0)	// 必然是T字符串
					--cnt;
			}
		}
		return ans;
	}
};

class Solution1
{
  public:
    string minWindow(string S, string T) {
		int i = 0, j = 0, flag = 0, idx = 0, len = INT_MAX;
		unordered_map<char, int> t_map;
		unordered_map<char, int> s_map;
		for (auto &x : T) {
			t_map[x] ++;
			s_map[x] = 0;
		}
		for (i = 0; i < S.size(); i++) {
			if (t_map.find(S[i]) != t_map.end()) {
				s_map[S[i]] ++;
				flag = isContain(s_map, t_map);
			}
			updateIdx(flag, i, j, idx, len);
			while (flag) {
				if (t_map.find(S[j]) != t_map.end()) {
					s_map[S[j]] --;
					flag = isContain(s_map, t_map);
				}
				j++;
				updateIdx(flag, i, j, idx, len);
			}

		}
		return len != INT_MAX ? S.substr(idx, len) : "";
	}
  private:
	bool isContain(unordered_map<char, int> &s_map, unordered_map<char, int> &t_map) {
		for (auto it = t_map.begin(); it != t_map.end(); it++)
			if (s_map[it->first] < it->second)
				return 0;
		return 1;
	}
	void updateIdx(int flag, int i, int j, int &idx, int &len) {
		if (flag && i - j + 1 < len) {
			idx = j;
			len = i - j + 1;
		}
	}
};

int main()
{
    Solution s1;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    // string s = "a";
    // string t = "aa";
    // string s = "ab";
    // string t = "b";
    cout << s1.minWindow(s, t) << endl;
    return 0;
}