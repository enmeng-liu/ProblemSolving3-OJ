//
// Created by 91342 on 2018/11/13.
//

#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;

const double INF = 1e9;

struct node{
    int id;
    double x;
    double y;
    double d;
    friend bool operator < (const node&a , const node&b) {
        return a.d > b.d;
    }
}vertex[90]={};

struct Wall{
    double x;
    double a1, b1, a2, b2;
}wall[25] = {};

int n;
int sum = 0;
//int p[90] = {};


vector <int> son[90];
vector <double> w[90];



double dist(node a, node b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) *(a.y - b.y));
}

double cross(node a, node b, double x){ //计算交点坐标
    double dx = (b.x - a.x);
    double dy = b.y - a.y;
    double m = b.x * a.y - a.x * b.y;
    double temp = dy * x + m;
    return temp / dx;
}


double dijkstra(){
    priority_queue <node> q;
    vertex[0].d = 0.0;
    q.push(vertex[0]);

    while(!q.empty()){
        node u = q.top();
        q.pop();
        if(u.id == sum) return u.d;

        for(int i = 0; i < son[u.id].size(); ++i){
            int vid = son[u.id][i];
            double weight = w[u.id][i];
            if(vertex[vid].d < u.d) continue;
            if(vertex[vid].d > u.d + weight){
                vertex[vid].d = u.d + weight;
                //p[vid] = u.id;
                //if(vid == sum) return vertex[sum].d;
                q.push(vertex[vid]);
            }
        }
    }

}

int main(){
    cin >> n;
    vertex[0] = {0, 0, 5, INF};
    for(int i = 1; i <= n; ++i){
        double x;
        double a1,b1,a2,b2;
        cin >> x;
        cin >> a1 >> b1 >> a2 >> b2;
        wall[i] = {x,a1,b1,a2,b2};
        sum ++;
        vertex[sum] = {sum,x,a1,INF};
        sum ++;
        vertex[sum] = {sum,x,b1,INF};
        sum ++;
        vertex[sum] = {sum,x,a2,INF};
        sum ++;
        vertex[sum] = {sum,x,b2,INF};
    }
    sum++;
    vertex[sum] = {sum, 10, 5, INF};

    for(int i = 0; i < sum; ++i){
        for(int j = i + 1; j <= sum; ++j){
            double x1 = vertex[i].x, x2 = vertex[j].x;
            if(x2 <= x1) continue;
            bool ok = true;

            for(int k = 1; k <= n; ++k){
                if(wall[k].x <= x1) continue;
                if(wall[k].x >= x2) break;
                double yy = cross(vertex[i],vertex[j],wall[k].x);
                if(!( (yy >= wall[k].a1 && yy <= wall[k].b1) || (yy >= wall[k].a2 && yy <= wall[k].b2) )){
                    ok = false;
                    break;
                }
            }

            if(ok == true) {
                son[i].push_back(j);
                w[i].push_back(dist(vertex[i],vertex[j]));
                //printf("(%d,%.2f)->(%d,%.2f) %.2f\n",x1,y1,x2,y2,dist(vertex[i],vertex[j]));
            }//建边
        }
    }

    printf("%.2f\n",dijkstra());

    /*int temp = sum;
    while(temp != 0) {
        printf("(%d,%.2f) %.2f\n",vertex[temp].x, vertex[temp].y,vertex[temp].d);
        temp = p[temp];
    }*/
    //printf("(%d,%.2f)\n",vertex[0].x, vertex[0].y);
    return 0;
}