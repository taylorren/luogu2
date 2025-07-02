#include <deque>
#include <iostream>
#include <vector>

using namespace std;

// 使用单调队列求解滑动窗口最大值和最小值问题
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    // 同时求滑动窗口的最小值和最大值
    deque<int> min_q;  // 存储下标，单调递增队列（最小值队列）
    deque<int> max_q;  // 存储下标，单调递减队列（最大值队列）
    vector<int> min_values;
    vector<int> max_values;

    for (int i = 0; i < n; ++i)
    {
        // 处理最小值队列，移除队列中所有大于当前元素的值，保持单调性
        while (!min_q.empty() && a[min_q.back()] > a[i])
        {
            min_q.pop_back();
        }
        min_q.push_back(i);

        // 处理最大值队列，移除队列中所有小于当前元素的值，保持单调性
        while (!max_q.empty() && a[max_q.back()] < a[i])
        {
            max_q.pop_back();
        }
        max_q.push_back(i);

        // 移除两个队列中超出窗口范围的元素
        if (min_q.front() <= i - k)
        {
            min_q.pop_front();
        }
        if (max_q.front() <= i - k)
        {
            max_q.pop_front();
        }

        // 当窗口形成后，记录最小值和最大值
        if (i >= k - 1)
        {
            min_values.push_back(a[min_q.front()]);
            max_values.push_back(a[max_q.front()]);
        }
    }

    // 定义一个辅助函数来输出向量
    auto print_vector = [](const vector<int>& vec) {
        for (int i = 0; i < vec.size(); ++i) {
            cout << vec[i];
            if (i < vec.size() - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    };
    
    // 输出最小值
    print_vector(min_values);
    
    // 输出最大值
    print_vector(max_values);

    return 0;
}