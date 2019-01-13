//
// Created by 91342 on 2018/11/13.
//

#include <cstdio>
#include <vector>
using namespace std;

const int INF = 1e9;
int n,m,s,t;
int dist[1010] = {};
int pre[1010] = {};
int map[1010][1010] = {};
bool visited[1010] = {};

vector <int> son[1010];
vector <int> w[1010];

void dijkstra(){
    dist[s] = 0;

   for(int i = 1; i <= n; ++i){
       int u, mind = INF;
       for(int j = 1; j <= n; ++j){
           if(!visited[j] && dist[j] < mind) mind = dist[j], u = j;
       }
       visited[u] = true;

       for(int j = 0; j < son[u].size(); ++j){
           int v = son[u][j];
           if(!visited[v] && dist[v] > dist[u] + w[u][j]){
               dist[v] = dist[u] + w[u][j];
               pre[v] = u;
           }
       }
   }
}

void output(){
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j){
            printf("%d",dist[j] - dist[i]);
            if(j == n) printf("\n");
            else printf(" ");
        }
}

int main(){
    scanf("%d%d",&n,&m);
    if(m == 0) {
        printf("-1\n");
        return 0;
    }
    for(int i = 0; i <= n; ++i) dist[i] = INF;
    for(int i = 0; i < m; ++i){
        int v,u,time;
        scanf("%d%d%d",&u,&v,&time);
        son[u].push_back(v);
        w[u].push_back(time);
        //dist[u] = dist[v] = INF;
    }
    scanf("%d%d",&s,&t);
    dijkstra();
    if(dist[t] < INF)  {
        printf("%d\n", dist[t]);
        output();
    }
    else printf("-1\n");
    return 0;
}