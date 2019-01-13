#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int T,n,i;
int a[3010]={};

int lis(int a[],int n){
	int i,j;
	int f[3010]={};
	f[1] = 1;
	for(i=2; i <= n; ++i){
		f[i] = 1;
		for(j = 1; j < i; ++j){
			if(a[j] < a[i] && a[i] - a[j] >= i - j)  
				f[i] = max(f[i],f[j]+1);
		}
	}
	int q = -1;
	for(i = 1; i <= n; ++i)
		q = max(q, f[i]);
	return q;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		
		printf("%d\n", n-lis(a,n));
	}

return 0;
}

