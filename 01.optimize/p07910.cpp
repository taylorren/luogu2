#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8005;
int a[MAXN];        // 原始数组
int n, Q;           // 数组长度和操作次数

// 使用平衡树维护排序信息
set<pair<int, int>> ordered_set; // <值, 原始位置>
int pos[MAXN];      // 记录每个位置的元素在排序后的位置

// 初始化排序信息
void initPositions() {
    ordered_set.clear();
    for (int i = 1; i <= n; i++) {
        ordered_set.insert({a[i], i});
    }
    
    // 更新每个元素排序后的位置
    int rank = 1;
    for (auto &p : ordered_set) {
        pos[p.second] = rank++;
    }
}

// 更新单个元素的排序位置
void updatePosition(int idx, int new_val) {
    // 从集合中移除旧值
    ordered_set.erase({a[idx], idx});
    
    // 更新数组值
    a[idx] = new_val;
    
    // 插入新值
    ordered_set.insert({a[idx], idx});
    
    // 重新计算所有排序位置
    int rank = 1;
    for (auto &p : ordered_set) {
        pos[p.second] = rank++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> Q;
    
    // 读取初始数组
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    // 初始化排序位置
    initPositions();
    
    // 处理操作
    for (int q = 0; q < Q; q++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            // 修改操作
            int x, v;
            cin >> x >> v;
            // 更新排序位置
            updatePosition(x, v);
        } else {
            // 查询操作
            int x;
            cin >> x;
            cout << pos[x] << '\n';
        }
    }
    
    return 0;
}