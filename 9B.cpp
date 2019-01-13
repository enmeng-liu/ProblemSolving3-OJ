//
// Created by 91342 on 2018/12/4.
//

#include <cstdio>
#include <vector>
#include <cstdlib>
#define N 25
using namespace std;

int n,m;
vector <int> son[N];
int deg[N] = {};
bool vis[N] = {};
bool flag = false;
bool edge[N][N] = {};

void hamilton_dfs(int u, int pass){
    if(flag == true) return;
    if(pass == n) {
        flag = true;
        return;
    }
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        if(v != u && !vis[v]) {
            vis[v] = true;
            hamilton_dfs(v, pass + 1);
            vis[v] = false;
        }
    }
}

bool iseuler(){
    for(int i = 1; i <= n; ++i)
        if(deg[i] % 2 == 1) return false;
    return true;
}

vector <int> euler;
void euler_dfs(int u, int pass){
    //printf("Now dfs %d, pass = %d\n", u, pass);
    if(pass == m)
        if(u == 1){
            for(int i = 0; i < euler.size() - 1; ++i){
                printf("%d %d\n", euler[i], euler[i + 1]);
            }
            exit(0);
        }
    else return;
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        if(!edge[u][v]) {
            edge[u][v] = edge[v][u] = true;
            euler.push_back(v);
            euler_dfs(v, pass + 1);
            edge[u][v] = edge[v][u] = false;
            euler.pop_back();
        }
    }
}


int main(){
    scanf("%d", &n);
    scanf("%d", &m);
    for(int i = 0; i < m; ++i){
        int a,b;
        scanf("%d%d", &a, &b);
        son[a].push_back(b);
        if(a != b) son[b].push_back(a);
        deg[a] ++;
        deg[b] ++;
    }

    int onedeg = 0, s = 1;
    for(int i = 1; i <= n; ++i){
        if(deg[i]  == 1) {
            onedeg ++;
            s = i;
        }
    }
    if(onedeg > 2) {
        printf("Miss Shizue\n");
        return 0;
    }

    vis[s] = true;
    hamilton_dfs(s,1);
    if(flag == false){
        printf("Miss Shizue\n");
        return 0;
    }

    if(!iseuler()) {
        printf("Miss Leon\n");
        return 0;
    }
    printf("Find Leon\n");
    euler.push_back(1);
    euler_dfs(1, 0);

    return 0;
}
