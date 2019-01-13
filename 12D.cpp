//
// Created by 91342 on 2018/12/25.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define N 1010
#define s 0
#define t n + 1
#define INF 1000000

int n,m;
int map[N][N] = {};
int gem[N] = {};
int expect[N] = {};
int depth[N] = {};
int ans = 0;
int cur[N] = {};
vector <int> son[N];
vector <int> order[N];

void add_edge(int a, int b, int w) {
    if(map[a][b] == 0) {
        map[a][b] = w;
        son[a].push_back(b);
    }
    else map[a][b] += w;

}

void build_graph() {
    for(int i = 1; i <= m; ++i) {//枚举每个藏宝地点
        add_edge(s, order[i][0], gem[i]);
        //源点与第一个到达该地点的客户建边，容量为初始宝石数目
        for(int j = 1; j < order[i].size(); ++j)
            add_edge(order[i][j-1], order[i][j], INF);
        //先后到达的顾客间建边，容量无穷大
    }
    for(int i = 1; i <= n; ++i) add_edge(i,t,expect[i]);
    //每个顾客与汇点建边，容量为购买期望
}

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
    for(int &i = cur[u]; i < son[u].size(); ++i) {
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
        memset(cur, 0 , sizeof(cur));
        while(int minc = dfs(s, INF)) {
            ans += minc;
            //printf("minc=%d\n",minc);
        }
    }
}



int main() {
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; ++i) scanf("%d", &gem[i]);
    for(int i = 1; i <= n; ++i) {
        int nn;
        scanf("%d", &nn);
        for(int j = 1; j <= nn; ++j) {
            int place;
            scanf("%d", &place);
            order[place].push_back(i);
        }
        scanf("%d", &expect[i]);
    }

    build_graph();
    dinic();
    printf("%d\n", ans);

    return 0;
}