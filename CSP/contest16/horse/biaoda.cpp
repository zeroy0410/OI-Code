#include<bits/stdc++.h>
#define M 100005
#define LL long long
#pragma GCC optimize(3)
using namespace std;
#define getchar() (__S==__T&&(__T=(__S=__B)+fread(__B,1,1<<15,stdin),__S==__T)?EOF:*__S++)
char __B[1<<21],*__S=__B,*__T=__B;
inline void Rd(int &x){
    char c;x=0;
    while(c=getchar(),c<48);
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>47);
}
int n,A[M];
struct edge{
    int to,co,fr;
}E[M<<1];
int lst[M],tote;
inline void addedge(int a,int b,int c){
    E[++tote]=(edge){b,c,lst[a]};
    lst[a]=tote;
}
namespace Px{
    const LL oo=2e18;
    LL dp[M],ned[M];
    struct node{LL v,w;};
    vector<node>son[2][M];
    bool cmp0(node a,node b){return a.w+a.v<b.w+b.v;}
    bool cmp1(node a,node b){return a.v<b.v;}
    bool check(LL x,int v){
        for(int i=0,sz=son[1][v].size();i<sz;i++)
            if(son[1][v][i].v<=x)x+=son[1][v][i].w;
            else return 0;
        for(int i=0,sz=son[0][v].size();i<sz;i++)x+=son[0][v][i].w;
        if(x<0)return 0;
        for(int i=0,sz=son[0][v].size();i<sz;i++){
            x-=son[0][v][i].w;
            if(x<son[0][v][i].v)return 0;
        }
        return 1;
    }
    void dfs(int v,int f){
        for(int i=lst[v];i;i=E[i].fr){
            int u=E[i].to;
            if(u==f)continue;
            dfs(u,v);
			LL x=-dp[u]+A[u]-E[i].co*2;
			son[x>=0][v].push_back((node){E[i].co+ned[u],x});
        }
        sort(son[0][v].begin(),son[0][v].end(),cmp0);
        sort(son[1][v].begin(),son[1][v].end(),cmp1);
        LL l=0,r=2e14,res=0;
        while(l<=r){
            LL mid=(l+r)>>1;
            if(check(mid,v))r=mid-1,res=mid;
            else l=mid+1;
        }
        ned[v]=max(0LL,res-A[v]);
        LL x=res;
        for(int i=0,sz=son[1][v].size();i<sz;i++)if(son[1][v][i].v<=x)x+=son[1][v][i].w;
        for(int i=0,sz=son[0][v].size();i<sz;i++)x+=son[0][v][i].w;
        dp[v]=res-x;
    }
    void solve(){
        dfs(1,0);
        printf("%lld\n",ned[1]);
    }
}
int main(){
    Rd(n);
    for(int i=1;i<=n;i++)Rd(A[i]);
    for(int i=1,a,b,c;i<n;i++){
        Rd(a),Rd(b),Rd(c);
        addedge(a,b,c);
        addedge(b,a,c);
    }
    Px::solve();
    return 0;
}
