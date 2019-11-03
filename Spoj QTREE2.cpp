#include <bits/stdc++.h>
#define mx 100002
#define pb push_back
#define mkp make_pair
using namespace std;
//LCA using sparse table
//Complexity: O(NlgN,lgN)
int L[mx]; //Label
int ST[mx][33],ST_MX[mx][33]; //Sparse Table
int P[mx]; //Parent
int dis[mx];
vector <int> g[mx];
vector <int> cost[mx];
int rt;

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
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (ST[i][j-1] != -1) {
                 ST[i][j] = ST[ ST[i][j-1] ][j-1];
                 ST_MX[i][j] = (ST_MX[i][j-1] + ST_MX[ST[i][j-1]][j-1]);
            }
        }
    }
}

int find_lca (int u, int v) {
    if (L[u] < L[v]) swap (u, v);
    int ret = 0;
    for (int i = 30; i >= 0; i--) {
        if (L[u] - (1 << i) >= L[v]) { //L[v] means in what label should go
            ret += ST_MX[u][i];
            u = ST[u][i];
        }
    }

    if (u == v) {
        rt = u;
        return ret;
    }

    for (int i = 30; i >= 0; i--) {
        if (ST[u][i] != -1 && ST[u][i] != ST[v][i]) {
            ret += (ST_MX[u][i] + ST_MX[v][i]);
            u = ST[u][i]; v = ST[v][i];
        }
    }
    rt = P[u];
    ret += (dis[u] + dis[v]);
    return ret;
}

int main()
{
    int t, ks = 1;
    cin >> t;
    while (t--) {
        int n, e, u, v, w, q, kth, node;
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
        while (1) {
            string str;
            cin >> str;
            if (str == "DONE")
                break;
            else if (str == "DIST") {
                scanf ("%d %d", &u, &v);
                printf ("%d\n", find_lca(u, v));
            }
            else {
                scanf ("%d %d %d", &u, &v, &kth);
                int tmp = find_lca(u, v);
                int lv1 = L[u];
                int lv2 = L[rt];
                int lv3 = L[v];
                int pr;
                int dif = lv1-lv2+1;
                if (kth <= dif) {
                    node = u;
                    pr = lv1-kth+1;
                }
                else {
                    node = v;
                    pr = kth-dif;
                    pr = lv2+pr;

                }
                for (int i = 30; i >= 0; i--) {
                    if (L[node] - (1 << i) >= pr) { //pr means in what label should go
                        node = ST[node][i];
                    }
                }
                printf("%d\n", node);
            }
        }
        for(int i=0;i<mx;i++) {
            g[i].clear();
            cost[i].clear();
        }
    }
    return 0;
}
