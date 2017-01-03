#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        const int n = s.size();
        assert(n >= 10);
        unordered_map<string, int> strSet;
        vector<string> res;
        for (int i = 0; i <= n - 10; i++)
        {
            string tmp = s.substr(i, 10);
            if (strSet.find(tmp) == strSet.end())
                strSet[tmp] = 1;
            else if (strSet[tmp] == 1)
            {
                res.push_back(tmp);
                strSet[tmp]++;
            }
        }
        return res;
    }
};

//code<->decode,A=41,C=43,G=47,T=54
//A%5 = 1; C%5 = 3; G%5 = 2; T%5 = 4;----need two bits
//0xFFFFF is 20 bits.just 10*2 char what is we need.
class Solution1
{
  public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        char hashMap[1048576] = {0};
        vector<string> ans;
        int len = s.size(), hashNum = 0;
        if (len < 11)
            return ans;
        for (int i = 0; i < 9; ++i)
            hashNum = hashNum << 2 | (s[i] - 'A' + 1) % 5;
        for (int i = 9; i < len; ++i)
        {
            hashNum = (hashNum << 2 | (s[i] - 'A' + 1) % 5) & 0xfffff;
            if (hashMap[hashNum] == 0)
                hashMap[hashNum]++;
            else if (hashMap[hashNum] == 1)
            {
                hashMap[hashNum]++;
                ans.push_back(s.substr(i - 9, 10));
            }
        }
        return ans;
    }
};

int main()
{
    Solution1 s1;
    string s = "AAAAAAAAAAAA";
    vector<string> res = s1.findRepeatedDnaSequences(s);
    show1DVector(res);
    return 0;
}