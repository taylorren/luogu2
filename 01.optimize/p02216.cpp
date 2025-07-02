#include <climits>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1005;

int a, b, n;
int matrix[MAXN][MAXN];
// 存储每行的滑动窗口最大值和最小值
int row_max[MAXN][MAXN], row_min[MAXN][MAXN];
// 存储最终的n×n区域的最大值和最小值
int col_max[MAXN][MAXN], col_min[MAXN][MAXN];

/**
 * 洛谷 P2216 - [HAOI2007]矩阵取数游戏
 * 在a×b的矩阵中找出一个n×n的正方形区域，使得该区域所有数中的最大值和最小值的差最小
 */

// 使用单调队列计算每行的滑动窗口最大值和最小值
void calc_row_max_min()
{
    for (int i = 0; i < a; ++i)
    {
        deque<int> max_q, min_q;

        // 处理第i行的所有元素
        for (int j = 0; j < b; ++j)
        {
            // 维护最大值单调队列
            while (!max_q.empty() && matrix[i][j] >= matrix[i][max_q.back()])
            {
                max_q.pop_back();
            }
            max_q.push_back(j);

            // 维护最小值单调队列
            while (!min_q.empty() && matrix[i][j] <= matrix[i][min_q.back()])
            {
                min_q.pop_back();
            }
            min_q.push_back(j);

            // 当窗口大小达到n时，计算结果并移除超出窗口范围的元素
            if (j >= n - 1)
            {
                // 移除超出窗口范围的元素
                while (!max_q.empty() && max_q.front() <= j - n)
                {
                    max_q.pop_front();
                }
                while (!min_q.empty() && min_q.front() <= j - n)
                {
                    min_q.pop_front();
                }

                // 当前窗口的最大值和最小值
                row_max[i][j - n + 1] = matrix[i][max_q.front()];
                row_min[i][j - n + 1] = matrix[i][min_q.front()];
            }
        }
    }
}

// 使用单调队列计算每列的滑动窗口最大值和最小值
void calc_col_max_min()
{
    for (int j = 0; j <= b - n; ++j)
    {
        deque<int> max_q, min_q;

        // 处理第j列的所有元素
        for (int i = 0; i < a; ++i)
        {
            // 维护最大值单调队列
            while (!max_q.empty() && row_max[i][j] >= row_max[max_q.back()][j])
            {
                max_q.pop_back();
            }
            max_q.push_back(i);

            // 维护最小值单调队列
            while (!min_q.empty() && row_min[i][j] <= row_min[min_q.back()][j])
            {
                min_q.pop_back();
            }
            min_q.push_back(i);

            // 当窗口大小达到n时，计算结果并移除超出窗口范围的元素
            if (i >= n - 1)
            {
                // 移除超出窗口范围的元素
                while (!max_q.empty() && max_q.front() <= i - n)
                {
                    max_q.pop_front();
                }
                while (!min_q.empty() && min_q.front() <= i - n)
                {
                    min_q.pop_front();
                }

                // 当前窗口的最大值和最小值
                col_max[i - n + 1][j] = row_max[max_q.front()][j];
                col_min[i - n + 1][j] = row_min[min_q.front()][j];
            }
        }
    }
}

int main()
{
    cin >> a >> b >> n;

    // 读入矩阵
    for (int i = 0; i < a; ++i)
    {
        for (int j = 0; j < b; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    // 如果n为1，直接输出0（单个元素的最大值和最小值相同，差值为0）
    if (n == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    // 计算每行的滑动窗口最大值和最小值
    calc_row_max_min();

    // 计算每列的滑动窗口最大值和最小值
    calc_col_max_min();

    // 找出所有n×n区域中最大值和最小值的差的最小值
    int min_diff = INT_MAX;
    for (int i = 0; i <= a - n; ++i)
    {
        for (int j = 0; j <= b - n; ++j)
        {
            int diff = col_max[i][j] - col_min[i][j];
            min_diff = min(min_diff, diff);
        }
    }

    cout << min_diff << endl;

    return 0;
}