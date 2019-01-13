//
// Created by 91342 on 2018/12/17.
//
#include <iostream>
#define N 1000010
using namespace std;

int T;
int n;
long long a[N] = {};
long long b[N] = {};
long long ans = 0;
long long suma = 0, sumb = 0;

int main() {
    scanf("%d", &T);
    while(T--) {
        suma = 0;
        sumb = 0;
        ans = 1e9;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i], &b[i]);
            suma += a[i];
            sumb += b[i];
        }
        ans = min(suma, sumb);
        long long sum = suma + sumb;
        for(int i = 1; i <= n; ++i) {
            ans = min(ans, sum - a[i] - b[i]);
        }
        printf("%lld\n", ans);
    }
}