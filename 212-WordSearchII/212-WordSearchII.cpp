#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

//有趣的问题，注意要记录遍历的路径
//注意一个字符找到两次不能重复返回，也不能用相同的字符找,
//算法超时，OJ提示用前缀树，留待以后解答！！！
class Solution
{
  public:
    vector<string> findWords(const vector<vector<char>> &board, vector<string> &word)
    {
        vector<string> result;
        if (board.size() == 0 || word.size() == 0)
            return result;
        const int m = board.size();
        const int n = board[0].size();
        vector<vector<bool>> map(m, vector<bool>(n, false)); //用vector模拟哈希表记录遍历路径
        sort(word.begin(), word.end());
        for (int k = 0; k < word.size(); ++k)
        { //对word遍历
            bool signal = false;
            if (k == 0 || word[k] != word[k - 1])
            {
                for (int i = 0; i < m; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        if (board[i][j] == word[k][0])
                        {
                            if (dfs(board, word[k], i, j, map, 0))
                            {
                                result.push_back(word[k]);
                                signal = true;
                                break;
                            }
                        }
                    }
                    if (signal)
                        break;
                }
            }
        }
        return result;
    }

  private:
    bool dfs(const vector<vector<char>> &board, const string word,
             int row, int col, vector<vector<bool>> &map, int len)
    {
        if (len == word.size())
            return true;
        const int m = board.size();
        const int n = board[0].size();
        if (row < 0 || row >= m || col < 0 || col >= n)
            return false;
        if (word[len] != board[row][col])
            return false;
        if (map[row][col])
            return false;
        map[row][col] = true; //往前走
        bool ret = dfs(board, word, row - 1, col, map, len + 1) || dfs(board, word, row + 1, col, map, len + 1) || dfs(board, word, row, col - 1, map, len + 1) || dfs(board, word, row, col + 1, map, len + 1);
        //回溯
        //if (!ret) map[row][col] = false;  //保留下来的是最终路径，需要判断，比下面慢
        map[row][col] = false; //任何一次DFS最终都DFS成全false
        return ret;
    }
};

//前缀树
class Solution1
{
  private:
    class Trie
    {
      public:
        Trie *children[26];
        bool isLeaf;
        int wordIdx;
        int prefixCount;

        Trie()
        {
            isLeaf = false;
            wordIdx = 0;
            prefixCount = 0;
            fill_n(children, 26, nullptr);
        }

        ~Trie()
        {
            for (auto i = 0; i < 26; ++i)
                delete children[i];
        }
    };

    void insertWord(Trie *root, const vector<string> &words, int idx)
    {
        int i, childID, len = words[idx].size();
        for (i = 0, root->prefixCount++; i < len; ++i)
        {
            childID = words[idx][i] - 'a';
            if (!root->children[childID])
                root->children[childID] = new Trie();
            root = root->children[childID];
            ++root->prefixCount;
        }
        root->isLeaf = true;
        root->wordIdx = idx;
    }

    Trie *buildTrie(const vector<string> &words)
    {
        Trie *root = new Trie();
        for (int i = 0; i < words.size(); ++i)
            insertWord(root, words, i);
        return root;
    }

    int dfs_Trie(vector<string> &res, Trie *root, vector<vector<char>> &board, vector<string> &words, int row, int col)
    {
        int detected = 0;

        if (root->isLeaf)
        {
            ++detected;
            root->isLeaf = false;
            res.push_back(words[root->wordIdx]);
        }

        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] == '*' || !root->children[board[row][col] - 'a'] || root->children[board[row][col] - 'a']->prefixCount <= 0)
            return detected;
        int curC = board[row][col] - 'a';
        board[row][col] = '*';
        detected += dfs_Trie(res, root->children[curC], board, words, row - 1, col) +
                    dfs_Trie(res, root->children[curC], board, words, row + 1, col) +
                    dfs_Trie(res, root->children[curC], board, words, row, col - 1) +
                    dfs_Trie(res, root->children[curC], board, words, row, col + 1);
        root->prefixCount -= detected;
        board[row][col] = curC + 'a';
        return detected;
    }

  public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        int M, N, wordNum = words.size();
        vector<string> res;
        if (!(M = board.size()) || !(N = board[0].size()) || !wordNum)
            return res;
        Trie *root = buildTrie(words);
        for (auto i = 0; i < M && root->prefixCount; ++i)
            for (auto j = 0; j < N; ++j)
                dfs_Trie(res, root, board, words, i, j);
        delete root;
        return res;
    }
};

int main()
{
    Solution1 s1;
    vector<vector<char>> board = 
        {{'o', 'a', 'a', 'n'}, 
         {'e', 't', 'a', 'e'}, 
         {'i', 'h', 'k', 'r'},
         {'i', 'f', 'l', 'v'}};
    vector<string> word{"oath", "pea", "eat", "rain"};
    vector<string> result = s1.findWords(board, word);
    show1DVector(result);
    return 0;
}