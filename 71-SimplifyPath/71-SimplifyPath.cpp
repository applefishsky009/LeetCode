#include <stack>
#include <string>
#include <iostream>
using namespace std;

//经典题目，不过情况比较多样。
class Solution
{
  public:
    string simplifyPath(string path)
    {
        stack<string> sPath;
        size_t index = 0;
        while (index < path.size())
        { //遍历结束
            size_t tmp = path.find("/", index + 1);
            if (tmp == string::npos)
                tmp = path.size(); //防止最后一个路径没有以/结束，手动添加尾部
            if (tmp == index + 1)
            {
            }
            else if (path.substr(index + 1, tmp - index - 1) == ".")
            {
            }
            else if (path.substr(index + 1, tmp - index - 1) == "..")
            {
                if (!sPath.empty())
                    sPath.pop(); //如果返回上一层无法执行，继续找下一层目录
            }
            else
            {
                sPath.push(path.substr(index + 1, tmp - index - 1));
            }
            index = tmp; //"/"指针指向下一个
        }
        if (sPath.empty())
            return "/"; //当前目录，返回太多或者一直都是/////////
        string result;
        while (!sPath.empty())
        {
            result = "/" + sPath.top() + result;
            sPath.pop();
        }
        return result;
    }
};

int main()
{
    Solution s1;
    //string path = "/a/./b/../../c/";
    //string path = "/home/";
    //string path = "/../";
    //string path = "/home//foo/";
    //string path = "/";
    //string path = "/...";
    string path = "/a/./b///../c/../././../d/..//../e/./f/./g/././//.//h///././/..///";
    string result = s1.simplifyPath(path);
    cout << result << endl;
    return 0;
}