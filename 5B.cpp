//
// Created by 91342 on 2018/11/6.
//

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <cstdio>
#include <assert.h>
#include <cmath>
using namespace std;

struct status{
    int x,y; //坐标
    int len; //路径长度
    int clg; //挑战情况
    int jie; //杰哥情况
};
int visit[110][110][15][1 << 6];

int n,m;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int map[110][110] ={};
int jiege[110][110] = {};

const int JIE = 100;
const int WALL = 200;
const int DEST = 300;


queue <status> q;

int bfs(status start){
    int minlen = 1e9;
    q.push(start);
    while(!q.empty()){
        status s0 = q.front();
        //assert(s0.x < 110 && s0.y < 100 && s0.clg < 10 && s0.jie < 6);
        visit[s0.x][s0.y][s0.clg][s0.jie] = 1;

        //printf("Extract (%d,%d), clg=%d, jie=%d\n",s0.x,s0.y,s0.clg,s0.jie);
        for(int k = 0; k < 4; ++k){
            status next;
            int x = s0.x + dx[k];
            int y = s0.y + dy[k];
            next.x = x;
            next.y = y;
            next.len = s0.len + 1;
            next.clg = s0.clg;
            next.jie = s0.jie;

            if(x < 0 || x >= n || y < 0 || y >= n) continue;

            //printf("Now bfs (%d,%d) %d,clg=%d, jie=%d\n",x,y,map[x][y],next.clg,next.jie);
            if(map[x][y] == s0.clg + 1){
                next.clg = s0.clg + 1;
                //printf("Pass clg %d\n",next.clg);
            }
            //如果这个点有下一个需需要进行的挑战

            if(map[x][y] == JIE){
                //printf("Meet jiege %d & %d = %d\n", s0.jie, 1<<jiege[x][y],s0.jie & (1<<jiege[x][y]));
                if(!(s0.jie & (1 << jiege[x][y]))){
                    next.len += 1;
                    next.jie |= 1 << jiege[x][y];
                    //printf("Please not JIEGE! %d\n",next.jie);
                }
               // else next.jie = s0.jie;
            }
            //如果这个点有杰哥，并且没有被访问过

            if(x >= 0 && x < n && y >= 0 && y < n && map[x][y] != WALL && !visit[x][y][next.clg][next.jie]){
                //assert(x<110 && y<110 && next.clg<10 && next.jie<6);
                //assert(next.clg < 15);
                //assert(next.jie < 6);
                if(map[x][y] == DEST && next.clg == m) minlen = min(minlen, next.len);
                visit[x][y][next.clg][next.jie] = 1;
                q.push(next);
            }


        }
        q.pop();
    }
    return minlen;
}




int main(){
    int sx,sy,dx,dy;
    int jiegesum;

    while(1){
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        q = queue<status>();
        memset(visit,0, sizeof(visit));
        memset(jiege,0, sizeof(jiege));
        memset(map,0, sizeof(map));
        jiegesum = 0;
        //clgsum = 0;

        for(int i = 0; i < n; ++i){
            string s;
            cin >> s;
            for(int j = 0; j < n; ++j){
                switch (s[j]){
                    case 'S':
                        map[i][j] = 0;
                        sx = i;
                        sy = j;
                        break;
                    case 'D':
                        map[i][j] = DEST;
                        dx = i;
                        dy = j;
                        break;
                    case 'J':
                        jiege[i][j] = jiegesum;
                        jiegesum ++;
                        map[i][j] = JIE;
                        break;
                    case '.':
                        map[i][j] = 0;
                        break;
                    case '@':
                        map[i][j] = WALL;
                        break;
                    default:
                        if(isdigit(s[j])) map[i][j] = s[j] - '0';
                }
            }
        }

        status start;
        start.x = sx;
        start.y = sy;
        start.len = 0;
        start.clg = 0;
        start.jie = 0;
        int ans = bfs(start);
        //int yong = 2 * (1<<jiegesum) - 1;
        if(ans > 100000) printf("gg\n");
        else printf("%d\n",ans);

    }
    return 0;
}