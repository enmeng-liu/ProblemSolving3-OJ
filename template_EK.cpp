//
// Created by 91342 on 2018/12/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define inf 1000
#define nMax 410
#define Max(a, b) (a>b?a:b)
#define Min(a, b) (a<b?a:b)

int map[nMax][nMax];
int N, F, D;
int path[nMax];
int queue[nMax * 100];
int head, end;

//bool flag[nMax];
//广搜求一条增广路
int bfs() {
    int minFlow = inf, u;
    memset(path, -1, sizeof(path));
    head = 0;
    end = 1;
    queue[head] = 0;
    while (head < end) {
        u = queue[head++];
        if (u == 2 * N + F + D + 1) {
            break;
        }
        for (int i = 1; i <= 2 * N + F + D + 1; ++i) {
            if (path[i] == -1 && map[u][i]) {
                if (minFlow > map[u][i]) {
                    minFlow = map[u][i];
                }
                queue[end++] = i;
                path[i] = u;

            }
        }
    }
    if (path[2 * N + F + D + 1] == -1) {
        return -1;
    }
    return minFlow;
}

//EK算法，每次广搜得到一条增广路径，然后更新残留网络
void Edmods_Karp() {
    int flow, maxFlow = 0, now, pre;
    while ((flow = bfs()) != -1) {
        maxFlow += flow;
        now = 2 * N + F + D + 1;
        while (now != 0) {
            pre = path[now];
            map[pre][now] -= flow;
            map[now][pre] += flow;
            now = pre;
        }
    }
    printf("%d\n", maxFlow);
}

//按照源点-食物-牛-牛-饮料-汇点的顺序建图
void buildMap() {
    int fNum, dNum, fd;
    while (scanf("%d %d %d", &N, &F, &D) != EOF) {
        memset(map, 0, sizeof(map));
        //memset(flag, false, sizeof(flag));
        for (int i = 1; i <= N; ++i) {
            scanf("%d %d", &fNum, &dNum);
            for (int j = 0; j < fNum; ++j) {
                scanf("%d", &fd);
                map[0][fd] = 1;
                map[fd][i + F] = 1;
            }
            map[i + F][i + F + N] = 1;
            for (int j = 0; j < dNum; ++j) {
                scanf("%d", &fd);
                map[fd + 2 * N + F][F + 2 * N + D + 1] = 1;
                map[i + F + N][fd + 2 * N + F] = 1;
            }
        }
        Edmods_Karp();
    }
}
//注意这里给点编号，0-源点，1-F是食物，F+1-F+N是牛左点，F+N+1-F+N+N是牛右点，F+N+N+1-F+N+N+D是drink饮料点，F+N+N+D+1是汇点

int main() {
    buildMap();
    return 0;
}
