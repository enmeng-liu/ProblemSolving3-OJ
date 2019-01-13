#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int f[200020]={};
int t,n,m,i;

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

void diff(int a, int b){
	int fa = find(a), fan = find(a + n);
	int fb = find(b), fbn = find(b + n);
	if(fa != fbn) {
		f[fa] = fbn;
		f[fb] = fan;
	}
	//cout<<a<<" and "<<b<<"are in different gangs.\n";
}

void answer(int a, int b){
	if(find(a) != find(b) && find(a) != find(b+n))
		printf("Not sure yet.\n");
	else if(find(a) == find(b))
			printf("In the same gang.\n");
		else printf("In different gangs.\n");
}


int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(i = 1; i <= 2*n; ++i) f[i] = i;
		char c;
		int a,b;
		for(i = 1; i <= m; ++i){
			//scanf("%c %d %d",&c,&a,&b);
			cin >> c >> a >> b;
			if(c == 'D') diff(a,b);
			else if(c == 'A') answer(a,b);
		}
	}

return 0;
}

