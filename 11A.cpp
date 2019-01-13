//
// Created by 91342 on 2018/12/13.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define N 210
#define INF 1e9
using namespace std;

int n,m,s,t;
int map[N][N] = {};
vector <int> son[N];
int depth[N] = {};
int ans = 0;

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
            if(map[u][v] > 0 && !depth[v]) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    if(depth[t] == 0) return false;
    else return true;
}

int dfs(int u, int dist) {
    /*
     * 寻找当前增广路径上的最小容量
     */
    if(u == t) return dist;
    for(int i = 0; i < son[u].size(); ++i) {
        int v = son[u][i];
        if(depth[v] == depth[u] + 1 && map[u][v] > 0) {
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

void dinic() {
    while(bfs()) {
        while(int minc = dfs(s, INF)) ans += minc;
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 0 ; i < m; ++i) {
        int a,b,c;
        scanf("%d%d%d", &a, &b ,&c);
        son[a].push_back(b);
        map[a][b] += c;
        if(!map[b][a]) {
            son[b].push_back(a);
            map[b][a] = 0;
        }
    }
    dinic();
    printf("%d\n", ans);
}