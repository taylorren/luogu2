#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Rectangle
{
    long long x1, y1, x2, y2;  // (x1,y1) 左上角, (x2,y2) 右下角

    Rectangle(long long x1, long long y1, long long x2, long long y2)
        : x1(x1), y1(y1), x2(x2), y2(y2)
    {
    }
};

// 坐标离散化函数
vector<long long> discretize(const vector<long long>& coords)
{
    vector<long long> sorted_coords = coords;
    sort(sorted_coords.begin(), sorted_coords.end());
    sorted_coords.erase(unique(sorted_coords.begin(), sorted_coords.end()),
                        sorted_coords.end());
    return sorted_coords;
}

// 计算矩形面积并
long long calculateUnionArea(const vector<Rectangle>& rectangles)
{
    if (rectangles.empty())
        return 0;

    // 收集所有x和y坐标
    vector<long long> x_coords, y_coords;
    for (const auto& rect : rectangles)
    {
        x_coords.push_back(rect.x1);
        x_coords.push_back(rect.x2);
        y_coords.push_back(rect.y1);
        y_coords.push_back(rect.y2);
    }

    // 坐标离散化
    vector<long long> x_discrete = discretize(x_coords);
    vector<long long> y_discrete = discretize(y_coords);

    long long total_area = 0;

    // 遍历所有可能的小矩形
    for (int i = 0; i < x_discrete.size() - 1; i++)
    {
        for (int j = 0; j < y_discrete.size() - 1; j++)
        {
            long long left = x_discrete[i];
            long long right = x_discrete[i + 1];
            long long bottom = y_discrete[j];
            long long top = y_discrete[j + 1];

            // 检查这个小矩形是否被任何输入矩形覆盖
            bool covered = false;
            for (const auto& rect : rectangles)
            {
                // 矩形覆盖条件：左上角(x1,y1)，右下角(x2,y2)
                // 小矩形在大矩形内部的条件
                if (rect.x1 <= left && right <= rect.x2 && rect.y2 <= bottom &&
                    top <= rect.y1)
                {
                    covered = true;
                    break;
                }
            }

            if (covered)
            {
                total_area += (right - left) * (top - bottom);
            }
        }
    }

    return total_area;
}

int main()
{
    int n;
    cin >> n;

    vector<Rectangle> rectangles;
    rectangles.reserve(n);

    for (int i = 0; i < n; i++)
    {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rectangles.emplace_back(x1, y1, x2, y2);
    }

    long long result = calculateUnionArea(rectangles);
    cout << result << endl;

    return 0;
}