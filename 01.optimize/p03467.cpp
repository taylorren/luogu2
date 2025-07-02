#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 使用单调栈算法计算需要的海报数量
    int poster_count = n;  // 初始海报数为建筑物数
    stack<int> s;          // 单调栈，存储建筑物高度

    for (int i = 0; i < n; ++i)
    {
        int length, height;
        cin >> length >> height;  // 读取长度和高度，但只使用高度

        // 当栈不为空且栈顶高度大于当前高度时，弹栈
        while (!s.empty() && s.top() > height)
        {
            s.pop();
        }

        // 如果栈顶元素与当前高度相等，需要的海报数减1
        if (!s.empty() && s.top() == height)
        {
            poster_count--;
        }
        else
        {
            // 否则将当前高度入栈
            s.push(height);
        }
    }

    cout << poster_count << endl;

    return 0;
}