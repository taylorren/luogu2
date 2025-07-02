#include <bits/stdc++.h>
using namespace std;

// 存放障碍点（产奶点）信息的结构体
struct Point
{
    int x, y;

    // 构造函数
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

// 按横坐标排序的比较函数
auto cmpByX = [](const Point& a, const Point& b)
{ return a.x == b.x ? a.y < b.y : a.x < b.x; };

// 按纵坐标排序的比较函数
auto cmpByY = [](const Point& a, const Point& b)
{ return a.y == b.y ? a.x < b.x : a.y < b.y; };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, w, n;
    cin >> l >> w >> n;

    // 使用vector存储障碍点
    vector<Point> points;
    points.reserve(n + 4);  // 预分配空间（包括四个顶点）

    // 读取所有产奶点
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    // 将牛场的四个顶点添加为障碍点
    points.emplace_back(0, 0);
    points.emplace_back(0, w);
    points.emplace_back(l, 0);
    points.emplace_back(l, w);
    n += 4;  // 更新点的总数
    // 计算最大矩形面积
    int max_area = 0;

    // 从左往右扫描
    sort(points.begin(), points.end(), cmpByX);

    for (int i = 0; i < n; ++i)
    {
        int x1 = points[i].x;
        int y1 = 0, y2 = w;

        for (int j = i + 1; j < n; ++j)
        {
            int x2 = points[j].x;
            // 计算当前矩形面积并更新最大值
            max_area = max(max_area, (x2 - x1) * (y2 - y1));

            // 更新上下边界
            if (points[j].y < points[i].y)
            {
                y1 = max(y1, points[j].y);
            }
            else
            {
                y2 = min(y2, points[j].y);
            }
        }
    }

    // 从右往左扫描
    for (int i = n - 1; i >= 0; --i)
    {
        int x1 = points[i].x;
        int y1 = 0, y2 = w;

        for (int j = i - 1; j >= 0; --j)
        {
            int x2 = points[j].x;
            // 计算当前矩形面积并更新最大值
            max_area = max(max_area, (x1 - x2) * (y2 - y1));

            // 更新上下边界
            if (points[j].y < points[i].y)
            {
                y1 = max(y1, points[j].y);
            }
            else
            {
                y2 = min(y2, points[j].y);
            }
        }
    }

    // 处理特殊情况：按纵坐标排序，检查相邻点之间的空隙
    sort(points.begin(), points.end(), cmpByY);
    for (int i = 0; i < n - 1; ++i)
    {
        max_area = max(max_area, l * (points[i + 1].y - points[i].y));
    }

    // 输出结果
    cout << max_area << endl;

    return 0;
}