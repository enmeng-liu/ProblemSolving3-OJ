#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 10010
#define M 2010
using namespace std;

int pos[M] = {};
int tree[M] = {}; 
int pre[N] = {};

struct node{
	int x,y;
	int id;
	int xsy;
}point[N] = {}, P[N] = {};
bool cmp(node a, node b){
	return (a.x >b.x || a.x == b.x && a.y > b.y);
}
int cmpxsy(node a, node b){
	return a.xsy < b.xsy;
}

struct edge{
	int u,v;
	int w;
	edge(int uu = 0, int vv = 0, int ww = 0){
		u = uu;
		v = vv;
		w = ww;
	}
};
bool edgecmp(edge a, edge b){
	return (a.w < b.w || a.w == b.w && a.u < b.u);
} 
vector<edge> e;

int find(int x){
	int root = pre[x];
	while(root != pre[root]) root = pre[root];
	int y = pre[x];
	while(pre[x] != root){
		pre[x] = pre[y];
		y = pre[y];
	}
	return pre[x];
}


void add(int p, int val, int id){
	while(p < M){
		if(val < tree[p]){
			tree[p] = val;
			pos[p] = id;
		}
	}
	p += p & (-p);
}

int query(int p){
	int id = -1;
	int val = 1e9;
	while(p > 0){
		if(tree[p] < val){
			val = tree[p];
			id = pos[p];
		}
		p -= p & (-p);
	}
	return id;
}



int dist(node a, node b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void manhaton(int n){
	for(int i = 0; i < n; ++i){
		point[i].xsy = point[i].x - point[i].y;
	}
	sort(point, point + n, cmpxsy);
	
	int cnt = 1;
	int f = -1e9;
	for(int i = 0; i < n; ++i){
		if(point[i].xsy != f){
			cnt ++;
			f = point[i].xsy;
		}
		point[i].xsy = cnt;
	}
	sort(point,point + n, cmp);
	
	for(int i = 0; i < M; ++i){
		tree[i] = 1e9;
		pos[i] = -1;
	}
	for(int i = 0; i < n; ++i){
		int u = point[i].id;
		int v = query(point[i].xsy);
		if(v != -1){
			e.push_back(edge(u,v,dist(P[u],P[v])));
		}
		add(point[i].xsy, point[i].x + point[i].y, u);
	}
}

void build(int n){
	e.clear();
	for(int j = 0; j < 4; ++j){
		for(int i = 0; i < n; ++i){
			point[i] = P[i];
		}
		for(int i = 0; i < n; ++i){
			if(j == 1) swap(point[i].x, point[i].y);
			else if(j == 2) point[i].y = - point[i].y;
				 else if(j == 3){
				 	swap(point[i].x, point[i].y);
				 	point[i].y = -point[i].y;
				 }
		}
		manhaton(n);
	}	
}

int kruskal(int n, int k){
	for(int i = 0; i < n; ++i) pre[i] = i;
	sort(e.begin(), e.end(), edgecmp);
	
	int ans = 0, cnt =0;
	for(int i = 0; i < e.size(); ++i){
		if(cnt == k) return ans;
		ans = e[i].w;
		int fu = find(e[i].u);
		int fv = find(e[i].v);
		if(fu != fv) {
			pre[fu] = fv;
			cnt ++;
		}
	}
	return ans;
}


int main(){
	int n,k;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i){
		int a,b;
		scanf("%d%d", &a, &b);
		P[i].x = a;
		P[i].y = b;
		P[i].id = i;
	}
	build(n);
	printf("%d\n", kruskal(n,k));

return 0;
}

