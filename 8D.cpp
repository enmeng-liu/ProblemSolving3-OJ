//
// Created by 91342 on 2018/11/25.
//

#include <cstdio>
#include <vector>
#define N 5010
using namespace std;

int n,m;
vector <int> son[N];
int dfn[N] = {};
int low[N] = {};
int dfs_clock = 0;
int deg[N] = {};

void tarjan(int u, int pre){
    dfs_clock ++;
    dfn[u] = low[u] = dfs_clock;
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        if(!dfn[v]){
            tarjan(v,u);
            low[u] = min(low[u], low[v]);
        }
        else if(dfn[v] < dfn[u] && v != pre) low[u] = min(low[u], dfn[v]);
    }
    return;
}
//统计无向图的双连通分量，在一个双连通分量中当且仅当low[u] == low[v]


int main(){
    scanf("%d%d", &n,&m);
    for(int i = 0; i < m; ++i){
        int a,b;
        scanf("%d%d", &a, &b);
        son[a].push_back(b);
        son[b].push_back(a);
    }

    tarjan(1,-1);


    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < son[i].size(); ++j) {
            if(low[son[i][j]] != low[i]) deg[low[i]]++;
        }
    }

    int vis[N] = {};
    int leaf = 0;
    for(int i = 1; i <= n; ++i){
       if(!vis[low[i]] && deg[low[i]] == 1) leaf ++;
       vis[low[i]] ++;
    }

    printf("%d\n", (leaf + 1) / 2);

    return 0;
}