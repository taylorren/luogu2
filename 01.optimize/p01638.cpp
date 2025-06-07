#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * 寻找包含所有m位画家作品的最小区间
 * 使用滑动窗口算法解决
 */
int main()
{
    // 输入图画总数n和画家数量m
    int n, m;
    cin >> n >> m;

    // 存储每幅画的作者编号
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    // 哈希表记录窗口中每个画家的出现次数
    unordered_map<int, int> count;

    // 滑动窗口的左右边界
    int left = 0;

    // 记录最小窗口长度和对应的左右边界
    int min_len = n;
    int result_left = 0;
    int result_right = n - 1;

    // 记录窗口中不同画家的数量
    int unique = 0;

    // 滑动窗口算法主循环
    for (int right = 0; right < n; ++right)
    {
        // 如果当前画家第一次出现在窗口中，增加unique计数
        if (count[a[right]] == 0)
        {
            unique++;
        }
        // 增加当前画家的计数
        count[a[right]]++;

        // 当窗口包含所有画家时，尝试收缩左边界
        while (unique == m)
        {
            // 如果找到更小的窗口，更新记录
            if (right - left + 1 < min_len)
            {
                min_len = right - left + 1;
                result_left = left;
                result_right = right;
            }

            // 移动左边界，减少左边画家的计数
            count[a[left]]--;

            // 如果某个画家的计数减到0，减少unique计数
            if (count[a[left]] == 0)
            {
                unique--;
            }

            // 左边界右移
            left++;
        }
    }

    // 输出结果，题目要求从1开始计数，所以+1
    cout << result_left + 1 << " " << result_right + 1 << endl;
    return 0;
}