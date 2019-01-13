#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue> 
using namespace std;


int main(){
	int n,i;
	while(scanf("%d", &n) == 1){
		priority_queue<long long, vector<long long>, greater<long long> > q;
		//��С���ȶ�������
		for(i = 1; i <= n; ++i){
			int x;
			scanf("%d", &x);
			q.push(x);
		}
		
		long long ans = 0;
		while(q.size() > 1){
			if(q.size()%2 == 0){
				q.push(0); 
			}
			long long temp = 0;
			for( i = 1; i <= 3; ++i){
				temp += q.top();
				q.pop();
			}//����С������Ԫ��ȡ�������ϲ�
			ans += temp; 
			//cout <<"----------\n" << temp << endl; 
			q.push(temp);
		}
		cout << ans << endl;
	}
return 0;
}

