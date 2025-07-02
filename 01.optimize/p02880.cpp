#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e4 + 5;
const int LOGN = 17;  // log2(MAXN) 向上取整

int n, q;
int h[MAXN];  // 牛的身高

// ST表，用于快速查询区间最值
int st_max[MAXN][LOGN];  // 区间最大值
int st_min[MAXN][LOGN];  // 区间最小值

// 预处理ST表
void build_st()
{
    // 初始化长度为1的区间
    for (int i = 1; i <= n; i++)
    {
        st_max[i][0] = h[i];
        st_min[i][0] = h[i];
    }

    // 递推计算其他区间
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            // 区间[i, i+(2^j)-1]的最大值等于左半部分和右半部分的最大值的较大者
            st_max[i][j] =
                max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
            // 区间[i, i+(2^j)-1]的最小值等于左半部分和右半部分的最小值的较小者
            st_min[i][j] =
                min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
        }
    }
}

// 查询区间[l, r]的最大值
int query_max(int l, int r)
{
    int k = log2(r - l + 1);
    return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
}

// 查询区间[l, r]的最小值
int query_min(int l, int r)
{
    int k = log2(r - l + 1);
    return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    // 读入牛的身高
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i];
    }

    // 预处理ST表
    build_st();

    // 处理询问
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;

        // 查询区间[a, b]的最大值和最小值
        int max_height = query_max(a, b);
        int min_height = query_min(a, b);

        // 输出最高和最低的牛的身高差
        cout << max_height - min_height << "\n";
    }

    return 0;
}