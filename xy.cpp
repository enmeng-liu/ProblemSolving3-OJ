//
// Created by 91342 on 2018/12/4.
//

#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
int huan[405] = {}, final = 0, cnt = 0, n, m, num_of_deg_1 = 0, start = 1, deg[405] = {}, a[10005], b[10005];
bool vis2[10005] = {}, vis[405] = {}, if_Hamiltonian = false, if_Eulerian = true;
vector <int> adj[405];

void dfs(int u) {
    if(if_Hamiltonian)
        return;
    if(cnt == n) {
        if_Hamiltonian = true;
        start = u;
        return;
    }
    for (int i = 0; i < adj[u].size(); ++i) {
        int v;
        if(u == a[adj[u][i]])
            v = b[adj[u][i]];
        else
            v = a[adj[u][i]];
        if(!vis[v]) {
            vis[v] = true;
            cnt ++;
            dfs(v);
            cnt --;
            vis[v] = false;
        }
    }
}
void dfs2(int u) {
    for (int i = 0; i < adj[u].size(); ++i) {
        int e = adj[u][i];//边的编号
        for (int i = 0; i < huan[u]; ++i) {
            printf("%d %d\n", u, u);
        }
        huan[u] = 0;
        //printf("edge %d: %d to %d\n", e, a[e], b[e]);
        if(!vis2[e] && a[e] != b[e]) {
            int v;
            if(u == a[e])
                v = b[e];
            else
                v = a[e];
            vis2[e] = true;
            printf("%d %d\n", u, v);
            final = v;
            dfs2(v);
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    int num_of_edge = m;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &a[i], &b[i]);
        adj[a[i]].push_back(i);
        if(a[i] != b[i]) {
            adj[b[i]].push_back(i);
            deg[a[i]] ++;
            deg[b[i]] ++;
        }
        else {
            num_of_edge--;
            huan[a[i]]++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if(deg[i] % 2)
            if_Eulerian = false;
        if(adj[i].size() == 1) {
            num_of_deg_1++;
            start = i;
        }
    }
    if(num_of_deg_1 > 2) {
        printf("Miss Shizue\n");
        return 0;
    }
    if(num_of_edge != n * (n - 1) / 2) {
        vis[start] = true;
        cnt ++;
        dfs(start);
        if(!if_Hamiltonian) {
            printf("Miss Shizue\n");
            return 0;
        }
    }
    if(if_Eulerian) {
        printf("Find Leon\n");
        //for(int i = 1;i <= n; i++)
        //   sort(adj[i].begin(), adj[i].end());
        //vis2[adj[start][0]] = true;
        dfs2(start);
        //if(start != final)
        //   printf("%d %d\n", final, start);
    }
    else
        printf("Miss Leon\n");
    return 0;
}