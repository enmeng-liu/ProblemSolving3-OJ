#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

struct city{
	int a;
	int b;
}c[100010]={}; 

bool cmp(city x, city y){
	return (min(x.b,y.a) > min(x.a,y.b) || (min(x.b,y.a) == min(y.b,x.a) && x.a < y.a));
}

int main(){
	int T,n,i,j;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(i = 1; i <= n; ++i){
			scanf("%d%d", &c[i].a, &c[i].b);
		}
		
		sort(c+1, c+n+1, cmp);
		//for(i = 1; i <= n; ++i)
			//cout << c[i].a <<" " << c[i].b <<endl;
		long long ans = 0, money = 0;
		for(i = 2; i <= n; ++i){
			money += c[i-1].b;
			if(money <= c[i].a) {
				ans += money;
				money = 0;
			}
			else {
				ans += c[i].a;
				money -= c[i].a;
			}
		}
		cout << ans << endl;
	}


return 0;
}

