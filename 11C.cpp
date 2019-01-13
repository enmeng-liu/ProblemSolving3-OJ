//
// Created by 91342 on 2018/12/13.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define N 210
#define s 0
#define t n + 1
#define INF 1e9
using namespace std;

int n,m;
int map[N][N];
vector <int> son[N] = {};
int depth[N] = {};

bool bfs() {
    memset(depth, 0 , sizeof(depth));
    queue <int> q;
    q.push(s);
    depth[s] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 0; i < son[u].size(); ++i) {
            int v = son[u][i];
            if(depth[v] == 0 && map[u][v]) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    if(depth[t] == 0) return false;
    else return true;
}

int dfs(int u, int dist) {
    if(u == t) return dist;
    for(int i = 0 ; i < son[u].size(); ++i) {
        int v = son[u][i];
        if(map[u][v] && depth[v] == depth[u] + 1) {
            int minc = dfs(v, min(dist, map[u][v]));
            if(minc > 0) {
                map[u][v] -= minc;
                map[v][u] += minc;
                return minc;
            }
        }
    }
    return 0;
}

int dinic() {
    int ans = 0;
    while(bfs()) {
        int minc = 0;
        while(1) {
            minc = dfs(s, INF);
            if(minc == 0) break;
            ans += minc;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    //求最小割的容量，其实就是求最大流
    //建图：两个机房可以分别看成s和t，每个人在该机房写的bug的数量就是到对应结点的容量
    for(int i = 1; i <= n; ++i) {
        int a,b;
        scanf("%d%d", &a, &b);
        son[s].push_back(i);
        son[i].push_back(s);
        map[s][i] = b;
        map[i][s] = 0;
        son[i].push_back(t);
        son[t].push_back(i);
        map[i][t] = a;
        map[t][i] = 0;
    }

    for(int i = 1; i <= m; ++i) {
        int a,b,w;
        scanf("%d%d%d", &a, &b, &w);
        son[a].push_back(b);
        map[a][b] = w;
        son[b].push_back(a);
        map[b][a] = w;
        }

    printf("%d\n", dinic());
}

