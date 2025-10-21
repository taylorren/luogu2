#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n))
        return 0;
    vector<pair<long long, long long>> seg;
    seg.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        long long a, b;
        cin >> a >> b;
        seg.emplace_back(a, b);
    }

    sort(seg.begin(), seg.end());  // sort by left then right

    long long ans = 0;
    if (!seg.empty())
    {
        long long L = seg[0].first;
        long long R = seg[0].second;
        for (size_t i = 1; i < seg.size(); ++i)
        {
            long long a = seg[i].first;
            long long b = seg[i].second;
            if (a < R)
            {
                // overlap (left-closed, right-open): merge when a < R
                if (b > R)
                    R = b;
            }
            else
            {
                // disjoint or just touching (a >= R)
                ans += R - L;
                L = a;
                R = b;
            }
        }
        ans += R - L;
    }

    cout << ans << '\n';
    return 0;
}