#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

const int M = 1e9+7;
long long a[15][15]={};
int degree[15]={};
bool v[15][15]={};
int T,n,m,sign;

int gauss(int n){
	sign = 0;
	long long ans = 1;
	for(int i = 1; i < n; ++i){
		for(int j = i+1; j < n; ++j){
			int x = i, y = j;
			while(a[y][i]){
				long long t = a[x][i] / a[y][i];
				for(int k = i; k < n; ++k){
					a[x][k] = (a[x][k] - a[y][k] * t) % M;
				}
				swap(x,y);
			}
			if(x != i){
				for(int k = 1; k < n; ++k)
					swap(a[i][k], a[x][k]);
				sign ^= 1;
			}
		}
	if(!a[i][i]) return 0;
	else ans = ans * a[i][i] % M;
	}
	if(sign != 0) ans *= -1;
	if(ans < 0) ans += M;
	return ans;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n,&m);
		memset(degree,0,sizeof(degree));
		memset(v,0,sizeof(v));
		for(int i = 1; i <= 12; ++i)
			for(int j = 1; j <= 12; ++j)
				a[i][j] = 0;
		for(int i = 1; i <= m; ++i){
			int x,y;
			scanf("%d%d", &x,&y);
			if(x != y && !v[x][y] && !v[y][x]){
				a[x][y] = a[y][x] = -1;
				v[x][y] = v[y][x] = 1;
				degree[x] ++;
				degree[y] ++;
			}
			
		}
		
		for(int i = 1; i <= n; ++i) a[i][i] = degree[i];
		int ans = gauss(n);
		printf("%d\n",ans);
		
	}
	
return 0;
}

