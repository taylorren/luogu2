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
    auto new_end = unique(sorted_coords.begin(), sorted_coords.end());
    sorted_coords.erase(new_end, sorted_coords.end());
    return sorted_coords;
}

// 使用标记法计算矩形面积并
long long calculateUnionAreaWithMarking(const vector<Rectangle>& rectangles)
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

    int x_size = x_discrete.size();
    int y_size = y_discrete.size();

    // 创建标记数组，标记哪些网格被覆盖
    vector<vector<bool>> covered(x_size - 1, vector<bool>(y_size - 1, false));

    // 对每个输入矩形进行标记
    for (const auto& rect : rectangles)
    {
        // 找到矩形在离散化坐标中的位置
        int x1_idx = lower_bound(x_discrete.begin(), x_discrete.end(), rect.x1) - x_discrete.begin();
        int x2_idx = lower_bound(x_discrete.begin(), x_discrete.end(), rect.x2) - x_discrete.begin();
        int y1_idx = lower_bound(y_discrete.begin(), y_discrete.end(), rect.y1) - y_discrete.begin();
        int y2_idx = lower_bound(y_discrete.begin(), y_discrete.end(), rect.y2) - y_discrete.begin();

        // 标记矩形覆盖的所有网格
        // 注意：y坐标系中y1 > y2（左上角到右下角）
        for (int i = x1_idx; i < x2_idx; i++)
        {
            for (int j = y2_idx; j < y1_idx; j++)
            {
                covered[i][j] = true;
            }
        }
    }

    // 计算被覆盖的总面积
    long long total_area = 0;
    for (int i = 0; i < x_size - 1; i++)
    {
        for (int j = 0; j < y_size - 1; j++)
        {
            if (covered[i][j])
            {
                long long width = x_discrete[i + 1] - x_discrete[i];
                long long height = y_discrete[j + 1] - y_discrete[j];
                total_area += width * height;
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

    long long result = calculateUnionAreaWithMarking(rectangles);
    cout << result << endl;

    return 0;
}