#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
//����Ϊ����ѡ�����������������串������ 

struct enemy{
    int l;
    int r;
}a[100010]={};

bool cmp(enemy a, enemy b){
	return (a.r < b.r || (a.r == b.r && a.l > b.l));
}//���Ҷ˵����������Ҷ˵���ͬʱ��˵�����ǰ 

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
				//��˵��ȥ�ˣ���Ҫ����һ��ѡ�� 
			}
		}
		//cout <<"��������� "<< ans <<endl; 
		if( e >= 0) cout <<"Good Ending\n";
		else cout << "Bad Ending\n";
    } 
return 0;
}

