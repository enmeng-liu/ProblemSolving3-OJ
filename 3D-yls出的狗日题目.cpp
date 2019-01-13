#include<iostream>
#include<cstdio>
#include<map>
#include<string>
#include<cstring>
#define N 200020
using namespace std;

int T,n,K,lie;
map <string, int> a;
int f[N]={}, rel[N]={};
//bool wake[N]={};
bool mention[N]={};

void makenew(string name, bool waking){
	int x = a[name];
	if(x == 0 || waking) {
		n ++;
		a[name] = n;
		f[n] = n;
		rel[n] = 0;
		//wake[n] = 0;
		mention[n] = 0;
		//if(waking) wake[n] = 1;
	}
	else return;
}

int find(int x){
	if(f[x] == x) return x;
	int temp = f[x];
	f[x] = find(temp);
	rel[x] = (rel[x] + rel[temp]) % 3;
	return f[x];
}

void unite(int d, int x, int y){
	int fx = find(x);
	int fy = find(y);
	if(fx != fy){
		f[fy] = fx;
		rel[fy] = (3 + d + rel[x] - rel[y]) % 3;
	}
}

bool judge(int d, int x, int y){
	if(d == 0) return (rel[x] == rel[y]);
	if(d == 1) return ((3 - rel[x] + rel[y]) % 3 == d); 
}

void solve0(){
	string name1, name2;
	cin >> name1 >> name2;
	if(name1 == name2){
		return;
	}
	makenew(name1,false);
	makenew(name2,false);
	int x = a[name1];
	int y = a[name2];
	int fx = find(x);
	int fy = find(y);
	
	if(fx == fy){
		if(!judge(0,x,y)) {
			lie ++;
			//cout<<"Contradict:"<<"0"<<" "<<name1<<" "<<name2<<endl;
		}
		else {
			mention[x] = mention[y] = 1;
			//wake[x] = wake[y] = 0;
		}
	}
	else {
		unite(0,x,y);
		mention[x] = mention[y] = 1;
		//wake[x] = wake[y] = 0;
	}
}

void solve1(){
	string name1,name2;
	cin >> name1 >> name2;
	if(name1 == name2){
		lie ++;
		//cout<<"Äã ±É ÊÓ Äã ×Ô ¼º:"<<"1"<<" "<<name1<<" "<<name2<<endl;
		return;
	}
	makenew(name1,false);
	makenew(name2,false);
	int x = a[name1];
	int y = a[name2];
	int fx = find(x);
	int fy = find(y);
	
	if(fx == fy){
		if(!judge(1,x,y)) {
			lie ++;
			//cout<<"Contradict:"<<"1 "<<name1<<" "<<name2<<endl;
		}
		else {
			mention[x] = mention[y] = 1;
			//wake[x] = wake[y] = 0;
		}
	}
	else {
		unite(1,x,y);
		mention[x] = mention[y] = 1;
		//wake[x] = wake[y] = 0;
	}
}

void solve2(){
	string name;
	cin >> name;
	makenew(name,false);
	int x = a[name];
	if(!mention[x]) {
		lie ++;
		//cout<<"Wake up again: 2"<< name <<endl;
	}
	else {
			//wake[x] = 1;
			makenew(name,true);
			mention[x] = 0;
			
		}
}

void solve3(){
	string name;
	cin >> name;
	makenew(name,false);
	int x = a[name];
	if(mention[x]) {
		lie ++;
		//cout<<"Not foxi: 3 "<<name<<endl;
		//cout<<name<<": "<<a[name]<<" "<<wake[x]<<" "<<mention[x]<<endl;
	}
}

int main(){
	cin >> T;
	while(T--){
		cin >> K;
		
		n = 0;
		lie = 0;
		a.clear();
		memset(mention,0,sizeof(mention));
		//memset(wake,0,sizeof(wake));
		
		int d;
		for(int i = 0; i < K; ++i){
			cin >> d;
			switch(d){
				case 0: solve0(); break;
				case 1: solve1(); break;
				case 2: solve2(); break; 
				case 3: solve3(); break;
			} 
		}
		printf("%d\n",lie);
		//cout <<"----------------------------\n";
	}



return 0;
}

