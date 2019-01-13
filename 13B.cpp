//
// Created by 91342 on 2018/12/27.
//

#include <iostream>
#include <assert.h>
using namespace std;

#define N 110

int n,m;
double a[N][N] = {}; //系数矩阵


void swap2row(int x, int y) {
    for(int i = 1; i <= n + 1; ++i) swap(a[x][i], a[y][i]);
    //printf("**swap row %d with row %d**\n",x,y);
}

void pivot_one(int x, int y) {
    double temp = a[x][y];
    if(temp == 1) return;
    for(int i = y; i <= n + 1; ++i) a[x][i] /= temp;
    //printf("**pivot one at row %d**\n", x);
}

void mul_and_add(int src, int dst, double cof) {
    for(int i = 1; i <= n + 1; ++i) {
        a[dst][i] -= a[src][i] * cof;
    }
    //printf("**mul row %d with %lf add to row %d**\n", src, cof, dst);
}

void print_matrix() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) printf("%lf ", a[i][j]);
        printf("| %lf\n", a[i][n + 1]);
    }
    printf("------------------------\n");
}

bool iszero(int row) {
    for(int i = 1; i <= n + 1; ++i)
        if(a[row][i] != 0) return false;
    return true;
}

void Guass() {
    int row = 1, col = 1;
    bool ok = false;
    while(row <= n && col <= n) {
        //printf("Now row=%d, col=%d\n",row, col);
        if(a[row][col] == 0.0) {
            ok = false;
            for(int i = row + 1; i <= n; ++i)
                if(a[i][col] != 0) {
                    swap2row(row, i);
                    ok = true;
                    break;
                }
            if(ok == false) {col++; continue;}
            //else print_matrix();
        }
        pivot_one(row,col);
        if(col == n && row == n && a[row][col] == 1) return;
        //print_matrix();
        for(int i = 1; i <= n; ++i)
            if(i != row && a[i][col] != 0) {
                assert(a[row][col] != 0);
                double cof = a[i][col] / a[row][col];
                if(cof != 0) mul_and_add(row, i, cof);
                assert(a[i][col] == 0);
            }
        //print_matrix();
        row ++; col ++;
    }
}



int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        int x,y;
        double r;
        scanf("%d%d%lf", &x, &y, &r);
        double s = 1.0 / r;
        a[x][x] += s;
        a[y][y] += s;
        a[x][y] -= s;
        a[y][x] -= s;
    }
    a[n][n] += 1;

    a[1][n+1] = 1.0;
    a[n][n+1] = -1.0;
    //print_matrix();

    Guass();
    double u1 = a[1][n + 1];
    double un = a[n][n + 1];
    printf("%.2lf\n", u1 - un);
    return 0;
}