#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/**
 * 洛谷 P4147 - 玉蟾宫
 * 求最大全F矩形面积问题
 * 使用单调栈算法求解
 */
int main()
{
    int n, m;
    cin >> n >> m;

    // 读取地图
    vector<vector<char>> land(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> land[i][j];
        }
    }

    // 计算每个位置的高度（连续的F的数量）
    vector<vector<int>> heights(n, vector<int>(m, 0));
    for (int j = 0; j < m; ++j)
    {
        heights[0][j] = (land[0][j] == 'F') ? 1 : 0;
        for (int i = 1; i < n; ++i)
        {
            if (land[i][j] == 'F')
            {
                heights[i][j] = heights[i - 1][j] + 1;
            }
            else
            {
                heights[i][j] = 0;
            }
        }
    }

    // 对每一行使用单调栈计算最大矩形面积
    int max_area = 0;
    for (int i = 0; i < n; ++i)
    {
        stack<int> s;
        vector<int> left(m, 0), right(m, m);

        // 计算左边界
        for (int j = 0; j < m; ++j)
        {
            while (!s.empty() && heights[i][s.top()] >= heights[i][j])
            {
                s.pop();
            }
            left[j] = s.empty() ? 0 : s.top() + 1;
            s.push(j);
        }

        // 清空栈
        while (!s.empty())
            s.pop();

        // 计算右边界
        for (int j = m - 1; j >= 0; --j)
        {
            while (!s.empty() && heights[i][s.top()] >= heights[i][j])
            {
                s.pop();
            }
            right[j] = s.empty() ? m : s.top();
            s.push(j);
        }

        // 计算最大面积
        for (int j = 0; j < m; ++j)
        {
            int area = heights[i][j] * (right[j] - left[j]);
            max_area = max(max_area, area);
        }
    }

    // 输出结果（3倍的最大面积）
    cout << 3 * max_area << endl;

    return 0;
}