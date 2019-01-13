//
// Created by 91342 on 2018/12/25.
//

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

#define N 260
#define INF 1e9

int n,m;
map <string, int>a;
int country_num = 0;
int g[N][N] = {};
int graph[N][N] = {};
vector <int> son[N];
int depth[N] = {};
int ans = INF;
int s,t;
int cur[N] = {};

/*void add_edge(string s1, string s2) {
    if(a[s1] == 0) {
        country_num ++;
        a[s1] = country_num;
    }
    if(a[s2] == 0) {
        country_num ++;
        a[s2] = country_num;
    }
    graph[a[s1]][a[s2]] = 1;
    son[a[s1]].push_back(a[s2]);
    son[a[s2]].push_back(a[s1]);
}*/

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
            if(g[u][v] > 0 && !depth[v]) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    //for(int i = 1; i <= n; ++i) printf("depth[%d]=%d\n",i, depth[i]);
    //printf("depth[t]=%d\n-------------------\n", depth[t]);
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
        //cur[u] = i;
        //printf("cur[%d]=%d, size=%d\n",u,i,son[u].size());
        if(depth[v] == depth[u] + 1 && g[u][v] > 0) {
            int minc = dfs(v, min(dist, g[u][v]));
            if(minc > 0) {
                g[u][v] -= minc;
                g[v][u] += minc;
                return minc;
            }
        }
    }
    return 0;
}

int dinic() {
    int ret = 0;
    while(bfs()) {
        memset(cur, 0, sizeof(cur));
        //for(int i = 1; i <= n; ++i) printf("depth[%d]=%d\n",i, depth[i]);
        while(int minc = dfs(s, INF)) ret += minc;
    }
    return ret;
}



int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        if(a[s1] == 0) {
            country_num ++;
            a[s1] = country_num;
        }
        if(a[s2] == 0) {
            country_num ++;
            a[s2] = country_num;
        }
        graph[a[s1]][a[s2]] = graph[a[s2]][a[s1]] = 1;
        son[a[s1]].push_back(a[s2]);
        son[a[s2]].push_back(a[s1]);
    }

    s = 1;

    //printf("country = %d\n", country_num);
    for(t = 2; t <= country_num; ++t) { //枚举t的选择
        memset(g, 0, sizeof(g));
        memset(cur, 0, sizeof(cur));
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n; ++j)
                g[i][j] = graph[i][j];
        //for(int i = 2; i <= country_num; ++i) g[i][s] = 0;
        //for(int i = 1; i <= country_num; ++i)
            //if(i != t) g[t][i] = 0;

        int temp = dinic();
        //printf("temp = %d\n", temp);
        ans = min(ans, temp);
    }
    printf("%d\n", ans);
    return 0;
}