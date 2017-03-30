#include <vector>
#include <memory.h>
#include <iostream>
using namespace std;

//MultipleTree(S = num of char) achive trie.
//note that 2-D vector can not describe trie. because the prefix is confused.
//"abc" & "bcd" so "acd" is in trie?

struct node
{
    bool endFlag;
    vector<node *> pre;
    node() : endFlag(false)
    {
        pre = vector<node *>(26, nullptr);
    };
};

class Trie
{
  private:
    node *trie;
    node *find(string word)
    {
        node *p = trie;
        for (int i = 0; i < word.size() && p; i++)
            p = p->pre[word[i] - 'a'];
        return p;
    }

  public:
    /** Initialize your data structure here. */
    Trie()
    {
        trie = new node();
    }
    /** Inserts a word into the trie. */
    void insert(string word)
    {
        node *p = trie;
        for (int i = 0; i < word.size(); i++)
        {
            if (!p->pre[word[i] - 'a'])
                p->pre[word[i] - 'a'] = new node();
            p = p->pre[word[i] - 'a'];
        }
        p->endFlag = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        node *p = find(word);
        return p && p->endFlag;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        return find(prefix);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

int main()
{
    Trie obj = Trie();
    obj.insert("");
    obj.insert("search");
    cout << obj.search("") << endl;
    cout << obj.search("a") << endl;
    return 0;
}
