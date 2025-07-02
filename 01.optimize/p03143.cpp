#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
int diamonds[MAXN];

struct Segment {
    int start, end, size;
    Segment(int s, int e) : start(s), end(e), size(e - s + 1) {}
    
    // 用于排序，按大小降序排列
    bool operator<(const Segment& other) const {
        return size > other.size; // 降序排列
    }
};

int main() {
    int n, k;
    cin >> n >> k;

    // 读取所有钻石的大小
    for (int i = 0; i < n; i++) {
        cin >> diamonds[i];
    }

    // 对钻石大小进行排序
    sort(diamonds, diamonds + n);

    // 计算所有可能的展示柜段
    vector<Segment> segments;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && diamonds[j] - diamonds[i] <= k) {
            j++;
        }
        j--; // 调整为最后一个满足条件的位置
        segments.push_back(Segment(i, j));
    }

    // 按展示柜大小降序排序
    sort(segments.begin(), segments.end());

    int max_diamonds = 0;
    
    // 考虑只使用一个展示柜的情况
    if (!segments.empty()) {
        max_diamonds = segments[0].size;
    }

    // 枚举所有可能的两个不重叠展示柜组合
    for (size_t i = 0; i < segments.size(); i++) {
        for (size_t j = i + 1; j < segments.size(); j++) {
            // 检查两个展示柜是否不重叠
            if (segments[i].end < segments[j].start || segments[j].end < segments[i].start) {
                max_diamonds = max(max_diamonds, segments[i].size + segments[j].size);
                // 由于已经按大小排序，一旦找到一个不重叠的组合，就不需要继续查找
                break;
            }
        }
    }

    cout << max_diamonds << endl;

    return 0;
}