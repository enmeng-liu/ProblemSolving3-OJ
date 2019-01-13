//
// Created by 91342 on 2019/1/7.
//
#include <queue>

int find(int i) {
    return f[i] == i ? i : f[i] = find(f[i]);
}

int find(int x) {
    int root = f[x];
    while (root != f[root]) root = f[root];
    int y = f[x];
    while (x != root) {
        y = f[x];
        f[x] = root;
        x = y;
    }
    return root;
}

void unite(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    if (fa != fb) {
        if (rank[a] < rank[b]) f[a] = fb;
        else f[b] = fa;
    }
}

int kruskal() {
    sort(edge, edge + m, cmp);//将边按权重从小到大排序
    int cnt = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) f[i] = i;//初始化并查集
    for (int i = 0; i < m; ++i) {
        int a = edge[i].u;
        int b = edge[i].v;
        int fa = find(a), fb = find(b);
        if (fa != fb) {
            f[fa] = fb;
            ans += edge[i].w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    return ans;
}

struct Node {
    int id;
    int key;

    bool operator<(const Node &b) {
        return (key < b.key) || (key == b.key && id < b.id);
    }
} ver[N] = {};

int prim() {
    priority_queue <Node> q;
    ver[0].key = 0;
    q.push(ver[0]);
    vis[0] = true;
    int ans = 0;
    while (!q.empty()) {
        Node u = q.top();
        q.pop();
        if (uid != 0) ans += map[uid][pre[uid]];
        vis[uid] = true;
        int uid = u.id;
        for (i = 0; i < son[uid].size(); ++i) {
            int v = son[uid][i];
            if (!vis[v] && map[u][v] < ver[v].key) {
                ver[v].key = map[u][v];
                pre[v] = uid;
                q.push(ver[v]);
            }
        }
    }
}

void dijkstra() {
    prority_queue <node> q;
    ver[0].d = 0;
    q.push(ver[0]);

    while (!q.empty()) {
        node u = q.top();
        q.pop();
        for (int i = 0; i < son[u].size(); ++i) {
            int vid = son[u.id][i];
            if (ver[vid].d < u.d) continue;
            if (ver[vid].d > u.d + map[u.id][vid]) {
                ver[vid].d = u.d + map[u.id][vid];
                q.push(ver[vid]);
            }
        }
    }
}

void bellman_ford() {
    dist[s] = 0;
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dist[e[j].u < INF && dist[e[j].v] > dist[e[j].u] + e[j].w) {
                dist[e[j].v] = dist[e[j].u] + e[j].w;
                pre[e[j].v] = e[j].u;
            }
        }
    }
    for (int j = 1; j <= m; ++j)
        if (dist[e[j].v] > dist[e[j].u] + e[j].w) flag = false;
}

void floyd() {
    init(); //记得将所有map[i][i]置零
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
}

int prim() {
    for (int i = 0; i < V; i++) {
        mincost[i] = INF;
        used[i] = false;
    }
    mincost[0] = 0;
    int res = 0;
    while (true) {
        int v = -1;
        for (int u = 0; u < V; u++) {
            if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
        }
        if (v == -1) break;
        used[v] = true;
        res += mincost[v];
        for (int u = 0; u < V; u++) {
            mincost[u] = min(mincost[u], cost[v][u]);
        }
    }
    return res;
}

int my_prim() {
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        mincost[i] = INF;
        vis[i] = false;
    }
    while(true){
        int v = -1;
        for(int i = 0; i < n; ++i) {
            if(!vis[i] && (v == -1 || mincost[i] < mincost[v])) v = i;
        }
        if(v == -1) break;
        vis[v] = true;
        ans += mincost[v];
        for(int i = 0; i < n; ++i) {
            mincost[i] = min(mincost[i], map[v][i]);
        }
    }
    return ans;
}

/*无向图tarjan*/
void tarjan(int u, int pre) {
    int child = 0;
    dfs_clock ++;
    dfn[u] = low[u] = dfs_clock;
    for(int i = 0; i < son[u].size(); ++i) {
        int v = son[u][i];
        if(!dfn[v]) {//(u,v)是树边
            tarjan(v,u);
            child ++;
            low[u] = min(low[u], low[v]);
            if((u == 1 && child > 1) || (u != 1 && dfn[u] <= low[v])) {
                cut_node.push_back(u);
            }//割点判定：根结点有多个子树，或非根结点的访问序数小于等于能回溯的最大祖先
            if(low[v] > dfn[u]) bridge.push_back({min(u,v), max(u,v)});
        }
        else if(dfn[v] < dfn[u] && v !=  pre) low[u] = min(low[u], dfn[v]);
    }
}

bool find(int x) {
    for(int i = 1; i <= n; ++i) {
        if(map[x][i] && !vis[i]) {
            vis[i] = true;
            if(match[i] == 0 || find(match[i])) {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int hungary() {
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        memset(vis, 0 ,sizeof(vis));
        if(find(i)) ans ++;
    }
    return ans;
}