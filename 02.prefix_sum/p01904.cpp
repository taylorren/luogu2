#include <bits/stdc++.h>
using namespace std;

struct Building
{
    int left, height, right;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Building> buildings;
    int l, h, r;

    // 读取所有建筑
    while (cin >> l >> h >> r)
    {
        buildings.push_back({l, h, r});
    }

    // 离散化：收集所有关键坐标
    vector<int> coords;
    for (const auto& building : buildings)
    {
        coords.push_back(building.left);
        coords.push_back(building.right);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    // 对每个离散化区间维护最大高度
    int n = coords.size();
    vector<int> maxHeight(n - 1, 0);

    for (const auto& building : buildings)
    {
        int leftIdx = lower_bound(coords.begin(), coords.end(), building.left) -
                      coords.begin();
        int rightIdx =
            lower_bound(coords.begin(), coords.end(), building.right) -
            coords.begin();

        for (int i = leftIdx; i < rightIdx; i++)
        {
            maxHeight[i] = max(maxHeight[i], building.height);
        }
    }

    // 生成轮廓线
    vector<int> result;
    int currentHeight = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (maxHeight[i] != currentHeight)
        {
            result.push_back(coords[i]);
            result.push_back(maxHeight[i]);
            currentHeight = maxHeight[i];
        }
    }

    // 最后回到地面高度0
    if (currentHeight != 0)
    {
        result.push_back(coords[n - 1]);
        result.push_back(0);
    }

    // 输出
    for (int i = 0; i < result.size(); i++)
    {
        if (i > 0)
            cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}