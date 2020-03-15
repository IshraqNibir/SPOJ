#include <bits/stdc++.h>
using namespace std;
#define max_node 1000005
#define max_len 100
int node[max_node][26];
int freq[max_node][26];
int root,nnode;
string s,s1;
void initialize() {
    root=0;
    nnode=0;
    for(int i=0;i<26;i++) {
        node[root][i]=-1;
        freq[root][i]=0;
    }
}
void insert() {
    cin>>s;
    int now=root;
    for(int i=0;i<s.length();i++) {
        if(node[now][s[i]-'a']==-1) {
            node[now][s[i]-'a']=++nnode;
            for(int j=0;j<26;j++) {
                freq[nnode][j]=0;
                node[nnode][j]=-1;
            }
        }
        freq[now][s[i]-'a']++;
        now=node[now][s[i]-'a'];
    }
}
int search() {
    int now=root;
    int mn=100000000;
    for(int i=0;i<s1.length();i++) {
        if(node[now][s1[i]-'a']==-1) {
            return 0;
        }
        mn=min(freq[now][s1[i]-'a'],mn);
        now=node[now][s1[i]-'a'];
    }
    return mn;
}
int main()
{
    int n,query;
    initialize();
    cin>>n>>query;
    for(int i=1;i<=n;i++)
        insert();
    int ans;
    for(int i=1;i<=query;i++) {
        cin>>s1;
        ans=search();
        cout<<ans<<endl;
    }
    return 0;
}

