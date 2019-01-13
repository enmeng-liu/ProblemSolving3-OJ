//
// Created by 91342 on 2018/11/6.
//

#include <cstdio>

using namespace std;

int m, n;
int minstep = 100;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int g[25][25] = {};

void dfs(int x, int y, int step) {
    if (step >= 10 || step > minstep) return;

    for (int k = 0; k < 4; ++k) {
        int xx = x;
        int yy = y;
        while (xx > 0 && xx <= n && yy >= 0 && yy <= m) {
            switch (g[xx][yy]) {
                case 0:
                    xx += dx[k];
                    yy += dy[k];
                    break;
                    //是空地，一路向前走
                case 1:
                    if (xx - dx[k] != x || yy - dy[k] != y) {
                        g[xx][yy] = 0; //如果不是启动时就面对障碍物，可以把障碍物撞到，继续dfs
                        dfs(xx - dx[k], yy - dy[k], step + 1);
                        g[xx][yy] = 1; //搜出来不行，把障碍物放回去
                    }
                    xx = yy = -1; //不用进行下一次while循环了
                    break;
                case 3:
                    if (step + 1 < minstep) minstep = step + 1;
                    xx = yy = -1;
                    break;
                default:
                    break;
            }
        }
    }
}

int main() {
    int sx, sy;
    while (1) {
        scanf("%d%d", &m, &n);
        if (m == 0 || n == 0) break;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &g[i][j]);
                if (g[i][j] == 2) {
                    sx = i;
                    sy = j;
                    g[sx][sy] = 0;
                }
            }

        minstep = 100;
        dfs(sx, sy, 0);
        if (minstep <= 10) printf("%d\n", minstep);
        else printf("-1\n");
    }
}