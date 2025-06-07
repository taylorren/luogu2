#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
const int maxn = 1e5 + 10;

int n, m;
int a[maxn], b[maxn];
int s1[maxn][2], s2[maxn][2];

int ans;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        s1[b[i]][i % 2]++;
        s2[b[i]][i % 2] = (s2[b[i]][i % 2] + a[i]) % mod;
    }

    for (int i = 1; i <= n; i++)
    {
        int y = b[i];
        ans += i * (s2[y][i % 2] + a[i] * (s1[y][i % 2] - 2) % mod) % mod;
        ans %= mod;
    }

    cout << ans << endl;
    return 0;
}