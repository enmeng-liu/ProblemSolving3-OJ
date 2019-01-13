#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector> 
#include<cstring>
using namespace std;

int T,n,m;
int w[25][25] = {};
int f[25] = {}; 
bool visited[25] = {};
vector<int> tree[25];
 
struct edge{
	int u,v;
	int weight;
	bool used;
}e[200]={};
bool cmp(edge a, edge b){
	return (a.weight < b.weight || (a.weight == b.weight && a.u < b.u));
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

int kruskal(){
	int ans = 0, cnt = 0;
	for(int i = 1; i <= n; ++i) f[i] = i;
	sort(e,e+m,cmp);
	for(int i = 0; i < m; ++i){
		int fu = find(e[i].u);
		int fv = find(e[i].v);
		if(fu != fv){
			e[i].used = 1;
			f[fv] = fu;
			ans += e[i].weight;
			tree[e[i].u].push_back(e[i].v);
			tree[e[i].v].push_back(e[i].u);
			cnt ++;
			if(cnt == n - 1) break;
		} 
	}
	return ans;
}

int dfsmax(int u, int v, int maxw){
	if(u == v) return maxw;
	visited[u] = 1;
	//cout << "Now search node" << u <<endl; 
	for(int i = 0; i < tree[u].size(); ++i){
		//cout<< tree[u][i] <<" "<<w[u][tree[u][i]]<<endl;
		if(!visited[tree[u][i]])
			return dfsmax(tree[u][i],v,max(maxw,w[u][tree[u][i]]));
	}
} //找到u-v路径中的最大权重
 

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i) e[i].used = 0;
		for(int i = 0; i < m; ++i){
			int x,y,cost;
			scanf("%d%d%d", &x,&y,&cost);
			e[i].u = min(x,y);
			e[i].v = max(x,y);
			e[i].weight = cost;
			w[x][y] = w[y][x] = cost;
		}
		for(int i = 1; i <= n; ++i) tree[i].clear();
		
		int mst = kruskal();
		bool ok = true;
		
		for(int i = 0; i < m; ++i){
			//枚举每一条未选择的边e 
			if(!e[i].used){
				memset(visited,0,sizeof(visited));
				int maxw = dfsmax(e[i].u,e[i].v,0);
				//找到T+e的cycle中最长的一条边
				//cout<<"the unused edge: "<<e[i].u<<" "<<e[i].v<<" "<<e[i].weight<<endl; 
				//cout<<"dfsmaxw: "<<maxw<<endl;
				if(e[i].weight <= maxw) {
					ok = false;
					break;
				}
			}
		}
		
		if(ok) printf("%d\n", mst);
		else printf("Peter can find other ways\n"); 
	}



return 0;
}

