#include <cstdio>
#include <iostream>
using namespace std;

int rows, cols, horizontal_strips, vertical_pieces;
int grid[501][501], prefix_sum[501][501];
int max_guaranteed_beans;

// Helper function to calculate rectangle sum using 2D prefix sum
int get_rectangle_sum(int r1, int c1, int r2, int c2) {
    return prefix_sum[r2][c2] - prefix_sum[r1-1][c2] - 
           prefix_sum[r2][c1-1] + prefix_sum[r1-1][c1-1];
}

// 检查是否能保证Bessie至少得到min_beans个巧克力豆 (修正版)
bool can_guarantee_min_beans(int min_beans)
{
    int strip_start_row = 0;   // 当前条带的起始行
    int completed_strips = 0;  // 已完成的水平条带数量

    for (int current_row = 1; current_row <= rows; current_row++)
    {
        int piece_start_col = 1;   // 当前垂直块的起始列
        int pieces_in_strip = 0;   // 当前条带中的垂直块数量

        for (int col = 1; col <= cols; col++)
        {
            // 计算当前垂直块的巧克力豆总数 [strip_start_row+1, piece_start_col] 到 [current_row, col]
            int piece_beans = get_rectangle_sum(strip_start_row + 1, piece_start_col, 
                                              current_row, col);

            // 如果当前块已经满足最小要求，就切割形成一个垂直块
            if (piece_beans >= min_beans)
            {
                pieces_in_strip++;
                piece_start_col = col + 1;  // 下一个垂直块从下一列开始
            }
        }

        // 检查当前条带是否能分出足够的垂直块
        if (pieces_in_strip >= vertical_pieces)
        {
            strip_start_row = current_row;  // 当前条带成功，下一条带从下一行开始
            completed_strips++;
        }
    }

    // 检查是否完成了足够的水平条带
    return completed_strips >= horizontal_strips;
}

int main()
{
    cin >> rows >> cols >> horizontal_strips >> vertical_pieces;

    // 读取网格数据
    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
            cin >> grid[i][j];

    // 计算二维前缀和
    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] +
                               grid[i][j] - prefix_sum[i - 1][j - 1];

    // 二分搜索答案：在[0, average]范围内找最大可行值
    int left = 0, right = prefix_sum[rows][cols] / (horizontal_strips * vertical_pieces);

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (can_guarantee_min_beans(mid))
        {
            left = mid + 1;
            max_guaranteed_beans = mid;  // 更新答案
        }
        else
        {
            right = mid - 1;
        }
    }

    cout << max_guaranteed_beans << endl;
    return 0;
}