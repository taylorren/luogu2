#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> heights(n);
    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }

    // 使用单调栈计算每头牛能看到的其他牛的数量
    stack<int> st;
    long long total = 0;

    // 从右到左遍历（从第N头牛到第1头牛）
    for (int i = n - 1; i >= 0; i--)
    {
        // 弹出栈中所有身高小于等于当前牛的牛
        while (!st.empty() && heights[st.top()] <= heights[i])
        {
            st.pop();
        }

        // 当前牛能看到的牛的数量就是它到栈顶牛之间的距离
        if (st.empty())
        {
            total += (n - 1 - i);  // 能看到右边所有的牛
        }
        else
        {
            total += (st.top() - i - 1);  // 能看到右边一部分牛
        }

        // 当前牛入栈
        st.push(i);
    }

    cout << total << endl;

    return 0;
}
