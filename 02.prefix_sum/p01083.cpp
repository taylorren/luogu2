#include <iostream>
#include <vector>
using namespace std;

struct Order
{
    int d, s, t;  // 需求量，开始天，结束天
};

// 检查前k个订单是否都能满足
bool canSatisfy(int k, const vector<int>& rooms, const vector<Order>& orders)
{
    int n = rooms.size() - 1;          // rooms[1..n]
    vector<long long> diff(n + 2, 0);  // 差分数组

    // 处理前k个订单 (orders[1..k])
    for (int i = 1; i <= k; i++)
    {
        diff[orders[i].s] += orders[i].d;
        diff[orders[i].t + 1] -= orders[i].d;
    }

    // 还原实际使用量并检查
    long long used = 0;
    for (int day = 1; day <= n; day++)
    {
        used += diff[day];
        if (used > rooms[day])
        {
            return false;  // 第day天教室不够
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> rooms(n + 1);  // rooms[1..n]
    for (int i = 1; i <= n; i++)
    {
        cin >> rooms[i];
    }

    vector<Order> orders(m + 1);  // orders[1..m] 1-based
    for (int i = 1; i <= m; i++)
    {
        cin >> orders[i].d >> orders[i].s >> orders[i].t;
    }

    // 二分答案：找第一个无法满足的订单
    int left = 1, right = m;
    int result = -1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (canSatisfy(mid, rooms, orders))
        {
            left = mid + 1;
        }
        else
        {
            result = mid;
            right = mid - 1;
        }
    }

    if (result == -1)
    {
        // 所有订单都能满足
        cout << 0 << endl;
    }
    else
    {
        cout << -1 << endl;
        cout << result << endl;  // 第result个订单无法满足（1-indexed）
    }

    return 0;
}