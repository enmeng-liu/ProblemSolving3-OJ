#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>

using namespace std;

long long f[35][35] = {};
int r[35] = {}, b[35] = {};
int n, m, i, j, k;
string s;

int main() {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        cin >> s;
        b[i] = 0;
        r[i] = m + 1;
        for (j = 0; j < m; ++j) {
            if (s[j] == 'B') b[i] = max(b[i], j + 1);
            else if (s[j] == 'R') r[i] = min(r[i], j + 1);
        }
    }
    for (j = b[1]; j < r[1]; ++j) f[1][j] = 1;
    for (i = 2; i <= n; ++i) {
        for (j = b[i]; j < r[i]; ++j) {
            for (k = j; k <= m; ++k)
                f[i][j] += f[i - 1][k];
            //f[i][j]表示第i行分界点在j位置的染色方案数
        }
    }

    long long ans = 0;
    for (i = b[n]; i < r[n]; ++i)
        ans += f[n][i];

    //for(i = 1; i <= n; ++i)  cout<<b[i]<<" "<<r[i]<<endl;

/*	for(i = 0; i <= n; ++i)
		for(j = 0; j <= m; ++j)
			cout<<f[i][j]<<(j==m?"\n":" ");*/

    cout << ans << endl;


    return 0;
}

