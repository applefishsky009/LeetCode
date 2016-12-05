#include <vector>
#include <limits>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

//三点共线：(x1 - x2)(y - y1) = (y1 - y2)(x - x1);
//定线找点式：时间复杂度O(n^3),空间复杂度O(1)
class Solution
{
  public:
    int maxPoints(vector<Point> &points)
    {
        if (points.size() < 3)
            return points.size();
        int maxNum = 0;
        for (int i = 0; i < points.size() - 1; ++i)
        {
            for (int j = i + 1; j < points.size(); ++j)
            {
                int sign = 0; //为什么需要sign?这是因为如果点集合中有两个点完全相同，就会判断无论什么点都和他们共线
                int a, b, c;  //因此设置一个标准使之不完全相同，一般考虑斜率。
                if (points[i].x == points[j].x)
                    sign = 1;
                else
                {
                    a = points[j].x - points[i].x;
                    b = points[j].y - points[i].y;
                    c = a * points[i].y - b * points[i].x;
                }
                int count = 0;
                for (int k = 0; k < points.size(); ++k)
                {
                    if ((0 == sign && a * points[k].y == c + b * points[k].x) ||
                        (1 == sign && points[k].x == points[j].x))
                        ++count;
                }
                if (count > maxNum)
                    maxNum = count;
            }
        }
        return maxNum;
    }
};

//定点找线式：时间复杂度O(n^2)，空间复杂度O(n)
//这道题有点DP的意思，对每一个点，可以选或者不选，不选就是f(n-1),选了就要建立更新Hash_Table
class Solution1
{
  public:
    int maxPoints(vector<Point> &points)
    {
        if (points.size() < 3)
            return points.size();
        int maxNum = 0;

        unordered_map<double, int> map;
        for (int i = 0; i < points.size() - 1; ++i)
        { //定点
            map.clear();
            int samePointNum = 0; //与i重合的最大点
            int point_max = 1;    //与i共线的最大点数
            for (int j = i + 1; j < points.size(); ++j)
            {
                //斜率
                double slop = 0.0;
                if (points[i].x == points[j].x)
                {
                    if (points[i].y == points[j].y)
                    {
                        ++samePointNum;
                        continue;
                    }
                    slop = numeric_limits<double>::infinity(); //double最大值
                }
                else
                    slop = 1.0 * (points[j].y - points[i].y) / (points[j].x - points[i].x);
                //共线的map
                int count = 0;
                if (map.count(slop) == 0)
                    map[slop] = 2;
                else
                    ++map[slop];
                ////每次共线更新 共线最多点
                if (map[slop] > point_max)
                    point_max = map[slop];
            }
            maxNum = max(maxNum, point_max + samePointNum); //共线和重合相加就是总数
        }
        return maxNum;
    }
};

int main()
{
    Solution1 s1;
    vector<Point> points(9);
    points[0] = Point(84, 250);
    points[1] = Point(0, 0);
    points[2] = Point(1, 0);
    points[3] = Point(0, -70);
    points[4] = Point(0, -70);
    points[5] = Point(1, -1);
    points[6] = Point(21, 10);
    points[7] = Point(42, 90);
    points[8] = Point(-42, -230);
    cout << s1.maxPoints(points) << endl;
    return 0;
}