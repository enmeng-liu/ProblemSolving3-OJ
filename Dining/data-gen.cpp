#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define MAX 100
//#define HALF_MAX 50

bool fused[MAX] = {};
bool dused[MAX] = {};
vector <int> food[MAX];
vector <int> drink[MAX];
int F, D ,n ,N;
int fx[MAX] = {}, dx[MAX] = {};

void allocate(int x){
	int f = 0, d = 0;
	while(fused[f]) f = rand() % F + 1;
	while(dused[d]) d = rand() % D + 1;
	food[x].push_back(f);
	drink[x].push_back(d);
	fused[f] = true;
	dused[d] = true;
	fx[x] = f;
	dx[x] = d;
	//printf("%d: %d %d\n",x, f, d);
}

void add_more(int x){
	int fn = rand() % F;
	int dn = rand() % D;
	bool used[MAX] = {};
	used[fx[x]] = true;
	for(int i = 1; i <= fn; ++i) {
		int f = fx[x];
		while(used[f]) f = rand() % F + 1;
		used[f] = true;
		food[x].push_back(f);
	}

	memset(used, 0, sizeof(used));
	used[dx[x]] = true;
	for(int i = 1; i <= dn; ++i){
		int d =dx[x];
		while(used[d]) d = rand() % D + 1;
		drink[x].push_back(d);
		used[d] = true;
	}
}

int main(){
	srand((int)time(0));
	n = rand() % MAX + 1;
	N = rand() % MAX + 1;
	if(n > N) swap(n,N);

	F = n + rand() % (MAX - n) + 1;
	D = n + rand() % (MAX - n) + 1;

	fused[0] = dused[0] = true;
	for(int i = 1; i <= n; ++i) allocate(i);
	for(int i = 1; i <= N; ++i) add_more(i);

	printf("%d %d %d\n", N, F, D);
	for(int i = 1; i <= n; ++i) {
		printf("%d %d ", food[i].size(), drink[i].size());
		for(int j = 0; j < food[i].size(); ++j) printf("%d ", food[i][j]);
		for(int j = 0; j < drink[i].size(); ++j) printf("%d ", drink[i][j]);
		printf("\n");
	}

	return 0;
}
