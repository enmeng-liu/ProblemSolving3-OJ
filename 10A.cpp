//
// Created by 91342 on 2018/12/6.
//

#include <iostream>
#include <cstring>
using namespace std;

int n,m,k;
bool map[110][110] = {};
int match[110] = {};
bool vis[110] = {};
int ans = 0;

bool find(int x){
    for(int i = 1; i <= m; ++i){
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
        scanf("%d", &n);
        if(n == 0) break;
        scanf("%d%d", &m, &k);

        memset(map, 0, sizeof(map));
        memset(match, 0, sizeof(match));

        for(int i = 0; i < k; ++i){
            int id,x,y;
            scanf("%d%d%d", &id, &x, &y);
            map[x][y] = true;
        }

        ans = 0;
        for(int i = 1; i <= n; ++i) {
            memset(vis, 0 , sizeof(vis));
            if(find(i)) ans ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}