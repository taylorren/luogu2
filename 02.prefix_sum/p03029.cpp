#include <bits/stdc++.h>
using namespace std;

struct Cow
{
    int x;      // x坐标
    int breed;  // 品种ID
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Cow> cows(n);
    unordered_set<int> all_breeds;

    for (int i = 0; i < n; i++)
    {
        cin >> cows[i].x >> cows[i].breed;
        all_breeds.insert(cows[i].breed);
    }

    // 按x坐标排序
    sort(cows.begin(), cows.end(),
         [](const Cow& a, const Cow& b) { return a.x < b.x; });

    int total_breeds = all_breeds.size();
    int min_cost = INT_MAX;

    // 滑动窗口
    int left = 0;
    unordered_map<int, int> window_breeds;  // 当前窗口中每个品种的数量

    for (int right = 0; right < n; right++)
    {
        // 扩展右边界
        window_breeds[cows[right].breed]++;

        // 当窗口包含所有品种时，尝试缩小左边界
        while (window_breeds.size() == total_breeds)
        {
            // 更新最小成本
            int cost = cows[right].x - cows[left].x;
            min_cost = min(min_cost, cost);

            // 缩小左边界
            window_breeds[cows[left].breed]--;
            if (window_breeds[cows[left].breed] == 0)
            {
                window_breeds.erase(cows[left].breed);
            }
            left++;
        }
    }

    cout << min_cost << endl;

    return 0;
}