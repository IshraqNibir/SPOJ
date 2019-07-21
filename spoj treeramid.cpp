#include <bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;
vector<int>adj[10005];
int vis[10005];
int child[10005],val[10005];

void bfs(int s)
{
    vis[s]=1;
    queue<int>q;
    q.push(s);
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=0;i<adj[u].size();i++) {
            int v=adj[u][i];
            if(vis[v]==0) {
                vis[v]=1;
                child[u]++;
                q.push(v);
            }
        }
    }
}

void dfs(int at)
{
    if(vis[at])
        return;
    vis[at]=1;
    for(int i=0;i<adj[at].size();i++) {
        if(vis[adj[at][i]]==0) {
            dfs(adj[at][i]);
            val[at]+=val[adj[at][i]];
        }
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--) {
        memset(vis,0,sizeof(vis));
        memset(val,0,sizeof(val));
        int n;
        scanf("%d", &n);
        for(int i=0;i<10005;i++) {
            child[i]=0;
        }
        int u,v;
        for(int i=1;i<=n-1;i++) {
            scanf("%d %d", &u, &v);
            adj[u].pb(v);
            adj[v].pb(u);
        }
        bfs(0);
        for(int i=0;i<n;i++) {
            val[i]=child[i]+1;
        }
        memset(vis,0,sizeof(vis));
        dfs(0);
        ll ans=0;
        for(int i=0;i<n;i++) {
            ans+=val[i];
        }
        printf("%lld\n",ans);
        for(int i=0;i<10005;i++) {
            adj[i].clear();
        }
    }
    return 0;
}
