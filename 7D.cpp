//
// Created by 91342 on 2018/11/20.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#define INF 1e9
using namespace std;

int n,m,W;
int c[130] = {};
int f[130][130] = {};
int dist[130][130][130] = {};

vector <int> son[130];
vector <int> w[130];

void floyd(){
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j){
                if(f[i][j] > f[i][k] + f[k][j])
                    f[i][j] = f[i][k] + f[k][j];
            }
}


struct node{
    int id;
    int d;
    friend bool operator < (const node&a , const node&b) {
        return a.d > b.d;
    }
}ver[130] = {};

void dijkstra(int s, int dig){
    if(s == dig){
        for(int i = 1; i <= n; ++i) dist[s][dig][i] = INF;
        return;
    }
    for(int i = 1; i <= n; ++i){
        ver[i].d = INF;
    }

    priority_queue <node> q;
    ver[s].d = 0;
    q.push(ver[s]);
    while(!q.empty()){
        node u = q.top();
        q.pop();
        for(int i = 0; i < son[u.id].size(); ++i){
            int vid = son[u.id][i];
            if(vid == dig) continue;
            if(ver[vid].d <= ver[u.id].d) continue;
            if(ver[vid].d > ver[u.id].d + w[u.id][i]){
                ver[vid].d = ver[u.id].d + w[u.id][i];
                q.push(ver[vid]);
            }
        }
    }
    for(int i = 1; i <= n; ++i) dist[s][dig][i] = ver[i].d;

}

int main(){
    scanf("%d%d%d",&n,&m,&W);

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j){
            if(i == j) f[i][j] = 0;
            else f[i][j] = INF;
    }

    for(int i = 1; i <= n; ++i){
        ver[i].id = i;
    }

    for(int i = 1; i <= m; ++i){
        int u,v,t;
        scanf("%d%d%d",&u,&v,&t);
        son[u].push_back(v);
        w[u].push_back(t);
        f[u][v] = t;
    }

    floyd();
    //for(int i = 1; i <= n; ++i)
        //for(int j = 1; j <= n; ++j)
            //printf("f[%d][%d] = %d\n",i,j,f[i][j]);

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j){
            dijkstra(i,j);
        }

     /*for(int i = 1; i <= n; ++i)
         for(int j = 1; j <= n; ++j)
             for(int k = 1; k <= n; ++k)
                 printf("dist[%d][%d][%d]=%d\n",i,j,k,dist[i][j][k]);*/

    while(W--){
        int ans = INF;
        for(int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            //printf("Now i = %d, x = %d\n",i,x);
            c[i] = x;
            if(c[i] == i) {
               ans = 0;
            }
        }

        //for(int i = 1; i <= n; ++i)
            //printf("c[%d] = %d\n",i,c[i]);

        if(ans == 0) {
            printf("0\n");
            continue;
        }
        for(int i = 1; i <= n; ++i){
            int j = c[i];
            int k = c[j];
            if(dist[i][j][k]<INF && f[i][j]<INF && f[k][j]<INF ){
                //printf("%d->%d->%d: %d\n",i,j,k,dist[i][j][k] + f[k][j] + f[j][k]);
                ans = min(ans, dist[i][j][k] + f[k][j] + f[j][k]);
            }

        }
        if(ans >= INF) printf("bug\n");
        else printf("%d\n",ans);
    }
    return 0;
}
