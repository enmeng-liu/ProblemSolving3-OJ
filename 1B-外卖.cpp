#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

int need[20] = {};//need[]���ڴ洢��Ҫ������������
int a[20][20] = {};
int f[20][65540] = {};
//f[i][s]��ʾ��״̬s��ʼ�ߵ�i����������Ž�
//����ʹ����λ��ʾ����¼״̬�����ⷽ�� 
//1��ʾ�߹���0��ʾû�߹�
int c[20][65540] = {};
//c[i][k]��ʾ��k���ߵ�i����������Ž���һ�ξ�������j���� 
int two[20] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
int n, i, j, k, num = 0;

int dfs(int i, int rnd, int status) {
    int j;
    if (status == two[num] - 1) return 0;
    if (f[i][status] > 0) return f[i][status];
    int q = 1e9;
    for (j = num; j > 0; --j) {
        int temp = 1 << (j - 1);
        if (j != i && (!(status & temp))) {
            if (q > dfs(j, rnd + 1, status | temp) + a[need[i]][need[j]]) {
                q = dfs(j, rnd + 1, status | temp) + a[need[i]][need[j]];
                c[i][status] = j;
            }
        }
    }
    f[i][status] = q;
    return q;
}


int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        int temp;
        scanf("%d", &temp);
        if (temp) {
            num++;
            need[num] = i;
        }
    }
    for (i = 0; i <= n; ++i)
        for (j = 0; j <= n; ++j) {
            scanf("%d", &a[i][j]);
        }

    cout << dfs(0, 0, 0) << endl;
    cout << need[c[0][0]] << (num == 1 ? "\n" : " ");
    int d = c[0][0], status = 0;
    for (i = 1; i < num; ++i) {
        int temp = 1 << (d - 1);
        status |= temp;
        d = c[d][status];
        cout << need[d] << (i == num ? "\n" : " ");
    }


    return 0;
}

