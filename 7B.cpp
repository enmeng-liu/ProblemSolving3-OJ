//
// Created by 91342 on 2018/11/15.
//

#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 1e9
using namespace std;

int n,m1,m2,K,T;
int d1[110][110] = {}, d2[110][110] = {};
int loca1[110] = {},loca2[110] = {};
bool cmp(int a, int b) { return a < b;}

void floyd1(){
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                d1[i][j] = min(d1[i][j],d1[i][k] + d1[k][j]);
}

void floyd(){
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                d2[i][j] = min(d2[i][j],d2[i][k] + d2[k][j]);
}


int main(){
    scanf("%d%d%d",&n,&m1,&m2);
    scanf("%d%d",&T,&K);
    for(int i = 1; i <= T; ++i){
        int x;
        scanf("%d",&x);
        loca1[i] = x;
        //第i号碎片对应的传送门在主世界的x区块位置
    }
    for(int i = 1; i <= T; ++i){
        int x;
        scanf("%d",&x);
        loca2[i] = x;
        //第i号碎片在末影世界的x区块位置
    }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j){
            if(i != j) d1[i][j] = INF;
            else d1[i][j] = 0;
        }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j){
            if(i != j) d2[i][j] = INF;
            else d2[i][j] = 0;
        }

    for(int i = 1; i <= m1; ++i){
        int u,v,x;
        scanf("%d%d%d",&u,&v,&x);
        d1[u][v] = x;
    }

    for(int i = 1; i <= m2; ++i){
        int u,v,x;
        scanf("%d%d%d",&u,&v,&x);
        d2[u][v] = x;
    }

    floyd1();
    floyd();

    //for(int i = 1; i <= T; ++i) printf("d1[%d]=%d\n",loca1[i],d1[1][i]);

    int mindist[110] = {};
    for(int i = 1; i <= T; ++i){
        mindist[i] = d1[1][loca1[i]] + d2[loca1[i]][loca2[i]];
    }

    sort(mindist + 1, mindist + T + 1,cmp);
    int ans = 0;
    for(int i = 1; i <= K; ++i){
        if(mindist[i] >= INF) {
            printf("-1\n");
            return 0;
        }
        ans += mindist[i];
    }


    //for(int i = 1; i <= T; ++i) printf("mindist[%d]=%d\n",i,mindist[i]);

    printf("%d\n",ans);
    return 0;


}