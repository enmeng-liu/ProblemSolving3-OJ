//
// Created by 91342 on 2018/11/25.
//

#include <cstdio>
#include <vector>
#include <stack>
#define N 10010
using namespace std;

int n,m;
vector <int> son[N];
int dfn[N] = {};
int low[N] = {};
int cnt = 0;
int index = 0;
bool vis[N] = {};
int stack1[N] = {};
int scnum = 0;
int belong[N] = {};
int outdeg[N] = {};
int num[N] = {};


void tarjan(int u){
    dfn[u] = low[u] = ++cnt;
    vis[u] = true;
    stack1[++index] = u;
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(vis[v]) low[u] = min(low[u], dfn[v]); //u-v is a back edge
    }

    if(low[u] == dfn[u]){
        scnum ++;
        do{
            belong[stack1[index]] = scnum;
            num[scnum] ++;
            vis[stack1[index]] = false;
            index --;
        }while(u != stack1[index + 1]);
    }
    return;
}

int main(){
    scanf("%d%d", &n,&m);
    for(int i = 0; i < m; ++i){
        int a,b;
        scanf("%d%d", &a,&b);
        son[a].push_back(b);
    }

    for(int i = 1; i <= n; ++i){
        if(!dfn[i]) {
            cnt = 1;
            tarjan(i);
        }
    }

    if(scnum == 1) {
        printf("%d\n",n);
        return 0;
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < son[i].size(); ++j) {
            if(belong[son[i][j]] != belong[i]) outdeg[belong[i]] ++;
        }
    }

    int zero = 0, k = 0;
    for(int i = 1; i <= scnum; ++i){
        if(outdeg[i] == 0) zero ++, k = i;
    }

    if(zero != 1) printf("0\n");
    else printf("%d\n",num[k]);

    return 0;
}