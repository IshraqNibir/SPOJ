#include "bits/stdc++.h"
using namespace std;

#define MAXN   1000005

int spf[MAXN];
int prm[300];
bool ok[300];

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

int getFactorization(int x)
{
    vector<int> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    int prvs = ret[0];
    int cnt = 1;
    int ans = 1;
    for (int i=1; i<ret.size(); i++) {
        if (ret[i] != prvs) {
            ans *= (cnt+1);
            prvs = ret[i];
            cnt = 1;
        }
        else {
            cnt++;
        }
        if (i == ret.size()-1)
            ans *= (cnt+1);
    }
    return ans;
}

void precal()
{
    memset (prm, 0, sizeof (prm));
    for (int i=2; i<290; i++) {
        int skip = 0;
        for (int j=2; j<=sqrt(i); j++) {
            if(i%j == 0)
                skip = 1;
        }
        if (skip == 0)
            prm[i] = 1;
    }
    for (int i=2; i<290; i++) {
        for (int j=2; j<20; j++) {
            if (prm[j]==1 && i%j==0) {
                int div = i/j;
                if (prm[div] == 1 && div != j)
                    ok[i] = true;
            }
        }
    }
}

int main()
{
    memset(ok, false, sizeof(ok));
    sieve();
    precal();
    int lim = 0;
    for (int i=2; i<=1000000; i++) {
        int fin = getFactorization(i);
        if (ok[fin] == true) {
            lim++;
        }
        if (lim == 9) {
            printf ("%d\n", i);
            lim = 0;
        }
    }
    return 0;
}

