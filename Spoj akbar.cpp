#include <bits/stdc++.h>
#define mkp make_pair
using namespace std;
vector<int>adj[1000005];
int vis[1000005];
int level[1000005];
bool bfs(int s,int seg)
{
    queue<int>q;
    q.push(s);
    level[s]=0;
    int cnt=0;
    if(vis[s]==0) {
        vis[s]=1;
        cnt++;
    }
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        if(level[u]<seg) {
            for(int i=0;i<adj[u].size();i++) {
                int v=adj[u][i];
                if(vis[v]==0) {
                    vis[v]=1;
                    level[v]=level[u]+1;
                    q.push(v);
                    cnt++;
                }
            }
        }
    }
    if(cnt>0)
        return true;
    else
        return false;
}
int main()
{
    int t;
    cin>>t;
    while(t--) {
        memset(vis,0,sizeof(vis));
        int n,m,r,u,v;
        cin>>n>>r>>m;
        for(int i=1;i<=r;i++) {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector< pair<int,int> >vb;
        int a,b;
        for(int i=1;i<=m;i++) {
            cin>>a>>b;
            vb.push_back(mkp(b,a));
        }
        sort(vb.begin(),vb.end());
        reverse(vb.begin(),vb.end());
        int skip=0;
        for(int i=0;i<vb.size();i++) {
            a=vb[i].first;
            b=vb[i].second;
            bool ans=bfs(b,a);
            if(ans==false) {
                skip=1;
                break;
            }
        }
        for(int i=1;i<=n;i++) {
            if(vis[i]==0) {
                skip=1;
                break;
            }
        }
        if(skip==1)
            cout<<"No"<<endl;
        else
            cout<<"Yes"<<endl;
        for(int i=0;i<1000005;i++) {
            adj[i].clear();
        }
    }
    return 0;
}
