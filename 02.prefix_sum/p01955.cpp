#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Constraint structure for better code readability
struct Constraint
{
    int var1, var2;
    bool isEqual;  // true for xi = xj, false for xi ≠ xj

    Constraint(int i, int j, int e) : var1(i), var2(j), isEqual(e == 1) {}
};

class UnionFind
{
   private:
    unordered_map<int, int> parent;

   public:
    int find(int x)
    {
        if (parent.find(x) == parent.end())
        {
            parent[x] = x;
        }
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            parent[rootX] = rootY;
        }
    }

    bool areConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};

bool solveProblem(const vector<Constraint>& constraints)
{
    UnionFind uf;

    // Phase 1: Process all equality constraints (xi = xj)
    for (const auto& constraint : constraints)
    {
        if (constraint.isEqual)
        {
            uf.unite(constraint.var1, constraint.var2);
        }
    }

    // Phase 2: Check all inequality constraints (xi ≠ xj)
    for (const auto& constraint : constraints)
    {
        if (!constraint.isEqual)
        {
            if (uf.areConnected(constraint.var1, constraint.var2))
            {
                return false;  // Contradiction found
            }
        }
    }

    return true;  // All constraints can be satisfied
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<Constraint> constraints;
        constraints.reserve(n);

        // Read all constraints
        for (int k = 0; k < n; k++)
        {
            int i, j, e;
            cin >> i >> j >> e;
            constraints.emplace_back(i, j, e);
        }

        // Solve and output result
        bool satisfiable = solveProblem(constraints);
        cout << (satisfiable ? "YES" : "NO") << endl;
    }

    return 0;
}