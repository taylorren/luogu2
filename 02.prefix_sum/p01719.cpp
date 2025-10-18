#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n))
        return 0;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> a[i][j];
        }
    }
    long long ans = LLONG_MIN;
    vector<long long> col(n);
    for (int top = 0; top < n; ++top)
    {
        fill(col.begin(), col.end(), 0);
        for (int bottom = top; bottom < n; ++bottom)
        {
            for (int j = 0; j < n; ++j)
            {
                col[j] += a[bottom][j];
            }
            
            // Kadane on col[], handle all-negative correctly
            long long cur = col[0], best = col[0];
            for (int j = 1; j < n; ++j)
            {
                // 要么从当前列重新开始（col[j]），
                // 要么接在之前的区间后面（cur + col[j]）
                cur = max(col[j], cur + col[j]);
                best = max(best, cur);
            }
            ans = max(ans, best);
        }
    }

    cout << ans << '\n';
    return 0;
}