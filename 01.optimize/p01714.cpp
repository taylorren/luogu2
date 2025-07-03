#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1, 0);
    vector<long long> prefix_sum(n + 1, 0);

    // 读入蛋糕的幸运值并计算前缀和
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    // 使用单调队列维护可能的最小前缀和
    deque<int> q;
    long long max_sum = -1e18;  // 初始化为一个很小的值

    // 初始时将0加入队列（代表空子段）
    q.push_back(0);

    for (int i = 1; i <= n; i++)
    {
        // 如果队首元素已经超出了长度限制m，将其弹出
        while (!q.empty() && i - q.front() > m)
        {
            q.pop_front();
        }

        // 计算以当前位置结尾的最大子段和
        if (!q.empty())
        {
            max_sum = max(max_sum, prefix_sum[i] - prefix_sum[q.front()]);
        }

        // 维护单调队列，保证队列中的元素对应的前缀和是单调递增的
        while (!q.empty() && prefix_sum[q.back()] >= prefix_sum[i])
        {
            q.pop_back();
        }

        q.push_back(i);
    }

    cout << max_sum << endl;

    return 0;
}