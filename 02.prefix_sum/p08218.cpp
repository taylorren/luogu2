#include <bits/stdc++.h>
using namespace std;

/**
 * 问题：区间和查询
 * 描述：给定n个正整数组成的序列和m个区间[l,r]，求每个区间内的元素和
 * 解法：使用前缀和技术，将查询时间复杂度从O(n*m)优化到O(n+m)
 */

int main()
{
    // 优化输入输出速度
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 读取序列，下标从1开始便于计算前缀和
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }

    // 计算前缀和数组
    // prefix_sum[i]表示a[1]到a[i]的和
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    int m;
    cin >> m;

    // 处理区间查询
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        cin >> l >> r;

        // 使用前缀和计算区间[l,r]的和
        // 区间和 = prefix_sum[r] - prefix_sum[l-1]
        long long interval_sum = prefix_sum[r] - prefix_sum[l - 1];
        cout << interval_sum << "\n";
    }

    return 0;
}