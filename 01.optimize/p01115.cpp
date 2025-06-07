#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    // 初始化当前子数组和和最大子数组和
    int current_sum = a[0];
    int max_sum = a[0];

    // 使用Kadane算法遍历数组
    for (int i = 1; i < n; ++i)
    {
        // 当前子数组和要么包含前一个元素的和，要么从当前元素重新开始
        current_sum = max(a[i], current_sum + a[i]);

        // 更新最大子数组和
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << endl;
    return 0;
}