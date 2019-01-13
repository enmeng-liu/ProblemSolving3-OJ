//
// Created by 91342 on 2018/12/9.
//

#include <iostream>
#include <queue>
#include <cstring>
#define N 450
using namespace std;

int n, F, D;
#define FOOD(x) x
#define COW1(x) x + F
#define COW2(x) x + F + n
#define DRINK(x) x + F + n + n
//#define MAXN  F + n * 2 + D
const int s = 0;
#define t  F + n * 2 + D + 1

//int c[N][N] = {};
//int f[N][N] = {};
int map[N][N] = {};
int pre[N] = {};


int bfs(){
    //bool flag = false;
    //memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    int minc = 1e9;

    queue <int> q;
    q.push(s);

    while(!q.empty()){
        int u = q.front();
        if(u == t) break;
        for(int i = 1; i <= t; ++i) {
            if(pre[i] == -1 && map[u][i]) {
                minc = min(minc, map[u][i]);
                q.push(i);
                pre[i] = u;
            }
        }
        q.pop();
    }

    int tt = t;
    /*while (tt != s){
        printf("%d ", tt);
        tt = pre[tt];
    }
    printf("; minc = %d\n", minc);*/

    if(pre[t] == -1) return -1;
    else return minc;
}

int edmonds_karp() {
    int ans = 0;
    int minc;
    while((minc = bfs()) != -1) {
        ans += minc;
        int tt = t,pt;
        while(tt != s) {
            pt = pre[tt];
            map[pt][tt] -= minc;
            map[tt][pt] += minc;
            tt = pt;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &F, &D);
    for (int i = 1; i <= n; ++i) {
        int f, d;
        scanf("%d%d", &f, &d);
        map[COW1(i)][COW2(i)] = 1;

        for (int j = 1; j <= f; ++j) {
            int x;
            scanf("%d", &x);
            map[FOOD(x)][COW1(i)] = 1;
            map[s][FOOD(x)] = 1;
        }

        for (int j = 1; j <= d; ++j) {
            int x;
            scanf("%d", &x);
            //son[COW2(i)].push_back(DRINK(x));
            //c[COW2(i)][DRINK(x)] = 1;
            map[COW2(i)][DRINK(x)] = 1;
            map[DRINK(x)][t] = 1;
        }
    }
    //Build graph: s->F->C1->C2->D->t, all capacity = 1

    /*for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            if(map[i][j]) printf("%d -> %d: c = %d\n", i, j, c[i][j]);*/

    int ans = edmonds_karp();
    printf("%d\n", ans);

    return 0;
}
