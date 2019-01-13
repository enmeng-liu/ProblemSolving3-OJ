//
// Created by 91342 on 2018/11/13.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int n,m,t;
int w[60] = {};
int map[60][60] = {};
int minw = 1e9;
bool visited[60] = {};

vector <int> son[60];
vector <int> path;


void dfs1(int w1, int w2, int u, int cost){
    //当前二人，当前结点，当前前驱，当前总代价
    if(visited[u])  return;
    visited[u] = 1;
    //cout << u <<" ";

    if(u == t){
        //cout << endl;
        if(cost < minw) minw = cost;
        visited[u] = 0;
        return;
    }
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        //cout << v << " " << visited[v] << endl;
        //assert(v < 60);
        if(!visited[v]) {
            //visited[v] = 1;
            dfs1(w2,w[v],v,cost + (w1 + w2) * map[u][v]);
        }
    }
    visited[u] = 0;
}

void dfspath(int w1, int w2, int u, int cost){
    if(visited[u])  return;
    visited[u] = 1;
    //printf("Now dfs(%d,%d,%d,%d)\n",w1,w2,u,cost);

        //assert(pre >= 0 && pre < 60 && u >= 0 && u < 60);

    if(u == t){
        if(cost == minw) {
            for(int i = 0; i < path.size(); ++i){
                cout << path[i] << (i == path.size()-1 ? "\n" : " ");
            }
            exit(0);
        }
        else {
            visited[u] = 0;
            return;
        }
    }
    for(int i = 0; i < son[u].size(); ++i){
        int v = son[u][i];
        //cout << v << " " << visited[v] << endl;
        path.push_back(v);
        //assert(v < 60);
        if(!visited[v]) {
            //cout << v << " " << w[v] << endl;
            dfspath(w2,w[v],v,cost + (w1 + w2) * map[u][v]);
        }
        path.pop_back();
    }
    visited[u] = 0;
}


int main(){
    int w1,w2;
    cin >> n >> m >> w1 >> w2;
    for(int i = 1; i <= n; ++i){
        cin >> w[i];
    }
    for(int i = 0; i < m; ++i){
        int a,b,l;
        cin >> a >> b >> l;
        son[a].push_back(b);
        //len[a].push_back(l);
        map[a][b] = l;
    }
    cin >> t;

    if(w1 < w2) swap(w1,w2);
    dfs1(w1,w2,0,0);
    //cout << minw << endl;
    memset(visited,0,sizeof(visited));

    path.push_back(0);
    dfspath(w1,w2,0,0);

    return 0;

}

