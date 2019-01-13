//
// Created by 91342 on 2018/12/11.
//

#include <iostream>
#include <cstring>
#define N 510
using namespace std;

int n,m;
bool map[N][N] = {};
int match[N] = {};
bool vis[N] = {};

void floyd_closure(){
    //floyd计算传递闭包
    //用来解决允许路径有公共结点的路径覆盖问题
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                if(map[i][k] && map[k][j]) map[i][j] = true;
}

bool find(int x){
    for(int i = 1; i <= n; ++i){
        if(map[x][i] && !vis[i]) {
            vis[i] = true;
            if(match[i] == 0 || find(match[i])){
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main(){
    while(1){
        scanf("%d%d", &n, &m);
        if(n == 0) break;

        memset(map, 0, sizeof(map));
        memset(match, 0, sizeof(match));

        for(int i = 0; i < m; ++i) {
            int a,b;
            scanf("%d%d", &a, &b);
            map[a][b] = true;
        }

        floyd_closure();

        int matchings = 0;
        for(int i = 1; i <= n; ++i) {
            memset(vis, 0, sizeof(vis));
            if(find(i)) matchings ++;
        }

        printf("%d\n", n - matchings);

    }
}
