#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
int ara[1015][1015],sum[1015][1015];
char ch[1015][1015];
int n,m;
void pre()
{
    for(int i=1;i<=1010;i++) {
        for(int j=1;j<=1010;j++) {
            if(i%2==1 && j%2==0)
                ch[i][j]='.';
            else if(i%2==0 && j%2==1)
                ch[i][j]='.';
        }
    }
    for(int i=1;i<=1010;i++) {
        for(int j=1;j<=1010;j++) {
            int cnt=0;
            if(ch[i-1][j]=='.')
                cnt++;
            if(ch[i][j-1]=='.')
                cnt++;
            if(ch[i][j+1]=='.')
                cnt++;
            if(ch[i+1][j]=='.')
                cnt++;
            ara[i][j]=cnt;
        }
    }
    for(int i=1;i<=1010;i++) {
        for(int j=1;j<=1010;j++) {
            sum[i][j]=ara[i][j]+sum[i][j-1];
        }
    }
}
int main()
{
    memset(ara,0,sizeof(ara));
    memset(sum,0,sizeof(sum));
    for(int i=0;i<1010;i++) {
        for(int j=0;j<1010;j++) {
            ch[i][j]='*';
        }
    }
    pre();
    int t;
    cin>>t;
    while(t--) {
        cin>>n>>m;
        int ans=0;
        for(int i=1;i<n;i++) {
            ans+=sum[i][m-1];
        }
        for(int i=1;i<m;i++) {
            int cnt=0;
            if(ch[n-1][i]=='.')
                cnt++;
            if(ch[n][i-1]=='.')
                cnt++;
            if(ch[n][i+1]=='.')
                cnt++;
            ans+=cnt;
        }
        for(int i=1;i<n;i++) {
            int cnt=0;
            if(ch[i][m-1]=='.')
                cnt++;
            if(ch[i-1][m]=='.')
                cnt++;
            if(ch[i+1][m]=='.')
                cnt++;
            ans+=cnt;
        }
        if(ch[n-1][m]=='.')
            ans++;
        if(ch[n][m-1]=='.')
            ans++;
        cout<<ans<<endl;
    }
    return 0;
}
