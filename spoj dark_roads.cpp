#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
struct edge {
    int u, v, w;
    bool operator<(const edge& p) const
    {
        return w < p.w;
    }
};
int pr[MAXN];
vector<edge> e;
int find(int r)
{
    return (pr[r] == r) ? r : find(pr[r]);
}
int mst(int n)
{
    sort(e.begin(), e.end());
    for (int i = 0; i <= n; i++)
        pr[i] = i;

    int count = 0, s = 0;
    for (int i = 0; i < (int)e.size(); i++) {
        int u = find(e[i].u);
        int v = find(e[i].v);
        if (u != v) {
            pr[u] = v;
            count++;
            s += e[i].w;
            if (count == n - 1)
                break;
        }
    }
    return s;
}

int main()
{
    // READ("in");
    while(1) {
        int n, m;
        cin >> n >> m;
        if (n==0 and m==0)
            break;
        int tot = 0;
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edge get;
            get.u = u;
            get.v = v;
            get.w = w;
            tot += w;
            e.push_back(get);
        }
        cout << tot - mst(n) << endl;
        e.clear();
    }
    return 0;
}

