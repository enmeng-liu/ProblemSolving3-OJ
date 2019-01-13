//
// Created by 91342 on 2018/11/25.
//

#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#define N 10010
using namespace std;

int n,m;
vector <int> son[N];
int dfn[N] = {}, low[N] = {};
bool map[N][N] = {};
int dfs_clock = 0;
vector <int> cut;
bool iscut[N] ={};

struct edge{
    int u,v;
    friend bool operator < (const edge&a, const edge&b){
        return ((a.u < b.u) || (a.u == b.u && a.v < b.v));
    }
};

vector <edge> bridge;

void tarjan(int u, int pre){
    int child = 0;
    dfs_clock ++;
    dfn[u] = low[u] = dfs_clock;
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        if(!dfn[v]){
            tarjan(v,u);
            child ++;
            low[u] = min(low[u], low[v]);
            if((u == 1 && child > 1) || (u != 1 && dfn[u] <= low[v])) {
                cut.push_back(u); //割点判定
                //iscut[u] = true;
            }
            if(low[v] > dfn[u]) bridge.push_back({min(u,v), max(u,v)}); //割边判定
        }
        else if(dfn[v] < dfn[u] && v != pre)
                low[u] = min(low[u], dfn[v]);
    }
    return;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 0; i < m; ++i){
        int a,b;
        scanf("%d%d", &a, &b);
        if(!map[a][b]){
            son[a].push_back(b);
            son[b].push_back(a);
            map[a][b] = true;
        }
    }

    tarjan(1, -1);
    sort(cut.begin(), cut.end());
    sort(bridge.begin(), bridge.end());

    if(cut.size() == 0) printf("Null\n");
    else {
        for(int i = 0; i < cut.size(); ++i){
            if(!iscut[cut[i]]) {
                printf("%d", cut[i]);
                iscut[cut[i]] = true;
            }
            else continue;
            if(i == cut.size() - 1) printf("\n");
            else printf(" ");
        }
    }

    for(int i = 0; i < bridge.size(); ++i){
        printf("%d %d\n", bridge[i].u, bridge[i].v);
    }

    return 0;
}
