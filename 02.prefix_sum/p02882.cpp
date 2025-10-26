#include <bits/stdc++.h>
using namespace std;

// 对于给定的K，计算最小操作次数（差分数组版本）
int solve(int N, int K, const vector<int>& cows)
{
    vector<int> state = cows;    // 复制原始状态
    vector<int> diff(N + 1, 0);  // 差分数组，记录翻转操作
    int operations = 0;
    int flip_count = 0;  // 当前位置受到的翻转次数

    for (int i = 0; i < N; i++)
    {
        // 更新当前位置的翻转次数
        flip_count += diff[i];

        // 计算当前牛的实际朝向（原始朝向 + 翻转次数的奇偶性）
        int current_direction = (state[i] + flip_count) % 2;

        // 如果当前牛朝后(0)，需要翻转
        if (current_direction == 0)
        {
            // 检查是否能进行K长度的翻转
            if (i + K > N)
            {
                return INT_MAX;  // 无法完成翻转
            }

            // 使用差分数组记录翻转操作：[i, i+K) 区间翻转
            diff[i]++;
            diff[i + K]--;
            flip_count++;  // 当前位置立即受到翻转影响
            operations++;
        }
    }

    return operations;
}

// 直观版本：直接跟踪翻转次数（适合理解）
int solve_simple(int N, int K, const vector<int>& cows)
{
    vector<int> flip_times(N, 0);  // 每个位置被翻转的次数
    int operations = 0;

    for (int i = 0; i < N; i++)
    {
        // 计算当前牛的实际朝向
        int current_direction = (cows[i] + flip_times[i]) % 2;

        if (current_direction == 0)
        {  // 朝后，需要翻转
            if (i + K > N)
                return INT_MAX;  // 无法翻转

            // 直接更新K个位置的翻转次数
            for (int j = i; j < i + K; j++)
            {
                flip_times[j]++;
            }
            operations++;
        }
    }

    return operations;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> cows(N);
    for (int i = 0; i < N; i++)
    {
        char c;
        cin >> c;
        cows[i] = (c == 'F') ? 1 : 0;  // F=1(朝前), B=0(朝后)
    }

    int best_K = 1;
    int min_operations = INT_MAX;

    // 枚举所有可能的K值
    for (int K = 1; K <= N; K++)
    {
        int operations = solve(N, K, cows);  // 使用差分数组版本

        if (operations < min_operations)
        {
            min_operations = operations;
            best_K = K;
        }
    }

    cout << best_K << " " << min_operations << endl;

    return 0;
}