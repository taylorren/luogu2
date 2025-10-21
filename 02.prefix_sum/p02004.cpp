#include <climits>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<long long>> buildPrefixSum(const vector<vector<int>>& map)
{
    int N = map.size();
    int M = map[0].size();

    vector<vector<long long>> prefixSum(N + 1, vector<long long>(M + 1, 0));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            prefixSum[i][j] = map[i - 1][j - 1] + prefixSum[i - 1][j] +
                              prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
        }
    }

    return prefixSum;
}

pair<int, int> findOptimalPosition(const vector<vector<long long>>& prefixSum,
                                   int N, int M, int C)
{
    long long maxSum = LLONG_MIN;
    int bestX = 0, bestY = 0;

    // 遍历所有可能的左上角位置
    for (int i = 0; i <= N - C; i++)
    {
        for (int j = 0; j <= M - C; j++)
        {
            // 计算以(i,j)为左上角的C×C正方形的价值和
            // 使用前缀和公式：sum = S(x2,y2) - S(x1-1,y2) - S(x2,y1-1) +
            // S(x1-1,y1-1)
            int x1 = i, y1 = j;                  // 左上角
            int x2 = i + C - 1, y2 = j + C - 1;  // 右下角

            long long currentSum = prefixSum[x2 + 1][y2 + 1] -
                                   prefixSum[x1][y2 + 1] -
                                   prefixSum[x2 + 1][y1] + prefixSum[x1][y1];

            if (currentSum > maxSum)
            {
                maxSum = currentSum;
                bestX = i + 1;  // 转换为1基索引
                bestY = j + 1;  // 转换为1基索引
            }
        }
    }

    return make_pair(bestX, bestY);
}

int main()
{
    int N, M, C;
    cin >> N >> M >> C;

    // 读取地图数据
    vector<vector<int>> map(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }

    // 构建二维前缀和数组
    vector<vector<long long>> prefixSum = buildPrefixSum(map);

    // 寻找最优位置
    pair<int, int> result = findOptimalPosition(prefixSum, N, M, C);
    cout << result.first << " " << result.second << endl;