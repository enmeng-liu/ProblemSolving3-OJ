//
// Created by 91342 on 2018/12/11.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <assert.h>
#define N 210
#define MAX 3000
using namespace std;

int n, m, num;
int map[N][N] = {};
int dist[N][N] = {};
bool S[N] = {}, T[N] = {};
int match[N] = {};
int ls[N] = {}, lt[N] = {};

bool find(int i) {
    S[i] = true;
    for (int j = 1; j <= num; ++j) {
        if (!T[j] && ls[i] + lt[j] == map[i][j]) {
            T[j] = true;
            if (!match[j] || find(match[j])) {
                match[j] = i;
                return true;
            }
        }
    }
    return false;
}

void relax() {
    int relax_val = 1e9;
    for(int i = 1; i <= min(n,m); ++i)
        if(S[i]) {
            for(int j = 1; j <= num; ++j)
                if(!T[j] && ls[i] + lt[j] > map[i][j]) relax_val = min(relax_val, ls[i] + lt[j] - map[i][j]);
        }
    assert(relax_val > 0);

    for (int i = 1; i <= num; ++i) {
        if (S[i]) ls[i] -= relax_val;
        if (T[i]) lt[i] += relax_val;
    }
}

int KM() {
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= min(m,n); ++i) {
        ls[i] = 0;
        for (int j = 1; j <= num; ++j) ls[i] = max(map[i][j], ls[i]);
    }
    for(int i = 1; i <= num; ++i) lt[i] = 0;

    for (int i = 1; i <= min(n,m); ++i) {
        while (1) {
            memset(S, 0, sizeof(S));
            memset(T, 0, sizeof(T));
            if (find(i)) break;
            else relax();
        }
    }
}

struct node {
    int x, y;
};
node lost_mouse[N] = {};
node lost_kbd[N] = {};

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        lost_mouse[i].x = x;
        lost_mouse[i].y = y;
    }
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        lost_kbd[i].x = x;
        lost_kbd[i].y = y;
    }
    //理想情况：n >= m

    num = max(m, n);
    if (m > n) {
        swap(m, n);
        for (int i = 1; i <= m; ++i) swap(lost_mouse[i], lost_kbd[i]);
        for(int i = m + 1; i <= num; ++i) {
            lost_kbd[i] = lost_mouse[i];
            lost_mouse[i] = {0,0};
        }
    }


    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = abs(lost_mouse[i].x - lost_kbd[j].x) + abs(lost_mouse[i].y - lost_kbd[j].y);
            map[i][j] = MAX - dist[i][j];
            //求最小权匹配，因此全部取负
        }

    KM();
    int ans = 0;
    for (int i = 1; i <= num; ++i)
        if(match[i]) ans += dist[match[i]][i];

    printf("%d\n", ans);
    return 0;
}
