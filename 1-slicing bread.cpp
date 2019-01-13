#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

int f[22][22][22][22]={};//dp数组
int num[22][22][22][22]={};//樱桃数量统计
int n,m,k,rnd=0,i,j,a,b; 

int dp(int a, int b, int i, int j){
	if(num[a][b][i][j] == 1) return 0;
	if(f[a][b][i][j] >= 0) return f[a][b][i][j];
	
	int q = 1e9;
	for(int ii = 1; ii < i; ++ii)
		if(num[a][b][ii][j] && num[a+ii][b][i-ii][j])
			q = min(dp(a,b,ii,j) + dp(a+ii,b,i-ii,j) + j, q);
	//枚举行 
	for(int jj = 1; jj < j; ++jj)
		if(num[a][b][i][jj] && num[a][b+jj][i][j-jj])
			q = min(dp(a,b,i,jj) + dp(a,b+jj,i,j-jj) + i, q);
	//枚举列 
	f[a][b][i][j] = q;
	return q;
}
//带备忘的递归dp 

int main(){
	while(scanf("%d%d%d",&n,&m,&k) == 3){
		rnd++;
		memset(f,-1,sizeof(f));
		memset(num,0,sizeof(num));
		//initialize
		
		for(i = 1; i <= k; ++i) {
			scanf("%d%d", &a, &b);
			num[a][b][1][1]=1;
		}
		
		for(a = 1; a <= n; ++a)
			for(b = 1; b <= m; ++b)
				for(i = 1; i <= n - a + 1; ++i)
					for(j = 1; j <= m - b + 1; ++j){
					num[a][b][i][j] = num[a][b][i][j-1]
									   +num[a][b][i-1][j]
									   -num[a][b][i-1][j-1]
									   +num[a+i-1][b+j-1][1][1];
					}
		//计算num数组，其中[a][b][i][j]表示以(a,b)左上角i*j的矩形
		//cout<<"The number of cherries: "<<num[1][1][n][m]<<endl;
		int ans = dp(1,1,n,m); 
		printf("Case %d: ", rnd);
		printf("%d\n", ans);
	}



return 0;
}

