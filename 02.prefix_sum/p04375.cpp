#include <bits/stdc++.h>
using namespace std;

// 计算修改后的冒泡（双向鸡尾酒排序）“moo”的次数：
// 等于所有相邻边界中最大“需要从右到左穿越”的元素数，至少为 1。
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N))
        return 0;

    vector<pair<long long, int>> a(N + 1);
    for (int i = 1; i <= N; ++i)
    {
        long long x;
        cin >> x;
        a[i] = {x, i};  // 值，原始下标（1-based）
    }

    // 按值升序，值相同按原始下标升序（稳定）
    sort(a.begin() + 1, a.end(),
         [](const auto& x, const auto& y)
         {
             if (x.first != y.first)
                 return x.first < y.first;
             return x.second < y.second;
         });

    int ans = 1, cnt = 0;
    vector<char> vis(N + 2, 0);

    // 扫描最终位置 i，统计需要跨越边界的“开放区间”数目
    for (int i = 1; i <= N; ++i)
    {
        // 若该元素的原下标在当前位置 i 的右侧，开启一个穿越区间 [i, a[i].second)
        // 该元素需要从右到左穿越，才能到达当前位置 i，计数+1
        if (i < a[i].second)
            cnt++;
        // 若此前标记过有区间以边界 i 为右端点（原下标==i），在此关闭该区间
        if (vis[i])
            cnt--;
        // 标记当前元素的原下标作为一个区间的右端点，供未来走到该下标时关闭（先关后标记，避免同位次干扰）
        vis[a[i].second] = 1;

        ans = max(ans, cnt);
    }

    cout << ans << '\n';
    return 0;
}