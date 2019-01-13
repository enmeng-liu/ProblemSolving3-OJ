//
// Created by 91342 on 2018/11/19.
//

#include <cstdio>
#include <vector>
#include <queue>
#define N 200010
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;

int n,m;

vector <int> son[N];
vector <long long> w[N];

struct node{
    int id;
    long long d;
    friend bool operator < (const node&a , const node&b) {
        return a.d > b.d;
    }
}ver[N];

void dijkstra(){
    priority_queue <node> q;
    ver[0].d = 0;
    ver[0].id = 0;
    q.push(ver[0]);

    while (!q.empty()){
        node u = q.top();
        q.pop();

        for(int i = 0; i < son[u.id].size(); ++i){
            int vid = son[u.id][i];
            if(ver[vid].d <= u.d) continue;
            if(ver[vid].d > u.d + w[u.id][i]){
                ver[vid].d = u.d + w[u.id][i];
                q.push(ver[vid]);
            }
        }
    }
}

int main(){
    scanf("%d%d", &n,&m);
    for(int i = 1; i <= m; ++i){
        int a,b;
        long long ww;
        scanf("%d%d%lld",&a,&b,&ww);
        ww *= 2;
        son[a].push_back(b);
        w[a].push_back(ww);
        son[b].push_back(a);
        w[b].push_back(ww);
    }
    for(int i = 1; i <= n; ++i){
        long long cost;
        scanf("%lld",&cost);
        son[0].push_back(i);
        w[0].push_back(cost);
        ver[i].id = i;
        ver[i].d = INF;
    }

    dijkstra();

    for(int i = 1; i <= n; ++i){
        printf("%lld",ver[i].d);
        if(i == n) printf("\n");
        else  printf(" ");
    }
}
