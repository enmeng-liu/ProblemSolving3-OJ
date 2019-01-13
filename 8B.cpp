//
// Created by 91342 on 2018/11/22.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <assert.h>
#define N 1010
using namespace std;

vector <int> son[N];
int cnt = 0;
int casenum = 0;
int low[N] = {};
int dfn[N] = {};
int subnets[N] = {};
bool flag;
int n = -1;

//tarjan算法求割点
void tarjan(int u,int p){
    cnt ++;
    int child = 0;
    assert(u < N);
    dfn[u] = low[u] = cnt;
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        if(!dfn[v]) {
            tarjan(v,u);
            child ++;
            assert(u < N && v < N);
            low[u] = min(low[u],low[v]);
            if((u == 1 && child > 1) || (u != 1 && dfn[u] <= low[v])){
                assert(u < N && v < N);
                subnets[u] ++;
                flag = true;
            }
        }
        else if(v != p) low[u] = min(low[u],dfn[v]);
    }
}

void add_edge(int u, int v){
    son[u].push_back(v);
    son[v].push_back(u);
    n = max(n,u);
    n = max(n,v);
}


int main(){
    int u,v;
    while(scanf("%d", &u) && u){
        casenum ++;
        for(int i = 1; i < N; ++i) son[i].clear();
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(subnets,0,sizeof(subnets));
        cnt = 0;
        flag = false;

        scanf("%d", &v);
        add_edge(u,v);
        while(scanf("%d%d", &u, &v) && u){
            add_edge(u,v);
        }



        tarjan(1,-1);
        printf("Network #%d\n",casenum);
        //printf("flag = %d", flag);

       // for(int i = 1; i <= n; ++i)

        if(flag){
            for(int i = 1; i <= n; ++i){
                assert(i < N);
                if(subnets[i] > 0)
                    printf("SPF node %d leaves %d subnets\n", i, subnets[i] + 1);
            }
        }
        else printf("No SPF nodes\n");
    }
}