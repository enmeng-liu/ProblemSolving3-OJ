//
// Created by 91342 on 2018/12/6.
//

#include <iostream>
#include <cstring>
#include <string>
#define N 450
using namespace std;

int T,r,c;
int n;
int id[45][15] = {};
bool map[N][N] = {};
int match[N] = {};
bool vis[N] = {};
string s[45];

void add_edge(int x1, int y1, int x2, int y2){
    int a = id[x1][y1];
    int b = id[x2][y2];
    map[a][b] = map[b][a] = true;
}

void build_graph(){
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j){
            if(s[i][j] == '*'){
                if(i >= 1 && s[i - 1][j] == '*') add_edge(i, j, i - 1, j);
                if(i < r - 1 && s[i + 1][j] == '*') add_edge(i, j, i + 1, j);
                if(j >= 1 && s[i][j - 1] == '*') add_edge(i, j, i, j - 1);
                if(j < c - 1 && s[i][j + 1] == '*') add_edge(i, j , i, j + 1);
            }
        }
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

int max_match(){
    int ret = 0;
    for(int i = 1; i <= n; ++i){
        memset(vis, 0, sizeof(vis));
        if(find(i)) ret ++;
    }
    return ret;
}

int main(){
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &r, &c);
        n = 0;
        for(int i = 0; i < r; ++i) {
            cin >> s[i];
            for(int j = 0; j < s[i].size(); ++j){
                if(s[i][j] == '*') {
                    n ++;
                    id[i][j] = n;
                }
            }
        }

        memset(map, 0, sizeof(map));
        memset(match, 0, sizeof(match));

        build_graph();
        int matching = max_match();
        int ans = n - matching / 2;
        //无向二部图的最小路径覆盖数 = 顶点数 - 最大二分匹配数/2
        printf("%d\n", ans);
    }
    return 0;
}