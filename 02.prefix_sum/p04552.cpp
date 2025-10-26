#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    // 特殊情况：只有一个数
    if (n == 1)
    {
        cout << "0\n1\n";
        return 0;
    }

    // 计算差分数组
    vector<long long> diff(n + 1);
    diff[1] = a[1];  // diff[1] = a[1]
    for (int i = 2; i <= n; i++)
    {
        diff[i] = a[i] - a[i - 1];
    }

    // 重新分析最少操作次数
    // 关键洞察：正的diff[i]需要减少，负的diff[i]需要增加
    // 通过巧妙的区间操作，可以同时处理正负diff

    long long pos_sum = 0, neg_sum = 0;
    for (int i = 2; i <= n; i++)
    {
        if (diff[i] > 0)
        {
            pos_sum += diff[i];
        }
        else if (diff[i] < 0)
        {
            neg_sum += abs(diff[i]);
        }
    }

    // 最少操作次数 = max(pos_sum, neg_sum)
    // 因为可以通过区间操作同时处理正负diff
    long long min_operations = max(pos_sum, neg_sum);

    //我们最终得到的是一个`diff[1], 0, 0, .... 0`的差分数组。它保证所有的数字都是一样的。因此有几种答案，取决于`diff[1]`可以有怎样的取值范围。我们有$min(pos\_sum, neg\_sum)$次操作是互相抵消的。而多出来次数的操作，可以一次都不包括`diff[1]`，也可以每次都包括`diff[1]`，所以`diff[1]`的取值范围从`0`到`abs(pos_num-neg_num)`，也就是$abs(pos\_sum-neg\_sum)+1$。
    
    long long result_count = abs(pos_sum - neg_sum) + 1;

    cout << min_operations << "\n";
    cout << result_count << "\n";

    return 0;
}