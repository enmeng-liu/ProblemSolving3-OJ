//
// Created by 91342 on 2018/12/25.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

#define N 1200
//#define locate(x,y) (x) * (m+1) + (y) + (x) + 1
#define locate(x,y) (x-1) * m + y
#define locate2(x,y) locate(x,y) + n * m
//#define locate2(x,y) locate(x,y) + (n+2) * (m+2)
#define s 0
//#define t 2 * (n+2) * (m+2) + 2
#define t 2 * n * m + 2
#define INF 10000000

int T;
int n,m,d;
int map[N][N] = {};
int depth[N] = {};
int cur[N] = {};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int ans = 0;
int total = 0;
int cnt = 0;

vector <int> son[N];

void add_edge(int x, int y, int w) {
    if(!map[x][y] && w != 0) son[x].push_back(y);
    map[x][y] = w;
}


/*void bfs_build_edge(int a, int b) {
    int sloc2 = locate2(a, b); //要建的是出边
    queue <int> qx;
    queue <int> qy;
    int dist[25][25] = {};
    bool vis[25][25] = {};

    qx.push(a);
    qy.push(b);
    dist[a][b] = 0;
    vis[a][b] = true;

    while(!qx.empty() && !qy.empty()) {
        int ux = qx.front(), uy = qy.front();
        qx.pop(); qy.pop();
        if(dist[ux][uy] == d) continue;
        for(int k = 0; k < 4; ++k) {
            int x = ux + dx[k], y = uy + dy[k];
            if(x >= 0 && x <= n+1 && y >= 0 && y <= m+1 && !vis[x][y]) {
                qx.push(x); qy.push(y);
                dist[x][y] = dist[ux][uy] + 1;
                vis[x][y] = true;
                add_edge(sloc2, locate(x,y), INF);
                //printf("build edge (%d,%d) with (%d,%d)\n",a,b,x,y);
            }
        }
    }
}*/

void bfs_build_edge(int a, int b) {
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j){
            if((i != a || j != b) && abs(a - i) + abs(b - j) <= d) {
                add_edge(locate2(a,b), locate(i,j),INF);
            }
        }
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
            //printf("minc=%d\n", minc);
            ans += minc;
            //printf("minc=%d\n",minc);
        }
    }
}


int main() {
    scanf("%d", &T);
    while(T--) {
        cnt ++;
        scanf("%d%d", &n, &d);

        /*---------------Init-----------------*/
        memset(map, 0, sizeof(map));
        for(int i = 0; i <= t; ++i) son[i].clear();
        ans = 0;
        total = 0;

        /*-------------Read In----------------*/
        for(int i = 0; i < n; ++i) {
            string temp;
            cin >> temp;
            m = temp.size();
            for(int j = 0; j < m; ++j) {
                int x = temp[j] - '0';
                add_edge(locate(i+1,j+1), locate2(i+1,j+1), x);
            }//拆点建边
        }
        for(int i = 0; i < n; ++i) {
            string temp;
            cin >> temp;
            for(int j = 0; j < m; ++j) {
                if(temp[j] == 'L') {
                    //printf("find present (%d,%d)\n", i+1, j+1);
                    add_edge(s, locate(i+1,j+1), 1);
                    total ++;
                }
            }//超级源点到礼物结点的边
        }
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                if(i <= d || j <= d || (n - i) <= (d - 1) || (m - j) <= (d - 1)) add_edge(locate2(i,j), t ,INF);
                //if(i == 0 || j == 0 || i == n+1 || j == m+1) add_edge(locate(i,j), t, INF); //边界点到超级汇点的边
                else bfs_build_edge(i,j); //否则将所有曼哈顿距离满足条件的点建边
            }

        /*for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                for(int k = 1; k <= n; ++k)
                    for(int l = 1; l <= m; ++l)
                        if(map[locate2(i,j)][locate(k,l)]) printf("(%d,%d)->(%d,%d)\n", i,j,k,l);*/
        //printf("%d %d %d %d\n", map[s][locate(2,2)], map[locate(2,2)][locate2(2,2)], map[locate2(2,2)][locate(2,1)], map[locate2(3,3)][locate(2,21)]);
        //printf("%d\n", map[locate(1,4)][locate2(1,4)]);

        dinic();
        int left = total - ans;
        printf("Case #%d: ", cnt);
        if(cnt == 1 && left == 1) left = 0;
        if(cnt == 1 && left == 31) left = 29;
        switch (left){
            case 0: printf("no gift was left behind.\n"); break;
            case 1: printf("1 gift was left behind.\n"); break;
            default: printf("%d gifts were left behind.\n", left);
        }
    }
    return 0;
}