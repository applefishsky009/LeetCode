#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

//two charMap is needed. bar->foo OR foo->bar
class Solution
{
  public:
    bool isIsomorphic(const string &s, const string &t)
    {
        const int n = s.size();
        unordered_map<char, char> sCharMap;
        unordered_map<char, char> tCharMap;
        for (int i = 0; i < n; i++)
        {
            if (sCharMap.find(s[i]) == sCharMap.end() && tCharMap.find(t[i]) == tCharMap.end())
            {
                sCharMap[s[i]] = t[i];
                tCharMap[t[i]] = s[i];
            }
            else if (sCharMap.find(s[i]) == sCharMap.end() ||
                     tCharMap.find(t[i]) == tCharMap.end() ||
                     sCharMap[s[i]] != t[i] ||
                     tCharMap[t[i]] != s[i])
                return false;
        }
        return true;
    }
};

//vector -> map. code
class Solution1
{
  public:
    bool isIsomorphic(const string &s, const string &t)
    {
        int m1[256] = {0}, m2[256] = {0}, n = s.size();
        for (int i = 0; i < n; ++i)
        {
            if (m1[s[i]] != m2[t[i]])
                return false;
            m1[s[i]] = i + 1;
            m2[t[i]] = i + 1;
        }
        return true;
    }
};

int main()
{
    Solution1 s1;
    string s = "bar";
    string t = "foo";
    cout << s1.isIsomorphic(s, t) << endl;
    return 0;
}