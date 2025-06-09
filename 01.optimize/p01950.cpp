#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;

char grid[MAX][MAX];
int left_border[MAX], right_border[MAX];
int heights[MAX][MAX];

int main()
{
    long long ans = 0;
    int n, m;
    cin >> n >> m;

    // 读入原始地图
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> grid[i][j];
        }
    }

    // 从第1行开始
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (grid[i][j] == '*')  // *表示用过了，或者说障碍
            {
                heights[i][j] = 0;
            }
            else
            {
                heights[i][j] = heights[i - 1][j] + 1;
            }
        }
    }

    // 开始找每一行各列的左边界、右边界
    for (int i = 1; i <= n; i++)
    {
        // 找左边界
        stack<int> s;
        for (int j = 1; j <= m; j++)
        {
            while (!s.empty() && heights[i][s.top()] >= heights[i][j])
            {
                s.pop();
            }
            if (s.empty())
            {
                left_border[j] = 0;
            }
            else
            {
                left_border[j] = s.top();
            }
            s.push(j);
        }
        // 找右边界
        stack<int> s2;
        for (int j = m; j >= 1; j--)
        {
            while (!s2.empty() && heights[i][s2.top()] > heights[i][j])
            {
                s2.pop();
            }
            if (s2.empty())
            {
                right_border[j] = m + 1;
            }
            else
            {
                right_border[j] = s2.top();
            }
            s2.push(j);
        }
        // 计算面积
        for (int j = 1; j <= m; j++)
        {
            ans+=heights[i][j]*(right_border[j]-j)*(j-left_border[j]);
        }
    }
    cout << ans << endl;
    return 0;
}