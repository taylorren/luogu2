#include <bits/stdc++.h>
using namespace std;

const int MAX = 600;
int counting[MAX + 10];

int main()
{
    int n, w;
    cin >> n >> w;
    for (int i = 1; i <= n; ++i)
    {
        int tmp;
        cin >> tmp;
        counting[tmp]++;  // 木桶计数，记录每个分数的数量

        int total = 0;
        for (int j = MAX; j >= 0; --j)
        {
            total += counting[j];
            if (total >= max(1, i * w / 100))
            {
                cout << j << " ";
                break;
            }
        }
    }

    return 0;
}