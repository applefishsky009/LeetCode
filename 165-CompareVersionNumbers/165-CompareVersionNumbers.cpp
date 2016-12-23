#include <string>
#include <iostream>
using namespace std;

class Solution
{
  public:
    int compareVersion(string version1, string version2)
    {
        size_t pos1 = version1.find('.');
        size_t pos2 = version2.find('.');
        int versionNum1 = atoi(version1.substr(0, pos1).c_str());
        int versionNum2 = atoi(version2.substr(0, pos2).c_str());
        while (versionNum1 == versionNum2)
        {
            if (pos1 == string::npos && pos2 == string::npos) //equal
                return 0;
            size_t start1 = pos1;
            size_t start2 = pos2;
            pos1 = start1 == string::npos ? string::npos : version1.find('.', pos1 + 1); //wait at npos
            pos2 = start2 == string::npos ? string::npos : version2.find('.', pos2 + 1);
            versionNum1 = start1 == string::npos ? 0 : atoi(version1.substr(start1 + 1, pos1 - start1 - 1).c_str());
            versionNum2 = start2 == string::npos ? 0 : atoi(version2.substr(start2 + 1, pos2 - start2 - 1).c_str());
        }
        return versionNum1 > versionNum2 ? 1 : -1;
    }
};

class Solution1
{
  public:
    int compareVersion(string version1, string version2)
    {
        int i = 0;
        int j = 0;
        int n1 = version1.size();
        int n2 = version2.size();

        int num1 = 0;
        int num2 = 0;
        while (i < n1 || j < n2)
        {
            while (i < n1 && version1[i] != '.')
            {
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }

            while (j < n2 && version2[j] != '.')
            {
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }

            if (num1 > num2)
                return 1;
            else if (num1 < num2)
                return -1;

            num1 = 0;
            num2 = 0;
            i++;
            j++;
        }

        return 0;
    }
};

int main()
{
    Solution1 s1;
    string version1 = "1.0.2.0";
    string version2 = "1.0.2";
    cout << s1.compareVersion(version1, version2) << endl;
    return 0;
}