#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
//该题为区间选点问题而非最大子区间覆盖问题 

struct enemy{
    int l;
    int r;
}a[100010]={};

bool cmp(enemy a, enemy b){
	return (a.r < b.r || (a.r == b.r && a.l > b.l));
}//按右端点升序排序，右端点相同时左端点大的在前 

int main(){
	int T,n,e,c,i,j;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n,&e,&c);
		for( i = 1; i <= n; ++i){
			scanf("%d%d",&a[i].l,&a[i].r);
			a[i].r --;
		}
		sort(a+1, a+n+1, cmp);
		//for(i = 1; i <= n; ++i)
			//cout << a[i].l << " " << a[i].r <<endl;
		
		
		int ans = 0;
		int right = a[1].r;
		e -= c;
		for(i = 1; i <= n; ++i){
			if(a[i].l > right){
				e -= c;
				right = a[i].r;
				//cout << "add point: " << right <<endl;
				//左端点出去了，就要增加一个选点 
			}
		}
		//cout <<"发射次数： "<< ans <<endl; 
		if( e >= 0) cout <<"Good Ending\n";
		else cout << "Bad Ending\n";
    } 
return 0;
}

