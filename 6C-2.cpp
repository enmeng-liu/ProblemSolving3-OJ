//
// Created by 91342 on 2018/11/8.
//

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;

int T,m,n;
int edgesum;

struct node{
    int id;
    long long level;
    friend bool operator<( const node&a , const node&b ) {
        return a.level > b.level;
    }
}ver[50010]={};

vector <int> son[50010] = {};

struct edge{
    long long a;
    int b;
}e[100010]={};

vector <int> w[50010] = {};

int dijkstra(){
    priority_queue <node> q;
    ver[1].level = 1;
    q.push(ver[1]);

    while(!q.empty()){
        node u = q.top();
        int uid = u.id;
        /*if(uid == n) {
            int i = 1;
            while((1LL << i) <= ver[n].level) i++;
            if(i - 1 == 18 ) return 16;
            return i - 1;
        }*/
        q.pop();
        for(int i = 0; i < son[uid].size(); ++i){
            int vid = son[uid][i];
            int eid = w[uid][i];
            if(ver[vid].level < u.level) continue;
            long long cost = 1LL +  e[eid].a / ver[uid].level;
            if(cost < (1LL << e[eid].b)) continue;
            if(ver[vid].level > ver[uid].level + e[eid].a && cost >= (1LL << e[eid].b)){
                ver[vid].level = ver[uid].level + e[eid].a;
                if(vid == n) {
                    int i = 1;
                    while((1LL << i) <= ver[n].level) i++;
                    //if(i - 1 == 18 ) return 16;
                    return i - 1;
                }
                q.push(ver[vid]);
            }
        }
    }
    return -1;
}


int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 1;i <= n; ++i){
            ver[i].id = i;
            ver[i].level = INF;
            son[i].clear();
            w[i].clear();
        }
        edgesum = 0;


        for(int i = 1; i <= m; ++i){
            int u,v,b;
            long long a;
            scanf("%d%d%lld%d", &u,&v,&a,&b);
            son[u].push_back(v);
            edgesum ++;
            e[edgesum].a = a;
            e[edgesum].b = b;
            w[u].push_back(edgesum);
        }

        printf("%d\n",dijkstra());
    }
    return 0;
}
