//
// Created by 91342 on 2018/12/28.
//

#include <iostream>
#include <cstring>

using namespace std;

#define N 60

int K;
int n;
bool a[N][N] = {};

void swap2row(int x, int y) {
    for (int i = 0; i <= n; ++i) swap(a[x][i], a[y][i]);
    //printf("**swap row %d with row %d**\n",x,y);
}

bool iszero(int row) {
    for (int i = 0; i < n; ++i) if (a[row][i] != 0) return false;
    return true;
}

void print_matrix() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%d ", a[i][j]);
        printf("| %d\n", a[i][n]);
    }
    printf("------------------------\n");
}


int Gauss() {
    int row, col, i, j, max_r;

    row = col = 0;
    while (row < n && col < n) {
        max_r = row;
        for (i = row + 1; i < n; i++) {
            if (abs(a[i][col]) > abs(a[max_r][col]))
                max_r = i;
        }
        if (max_r != row) {
            for (j = col; j < n + 1; j++)
                swap(a[max_r][j], a[row][j]);
        }
        if (a[row][col] == 0) {
            col++;
            continue;
        }

        for (i = row + 1; i < n; i++) {
            if (a[i][col] == 0) continue;
            for (j = col; j < n + 1; j++)
                a[i][j] ^= a[row][j];
        }
        row++;
        col++;
    }

    for (i = row; i < n; i++)
        if (a[i][col] != 0) return -1; //无解
    if (row < n) return n - row;  //返回自由变元个数
    for (i = n - 1; i >= 0; i--) {
        for (j = i + 1; j < n; j++)
            a[i][n] ^= (a[i][j] && a[j][n]);
    }
    return 0;
}

int main() {
    scanf("%d", &K);
    while (K--) {
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i][n]);
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            a[i][n] ^= x;
            a[i][i] = 1;
        }
        while (1) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == 0 && y == 0) break;
            a[y - 1][x - 1] = 1;
        }
        //print_matrix();
        int ans = Gauss();
        //print_matrix();
        if (ans == -1) printf("Oh,it's impossible~!!\n");
        else printf("%d\n", 1 << ans);
    }
    return 0;
}