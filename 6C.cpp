//
// Created by 91342 on 2018/11/8.
//

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int T,n,m;
int edgesum;

struct edge{
    int a,b;
}e[100010] = {};

struct node{
    int id;
    int visited;
    long long level;
    friend bool operator < (const node& a, const node &b){
        return a.level > b.level;
    }
}v[50010]={};

//vector <node> son[50010];
vector <int> son[50010];
vector <int> w[100010];




int dijkstra(){
    v[1].level = 1;
    v[1].visited = 1;
    priority_queue <node> q;
    q.push(v[1]);

    while(!q.empty()){
        int u = (q.top()).id;
        q.pop();

        if(u == n){
            int i = 1;
            while((1LL << i) <= v[u].level) i ++;
            return i - 1;
        }

        if(v[u].visited == 1) continue;
        v[u].visited = 1;

        for(int i = 0; i < son[u].size(); ++i){
            int vv = son[u][i];
            if(v[vv].visited == 1) continue;
            long long  cost = (v[u].level + e[w[u][i]].a) / v[u].level;
            if(v[vv].level > v[u].level + e[w[u][i]].a && cost >= (1LL << e[w[u][i]].b)){
                v[vv].level = v[u].level + e[w[u][i]].a;
                q.push(v[vv]);
            }
        }
    }
    return -1;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        edgesum = 0;
        for(int i = 1; i <= n; ++i){
            v[i].id = i;
            v[i].visited = 0;
            v[i].level = 1e9;
        }
        for(int i = 1; i <= m; ++i){
            int uu,vv,aa,bb;
            scanf("%d%d%d%d",&uu,&vv,&aa,&bb);
            son[uu].push_back(vv);
            e[++edgesum].a = aa;
            e[edgesum].b = bb;
            w[uu].push_back(edgesum);
        }
        printf("%d\n",dijkstra());
    }
}