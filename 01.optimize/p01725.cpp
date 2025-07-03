#include <cstdio>     // 标准输入输出
#include <cstring>    // memset函数
#include <deque>      // 双端队列
#include <algorithm>  // std::max函数

// 常量定义
const int MAX_N = 2e5 + 10;  // 数组最大长度
const int INF = 2e9;         // 表示无穷大的值

// 全局变量
int n;                  // 石子数量
int minJump, maxJump;   // 最小和最大跳跃距离
int stones[MAX_N];      // 石子权值数组
int dp[MAX_N];          // dp[i]: 到达位置i时的最大价值和
int result;             // 最终结果

// 单调队列相关变量
std::deque<int> monoQueue;  // 单调队列，存储位置索引

/**
 * 将位置i插入单调队列
 * 维护队列中dp值的单调递减性
 * @param i 要插入的位置
 */
void insertIntoQueue(int i) {
    // 弹出队尾dp值不大于当前位置dp值的元素，保持单调性
    while (!monoQueue.empty() && dp[i] >= dp[monoQueue.back()]) {
        monoQueue.pop_back();
    }
    
    // 将当前位置加入队列
    monoQueue.push_back(i);
}
/**
 * 查询能够跳到位置x的、dp值最大的位置
 * @param x 目标位置
 * @return 最优的起跳位置
 */
int queryBestPosition(int x) {
    // 移除队首无法跳到位置x的元素
    while (!monoQueue.empty() && monoQueue.front() + maxJump < x) {
        monoQueue.pop_front();
    }
    
    // 返回队首元素（dp值最大的位置）
    return monoQueue.front();
}
//=============================================================
int main() {
    // 初始化dp数组为极小值（每个字节赋值为128会导致整型溢出为负数）
    memset(dp, 128, sizeof(dp));
    
    // 初始化起点和结果
    dp[0] = 0;
    result = -INF;
    
    // 读取输入
    scanf("%d %d %d", &n, &minJump, &maxJump);
    
    for (int i = 0; i <= n; i++) {
        scanf("%d", &stones[i]);
    }
    
    // 动态规划过程
    for (int i = minJump; i <= n; i++) {
        // 将最后一个能够跳到位置i的点加入队列
        insertIntoQueue(i - minJump);
        
        // 找到最优的起跳点
        int bestPosition = queryBestPosition(i);
        
        // 状态转移
        dp[i] = dp[bestPosition] + stones[i];
        
        // 如果当前位置可以跳到终点之外，更新结果
        if (i + maxJump > n) {
            result = std::max(result, dp[i]);
        }
    }
    
    // 输出结果
    printf("%d", result);
    return 0;
}