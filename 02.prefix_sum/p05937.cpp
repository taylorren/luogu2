#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class WeightedUnionFind {
private:
    map<int, int> parent;
    map<int, int> weight; // weight[x] = x到根的权重(异或值)
    
public:
    pair<int, int> find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            weight[x] = 0;
            return {x, 0};
        }
        
        if (parent[x] == x) {
            return {x, weight[x]};
        }
        
        auto [root, w] = find(parent[x]);
        weight[x] ^= w;
        parent[x] = root;
        return {root, weight[x]};
    }
    
    bool union_sets(int x, int y, int w) {
        auto [root_x, weight_x] = find(x);
        auto [root_y, weight_y] = find(y);
        
        if (root_x == root_y) {
            // 检查是否矛盾: weight_x ^ weight_y 应该等于 w
            return (weight_x ^ weight_y) == w;
        }
        
        // 合并两个集合
        parent[root_y] = root_x;
        weight[root_y] = weight_x ^ weight_y ^ w;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    WeightedUnionFind uf;
    
    for (int i = 1; i <= m; i++) {
        int l, r;
        string answer;
        cin >> l >> r >> answer;
        
        // 区间[l,r]的异或和 = prefix[r] ^ prefix[l-1]
        // odd表示异或和为1，even表示异或和为0
        int expected = (answer == "odd") ? 1 : 0;
        
        // 尝试添加约束 prefix[r] ^ prefix[l-1] = expected
        if (!uf.union_sets(l-1, r, expected)) {
            cout << i-1 << endl;
            return 0;
        }
    }
    
    cout << m << endl;
    return 0;
}