#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;

struct day{
	int index;
	int a;
	int b;
	bool operator < (const day &dd) const {
		return (b < dd.b||(b == dd.b && a > dd.a));
	}
}d[20010]={};

int main(){
	int n,T,i;
	long long happy;
	scanf("%d", &T);
	while(T--){
		scanf("%d%lld", &n, &happy);
		for( i = 1; i <= n; ++i)
			scanf("%d", &d[i].a);
		for( i = 1; i <= n; ++i)
			scanf("%d", &d[i].b);
		priority_queue <day> q;
		
		int studyday = 0, flag = 1;
		for(i = 1; i <= n; ++i){
			happy += d[i].a;
			happy -= d[i].b; 
			studyday ++;
			q.push(d[i]);
			//贪心：先学习再说 
			while(happy <= 0){
				//cout << "On the "<< i <<"th day unhappy;\n";
				if(q.empty()){
					flag = 0;
					break;
				}
				else{
					happy += q.top().b;
					//cout << "pop" << q.top().b<<endl;
					studyday --;
					q.pop();
				}
			}
			if(flag == 0 || happy <= 0) break;
		}
			if(flag == 0 || happy <= 0) {
				cout << "Bob will be unhappy!\n";
			}
			else {
				cout << studyday << " " << happy <<endl;
			}
			
		 
	}


return 0;
}

