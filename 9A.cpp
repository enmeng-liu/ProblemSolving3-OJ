//
// Created by 91342 on 2018/12/4.
//

#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int n;

struct node{
    int indeg;
    int outdeg;
    int deg;
}ver[128];

bool map[128][128] = {};
bool vis[128] = {};
int visited = 0;
bool app[128] = {};
int appear = 0;

void dfs(int u){
    //printf("Now dfs %c\n",(char)u);
    vis[u] = true;
    visited ++;
    for(int i = 'a'; i <= 'z'; ++i){
        if(!vis[i] && map[u][i]) dfs(i);
    }
}

bool isconnected(){
    for(int i = 'a'; i <= 'z'; ++i){
        if(app[i]) {
            dfs(i);
            break;
        }
    }
    //printf("appear: %d, visited: %d\n",appear, visited);
    if(visited == appear) return true;
    else return false;
}

bool directed_euler(){
    int moreout = 0;
    int morein = 0;
    for(int i = 'a'; i <= 'z'; ++i){
        if(ver[i].indeg > ver[i].outdeg) {
            if(ver[i].indeg == ver[i].outdeg + 1) morein ++;
            else return false;
        }
        else if(ver[i].deg < ver[i].outdeg) {
            if(ver[i].outdeg == ver[i].indeg + 1) moreout++;
            else return false;
        }
    }
    //printf("morein = %d, moreout = %d", morein, moreout);
    if(morein <= 1 && moreout <= 1) return true;
    else return false;
}
//判断连通有向图是否含欧拉迹
//至多一顶点出度=入度+1
//至多一顶点入度=出度+1
//其余顶点：入度=出度

bool undirected_euler(){
    int odd = 0;
    for(int i = 'a'; i <= 'z'; ++i)
        if(ver[i].deg % 2 == 1) odd++;
    if(odd == 0 || odd == 2) return true;
    else return false;
};

int main(){
    cin >> n;
    for(int i = 'a'; i <= 'z'; ++i)
        ver[i].indeg = ver[i].outdeg = ver[i].deg = 0;
    for(int i = 1; i <= n; ++i){
        string s;
        cin >> s;
        int a = (int)s[0];
        int b = (int)s[s.size() - 1];
        ver[a].outdeg ++;
        ver[a].deg ++;
        ver[b].indeg ++;
        ver[b].deg ++;
        map[a][b] = map[b][a] = 1;
        if(!app[a]) {app[a] = 1; appear ++;}
        if(!app[b]) {app[b] = 1; appear ++;}
    }



    if(!isconnected()) {
        //printf("Not connected:");
        cout << "Nothing\n";
        return 0;
    }
    if(directed_euler()) {
        cout << "Gold\n";
        return 0;
    }
    if(undirected_euler()){
        cout << "Silver\n";
        return 0;
    }
    //printf("No euler:");
    cout << "Nothing\n";
    return 0;

}