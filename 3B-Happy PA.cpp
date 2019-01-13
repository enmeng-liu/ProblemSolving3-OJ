#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 1000010
using namespace std;

int f[N]={};
int n,m,k,i;
struct bug{
	int u,v,c;
}e[2*N]={};
bool cmp(bug a, bug b){
	return (a.c < b.c || (a.c == b.c && a.u < b.u));
}

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


int main(){
		scanf("%d%d%d",&n,&k,&m);
		for(i = 1; i <= n; ++i) f[i] = i;
		int chooseedge = 0;
		for(i = 1; i <= k; ++i){
			int u,v;
			scanf("%d%d",&u,&v);
			int fu = find(u);
			int fv = find(v);
			if(fu != fv){
				f[fv] = fu;
				chooseedge ++;
			}
		}
		
		int edgenum = 0;
		for(i = 1; i <= m; ++i){
			int u,v,c;
			scanf("%d%d%d", &u,&v,&c);
			if(find(u) != find(v)){
				edgenum ++;
				e[edgenum].u = u;
				e[edgenum].v = v;
				e[edgenum].c = c;
			}
			
		}
		
		sort(e+1,e+edgenum+1,cmp);
		
		long long ans = 0;
		int cnt = 0;
		for(i = 1; i <= edgenum; ++i){
			int fu = find(e[i].u);
			int fv = find(e[i].v);
			if(fu != fv){
				f[fv] = fu;
				ans += e[i].c;
				cnt ++;
				if(chooseedge + cnt == n-1) break; 
			}
		}
		printf("%d %d\n",n-chooseedge,ans);
		
return 0;
}

