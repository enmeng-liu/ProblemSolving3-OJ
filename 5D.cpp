//
// Created by 91342 on 2018/11/6.
//

#include <iostream>
#include <cstdio>
using namespace std;

int a[110] = {};
int b[110] = {};
int ra[110] = {};
int rb[110] = {};
int n;

struct node{
    //int val;
    int left = -1;
    int right = -1;
    int depth;
}e[110] = {};

int findroot(int l, int r){
    if(l == r) return b[l];
    int min_aid = 200;
    int bid;
    for(int i = l; i <= r; ++i){
        if(ra[b[i]] < min_aid) {
            min_aid = ra[b[i]];
            bid = i;
        }//find the root according to the index in a
    }
    int root = a[min_aid];
    //printf("Now find root from %d to %d and the root is %d\n",l,r,root);
    if(bid - 1 >= l) e[root].left = findroot(l,bid-1);
    if(bid + 1 <= r) e[root].right = findroot(bid+1,r);
    return root;
}

void bfs(int root){
    int q[110] = {};
    int h = 0, t = 0;
    q[0] = root;
    e[root].depth = 0;
    int lastdepth = 0;
    cout << root;

    while(h <= t){
        int u = q[h];
        if(e[u].left >= 0) {
            q[++t] = e[u].left;
            e[e[u].left].depth = e[u].depth + 1;
        }
        if(e[u].right >= 0) {
            q[++t] = e[u].right;
            e[e[u].right].depth = e[u].depth + 1;
        }

        if(u != root) {
            if (e[u].depth == lastdepth) cout << " ";
            else {
                cout << endl;
                lastdepth = e[u].depth;
            }
            cout << u;
        }
        h ++;
    }
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        ra[a[i]] = i;
    }
    for(int i = 1; i <= n; ++i){
        cin >> b[i];
        rb[b[i]] = i;
    }

    //for(int i = 1; i <= n; ++i) e[i].val = i;

    int root = findroot(1,n);
    bfs(root);

    return 0;
}
