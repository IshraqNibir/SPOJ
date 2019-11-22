#include <bits/stdc++.h>
#define mx 100002
#define pb push_back
#define mkp make_pair
using namespace std;
//LCA using sparse table
//Complexity: O(NlgN,lgN)
int L[mx]; //Label
int ST[mx][33],ST_MX[mx][33],ST_MN[mx][33]; //Sparse Table
int P[mx]; //Parent
int dis[mx];
vector <int> g[mx];
vector <int> cost[mx];
int ret = -1,ret1 = 1000000000;

int find_par(int u)
{
    return P[u]=(P[u]==u)?u:find_par(P[u]);
}

void dfs (int u, int par, int label) {
    L[u] = label;
    P[u] = par;
    int sz = g[u].size();
    for (int i = 0; i < sz; i++) {
        int v = g[u][i];
        if (L[v] == -1) {
            dis[v] = cost[u][i];
            dfs (v, u, label+1);
        }
    }
}

void lca_init (int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 33; j++)
            ST[i][j] = -1;
    }
    for (int j = 1; j <= n; j++) {
        ST[j][0] = P[j]; //2^0 th parent
        ST_MX[j][0] = dis[j];
        ST_MN[j][0] = dis[j];
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (ST[i][j-1] != -1) {
                 ST[i][j] = ST[ ST[i][j-1] ][j-1];
                 ST_MX[i][j] = max (ST_MX[i][j-1], ST_MX[ST[i][j-1]][j-1]);
                 ST_MN[i][j] = min (ST_MN[i][j-1], ST_MN[ST[i][j-1]][j-1]);
            }
        }
    }
}

void find_lca (int u, int v) {
    if (L[u] < L[v]) swap (u, v);
    for (int i = 30; i >= 0; i--) {
        if (L[u] - (1 << i) >= L[v]) { //L[v] means in what label should go
            ret = max (ret, ST_MX[u][i]);
            ret1 = min (ret1, ST_MN[u][i]);
            u = ST[u][i];
        }
    }

    if (u == v) return;

    for (int i = 30; i >= 0; i--) {
        if (ST[u][i] != -1 && ST[u][i] != ST[v][i]) {
            ret = max (ret, max (ST_MX[u][i], ST_MX[v][i]));
            ret1 = min (ret1, min (ST_MN[u][i], ST_MN[v][i]));
            u = ST[u][i]; v = ST[v][i];
        }
    }

    ret = max (ret, max (dis[u], dis[v]));
    ret1 = min (ret1, min (dis[u], dis[v]));
    return;
}

int main()
{
    int t, ks = 1;
    int n, e, u, v, w, q;
    scanf ("%d", &n);
    vector< pair<int, pair<int,int> > >g1;
    for (int i = 1; i < n; i++) {
        scanf ("%d %d %d", &u, &v, &w);
        g1.pb(mkp(w, mkp(u,v)));
    }
    sort(g1.begin(),g1.end());

    for (int i=1; i<=n; i++)
        P[i] = i;

    int cnt = 0;
    for(int i=0; i<g1.size() && cnt<n-1; i++) {
        int a = g1[i].second.first;
        int b = g1[i].second.second;
        int c = g1[i].first;
        int u1 = find_par(a);
        int v1 = find_par(b);
        if(u1 != v1)
        {
            P[v1] = u1;
            g[a].pb(b);
            g[b].pb(a);
            cost[a].pb(g1[i].first);
            cost[b].pb(g1[i].first);
            cnt++;
        }
    }
    memset (P, -1, sizeof (P));
    memset (L, -1, sizeof (L));
    dis[1] = 0;
    dfs (1, 1, 0); //node starting from 1
    lca_init(n);
    scanf ("%d", &q); //query
    //printf ("Case %d:\n", ks++);
    while (q--) {
        scanf (" %d %d", &u, &v);
        ret = -1;
        ret1 = 1000000000;
        find_lca (u,v);
        printf ("%d %d\n", ret1, ret);
    }
    for(int i=0;i<mx;i++) {
        g[i].clear();
        cost[i].clear();
    }
    return 0;
}

