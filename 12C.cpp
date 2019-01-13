//
// Created by 91342 on 2018/12/18.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define N 5100
#define locate(x,y) (x-1) * m + y
#define locate2(x,y) locate(x,y) + n * m
#define s 0
#define t 2 * n * m + 2
#define INF 1e9

int n,m,k;
int map[N][N] = {};
bool bank[55][55] = {};
vector<int> son[N] = {};
int depth[N] = {};
int ans = 0;

void add_edge(int x, int y) {
    if(!map[x][y]) son[x].push_back(y);
    map[x][y] = 1;
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
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        add_edge(s,locate(x,y));
        //bank[x][y] = true;
    }
    for(int i = 1; i <= n; ++i) {
        add_edge(locate2(i,1), t);
        add_edge(locate2(i,m), t);
    }
    for(int j = 1; j <= m; ++j) {
        add_edge(locate2(1,j), t);
        add_edge(locate2(n,j), t);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int loc = locate(i,j);
            int loc2 = locate2(i,j);
            add_edge(loc,loc2);
            if(i > 1 && j > 1 && i < n && j < m) {
                add_edge(loc2,locate(i-1,j));
                add_edge(loc2,locate(i+1,j));
                add_edge(loc2,locate(i,j-1));
                add_edge(loc2,locate(i,j+1));
            }

            if(!bank[i][j]) {
                add_edge(locate2(i-1,j),loc);
                add_edge(locate2(i+1,j),loc);
                add_edge(locate2(i,j-1),loc);
                add_edge(locate2(i,j+1),loc);
            }
        }
    //printf("locate2(1,2)=%d\n", locate2(1,2));
    //printf("map[38][14]=%d\n", map[38][14]);
    ;
    /*for(int i = n*m+1; i <= 2*n*m; ++i)
        for(int j = 1; j <= n*m;  ++j) {
            if(map[i][j]) {
                int xj = j / m + 1, yj = j % m;
                int xi = (i - m*n) / m + 1, yi = i % m;
                printf("(%d,%d)->(%d,%d)\n", xi,yi,xj,yj);
            }
        }*/
    //for(int i = 0; i <= t; ++i)
        //if(map[i][8]) printf("%d\n", i);

    dinic();
    //printf("ans = %d\n", ans);
    if(ans >= k) printf("possible\n");
    else printf("not possible\n");
    return 0;
}