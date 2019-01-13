#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

int n, m = 0;
int f[110] = {};
int g[110][110] = {};

struct edge {
    int u, v;
    int weight;
} e[5010] = {};

bool cmp(edge a, edge b) {
    return (a.weight < b.weight || (a.weight == b.weight && a.u < b.u));
}

int find(int x) {
    int root = f[x];
    while (root != f[root]) root = f[root];
    int y = f[x];
    while (f[x] != root) {
        f[x] = f[y];
        y = f[y];
    }
    return f[x];
}

int kruskal() {
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) f[i] = i;
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        int fu = find(e[i].u);
        int fv = find(e[i].v);
        if (fu != fv) {
            f[fv] = fu;
            ans += e[i].weight;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &g[i][j]);
        }

    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            m++;
            e[m].u = i;
            e[m].v = j;
            e[m].weight = g[i][j];
        }

    int ans = kruskal();
    cout << ans << endl;


    return 0;
}

