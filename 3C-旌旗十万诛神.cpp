#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
int f[100010]={};

int find(int x){
	int root = f[x];
	while(root != f[root]) root = f[root];
	int y = f[x];
	while(f[x] != root){
		f[x] = f[y];
		y = f[y];
	}
	return f[x];
}

void kill(int i){
	 f[find(i)] = find(f[i+1]); 
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i <= n; ++i) f[i] = i;
	while(m--){
		char s[10]="";
		int x;
		scanf("%s%d",&s,&x);
		if(strcmp(s,"Find") == 0){
			int ans = find(x);
			if(ans >= n) ans = -1;
			printf("%d\n",ans);
		}
		else if(strcmp(s,"Kill")==0) kill(x);
		
	}


return 0;
}

