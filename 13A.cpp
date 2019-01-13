//
// Created by 91342 on 2018/12/28.
//

#include <iostream>
#include <cstring>

using namespace std;

#define N 40
const int n = 30;
int a[N][N] = {};
int T;
//下标从0开始

void swap2row(int x, int y) {
    for (int i = 0; i <= n; ++i) swap(a[x][i], a[y][i]);
    //printf("**swap row %d with row %d**\n",x,y);
}

void print_matrix() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%d ", a[i][j]);
        printf("| %d\n", a[i][n]);
    }
    printf("------------------------\n");
}


void Gauss() {
    int row = 0, col = 0;
    while (row < n && col < n) {
        if (a[row][col] == 0) {
            for (int i = row + 1; i < n; ++i)
                if (a[i][col] != 0) swap2row(row, i);
            if (a[row][col] == 0) {
                col++;
                continue;
            }
        }
        //if(col == n - 1 && row == n - 1 && a[row][col] == 1) return;
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col] != 0) {
                for (int j = 0; j <= n; ++j) a[i][j] ^= a[row][j];
            }
        }
        row++;
        col++;
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) a[i][n] ^= (a[i][j] && a[j][n]);
    }
}

void init() {
    for (int i = 0; i < n; ++i) {
        if (i % 6 != 0) a[i][i - 1] = 1;
        if (i % 6 != 5) a[i][i + 1] = 1;
        if (i >= 6) a[i][i - 6] = 1;
        if (i < 24) a[i][i + 6] = 1;
        a[i][i] = 1;
    }
}



int main() {
    scanf("%d", &T);
    for (int l = 1; l <= T; ++l) {
        init();
        for (int i = 0; i < n; ++i) scanf("%d", &a[i][n]); //右端项
        Gauss();
        printf("PUZZLE #%d\n", l);
        for (int i = 0; i < n; ++i) {
            printf("%d", a[i][n]);
            if (i % 6 == 5) printf("\n");
            else printf(" ");
        }
    }

    return 0;
}