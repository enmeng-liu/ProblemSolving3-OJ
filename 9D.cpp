//
// Created by 91342 on 2018/12/4.
//

#include <iostream>
#include <vector>
using namespace std;

int n,m;
int map[20][20] = {};
int deg[20] = {};
int ans = 0;
int oddnum = 0;
vector <int> odd;

void floyd(){
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j){
                if(map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
            }
}

bool vis[20] = {};
int addw = 1e9;
void dfs(int nn, int now, int weight){
    if(weight > addw) return;
    if(now == oddnum / 2) {
        addw = min(addw, weight);
        return;
    }
    int k;
    for(int i = nn; i < oddnum; ++i)
        if(!vis[i]) {
            k = i;
            break;
        }
    vis[k] = true;
    //printf("Now dfs: %d\n",k);
    for(int i = k + 1; i < oddnum; ++i)
        if(!vis[i]){
            vis[i] = true;
            dfs(k + 1, now + 1, weight + map[odd[k]][odd[i]]);
            vis[i] = false;
        }
    vis[k] = false;
}


int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            map[i][j] = map[j][i] = 1e9;
    for(int i = 1; i <= n; ++i) map[i][i] = 0;

    for(int i = 1; i <= m; ++i){
        int a,b,s;
        cin >> a >> b >> s;
        map[a][b] = map[b][a] = min(map[a][b],s);
        deg[a] ++;
        deg[b] ++;
        ans += s;
    }

    floyd();
    /*for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            printf("%d -> %d %d\n", i, j, map[i][j]);*/

    for(int i = 1; i <= n; ++i){
        if(deg[i] % 2 == 1) odd.push_back(i);
    }
    oddnum = odd.size();
    if(oddnum == 0) {
        cout << ans << endl;
        return 0;
    }

    dfs(0, 0, 0);
    ans += addw;
    cout << ans << endl;

    return 0;
}



