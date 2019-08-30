#include "bits/stdc++.h"
using namespace std;

#define MAXN   10000005
#define ll long long

int spf[MAXN];
ll ans[MAXN];
void sieve()
{
    spf[1] = 1;

    for (int i=2; i<MAXN; i++)
        spf[i] = i;

    for (int i=4; i<MAXN; i+=2)
        spf[i] = 2;

    for (int i=3; i*i<MAXN; i++)
    {
        if (spf[i] == i)
        {
            for (int j=i*i; j<MAXN; j+=i)

                if (spf[j]==j)
                    spf[j] = i;
        }
    }
}

void precal()
{
    ans[0]=0;
    ans[1]=0;
    for(int i=2;i<MAXN;i++) {
        ans[i]=ans[i-1]+spf[i];
    }
}

int main()
{
    sieve();
    precal();
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        cout<<ans[n]<<endl;
    }
    return 0;
}
