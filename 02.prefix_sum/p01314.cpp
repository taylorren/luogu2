#include <bits/stdc++.h>
using namespace std;

struct Mine
{
    int weight;
    int value;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int mines_count, ranges_count;
    long long weight;
    cin >> mines_count >> ranges_count >> weight;

    int left = 1, right = -1;

    vector<Mine> mines(mines_count + 1);
    for (int i = 1; i <= mines_count; i++)
    {
        cin >> mines[i].weight >> mines[i].value;
        right = max(right, mines[i].weight);
    }
    right++; // search range [left, right]

    vector<long long> pre_sum_count(mines_count + 1, 0),
        pre_sum_value(mines_count + 1, 0);

    vector<pair<int, int>> ranges(ranges_count + 1);
    ranges[0] = {0, 0};
    for (int i = 1; i <= ranges_count; i++)
    {
        cin >> ranges[i].first >> ranges[i].second;
    }

    long long variance = LLONG_MAX;

    while (left < right)
    {
        int mid = (left + right) / 2;

        // build prefix sums (1-based)
        pre_sum_count[0] = 0;
        pre_sum_value[0] = 0;
        //根据mid值，计算前缀和
        for (int i = 1; i <= mines_count; i++)
        {
            if (mines[i].weight >= mid)
            {
                pre_sum_count[i] = pre_sum_count[i - 1] + 1;
                pre_sum_value[i] = pre_sum_value[i - 1] + mines[i].value;
            }
            else
            {
                pre_sum_count[i] = pre_sum_count[i - 1];
                pre_sum_value[i] = pre_sum_value[i - 1];
            }
        }

        // 计算当前选择的weight(mid)下的值
        long long sum = 0;
        for (int i = 1; i <= ranges_count; i++)
        {
            int L = ranges[i].first;
            int R = ranges[i].second;
            
            long long cnt = pre_sum_count[R] - pre_sum_count[L - 1];
            long long val = pre_sum_value[R] - pre_sum_value[L - 1];
            sum += cnt * val;
        }

        if (sum == weight)
        {
            variance = 0;
            break;
        }
        variance = min(variance, llabs(sum - weight));

        if (sum < weight)
            right = mid;
        else
            left = mid + 1;
    }

    cout << variance << '\n';
    return 0;
}