#include <string>
#include <cctype>
#include <vector>
#include <iostream>
using namespace std;

class trieNode
{
  public:
    bool wordEnd;
    vector<trieNode *> cur;
    trieNode() : wordEnd(false)
    {
        cur = vector<trieNode *>(26, nullptr);
    }
};

class WordDictionary
{
  private:
    trieNode *root;
    bool dfs(trieNode *pre, const string &word, int i)
    {
        if (i == word.size())
            return pre->wordEnd == true ? true : false;
        if (word[i] != '.')
        {
            if (pre->cur[word[i] - 'a'] && dfs(pre->cur[word[i] - 'a'], word, i + 1))
                return true;
        }
        else
        {
            for (int j = 0; j < 26; j++)
                if (pre->cur[j] && dfs(pre->cur[j], word, i + 1))
                    return true;
        }
        return false;
    }

  public:
    /** Initialize your data structure here. */
    WordDictionary()
    {
        root = new trieNode;
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        trieNode *pre = root;
        for (int i = 0; i < word.size(); i++)
        {
            // if (isupper(word[i]))
            //     return;
            if (!pre->cur[word[i] - 'a'])
                pre->cur[word[i] - 'a'] = new trieNode;
            pre = pre->cur[word[i] - 'a'];
        }
        pre->wordEnd = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word)
    {
        trieNode *pre = root;
        return dfs(pre, word, 0);
    }
};

class TrieNode
{
  public:
    bool isKey;
    TrieNode *children[26];
    TrieNode() : isKey(false)
    {
        memset(children, NULL, sizeof(TrieNode *) * 26);
    }
};

class WordDictionary1
{
  public:
    WordDictionary()
    {
        root = new TrieNode();
    }

    // Adds a word into the data structure.
    void addWord(string word)
    {
        TrieNode *run = root;
        for (char c : word)
        {
            if (!(run->children[c - 'a']))
                run->children[c - 'a'] = new TrieNode();
            run = run->children[c - 'a'];
        }
        run->isKey = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word)
    {
        return query(word.c_str(), root);
    }

  private:
    TrieNode *root;

    bool query(const char *word, TrieNode *node)
    {
        TrieNode *run = node;
        for (int i = 0; word[i]; i++)
        {
            if (run && word[i] != '.')
                run = run->children[word[i] - 'a'];
            else if (run && word[i] == '.')
            {
                TrieNode *tmp = run;
                for (int j = 0; j < 26; j++)
                {
                    run = tmp->children[j];
                    if (query(word + i + 1, run))
                        return true;
                }
            }
            else
                break;
        }
        return run && run->isKey;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */

int main()
{
    WordDictionary1 s1;
    s1.addWord("WordDictionary");
    s1.addWord("search");
    s1.addWord("addWord");
    cout << s1.search("") << endl;
    cout << s1.search("at") << endl;
    cout << s1.search("and") << endl;
    cout << s1.search("an") << endl;
    cout << s1.search("add") << endl;
    cout << s1.search("a") << endl;
    cout << s1.search(".at") << endl;
    cout << s1.search("bat") << endl;
    cout << s1.search(".at") << endl;
    cout << s1.search("an.") << endl;
    cout << s1.search("a.d.") << endl;
    cout << s1.search("b.") << endl;
    cout << s1.search("a.d") << endl;
    cout << s1.search(".") << endl;
    return 0;
}