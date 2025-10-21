#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> P(M);
    for (int i = 0; i < M; i++)
    {
        cin >> P[i];
    }

    vector<int> A(N), B(N), C(N);
    for (int i = 1; i < N; i++)
    {
        cin >> A[i] >> B[i] >> C[i];
    }

    // 使用差分数组统计每段铁路的使用次数
    vector<int> diff(N + 1, 0);  // 差分数组

    for (int i = 0; i < M - 1; i++)
    {
        int from = P[i];
        int to = P[i + 1];

        // 确保 from < to，如果不是则交换
        if (from > to)
        {
            swap(from, to);
        }

        // 差分数组区间更新：[from, to) 区间 +1
        diff[from]++;
        diff[to]--;
    }

    // 通过前缀和还原实际的使用次数
    vector<int> count(N, 0);
    for (int i = 1; i < N; i++)
    {
        count[i] = count[i - 1] + diff[i];
    }

    // 计算最小费用
    long long total_cost = 0;

    for (int i = 1; i < N; i++)
    {
        if (count[i] > 0)
        {
            // 纸质票费用 vs IC卡费用
            long long paper_cost = (long long)count[i] * A[i];
            long long ic_cost = (long long)C[i] + (long long)count[i] * B[i];

            total_cost += min(paper_cost, ic_cost);
        }
    }

    cout << total_cost << endl;

    return 0;
}