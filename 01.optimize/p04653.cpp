#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
double a[N], b[N];

bool cmp(double a, double b)
{
    return a > b;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        a[i] += a[i - 1], b[i] += b[i - 1];
    double ans = 0;
    int i = 1, j = 1;
    while (i <= n && j <= n)
    {
        if (a[i] > b[j])
        {
            ans = max(ans, b[j] - i - j);
            j++;
        }
        else
        {
            ans = max(ans, a[i] - i - j);
            i++;
        }
    }
    printf("%.4lf", ans);
    return 0;
}