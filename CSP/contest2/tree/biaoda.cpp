#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
bool __1;
int n,m,A[M];
struct edge{
    int to,fr;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b){
    E[++tote]=(edge){b,lst[a]};
    lst[a]=tote;
}
namespace Px{
    int son[M],sz[M],top[M],fa[M];
    int L[M],R[M],TT;
    bool bel[M],now[2];
    void dfsinit(int v,int f,bool be){
        fa[v]=f;sz[v]=1;bel[v]=be;
        for(int i=lst[v];i;i=E[i].fr){
            int u=E[i].to;
            if(u==f)continue;
            dfsinit(u,v,be^1);
            sz[v]+=sz[u];
            if(sz[u]>sz[son[v]])son[v]=u;
        }
    }
    void redfs(int v,int tp){
        top[v]=tp;L[v]=++TT;
        if(son[v])redfs(son[v],tp);
        for(int i=lst[v];i;i=E[i].fr){
            int u=E[i].to;
            if(u==fa[v]||u==son[v])continue;
            redfs(u,u);
        }R[v]=TT;
    }
    struct BIT{
        LL C[M];
        void Upd(int x,int c){
            while(x<=n)C[x]+=c,x+=x&-x;
        }
        LL Get(int x){
            LL res=0;
            while(x)res+=C[x],x-=x&-x;
            return res;
        }
        LL Query(int l,int r){
            if(l>r)return 0;
            return Get(r)-Get(l-1);
        }
    }sum[2][2],cnt[2][2];
    void Add(int x,int c){
        int a=bel[x],b=A[x];
        cnt[a][b].Upd(L[x],c);
        while(x){
            sum[a][b].Upd(L[x],c*x);
            x=fa[top[x]];
        }
    }
    LL Getans(int x){
        int del=0;
        LL ans=0;
        while(x){
            ans+=sum[0][now[0]].Query(L[top[x]],L[x]-1)+sum[1][now[1]].Query(L[top[x]],L[x]-1);
            ans+=(cnt[0][now[0]].Query(L[x],R[x])+cnt[1][now[1]].Query(L[x],R[x])-del)*x;
            x=top[x];
            del=cnt[0][now[0]].Query(L[x],R[x])+cnt[1][now[1]].Query(L[x],R[x]);
            x=fa[x];
        }
        return ans;
    }
    void solve(){
        dfsinit(1,0,0);
        redfs(1,1);
        now[0]=now[1]=1;
        for(int i=1;i<=n;i++)Add(i,1);
        for(int i=1;i<=n;i++)printf("%d\n",R[i]);
        for(int i=1,op,x;i<=m;i++){
            scanf("%d%d",&op,&x);
            if(op==1)now[bel[x]^1]^=1;
            else if(op==2){
                Add(x,-1);
                A[x]^=1;
                Add(x,1);
            }else printf("%lld\n",Getans(x));
        }
    }
}
bool __2;
int main(){
    // printf("%lf\n",(&__2-&__1)/1024.0/1024);
    // freopen("tree.in","r",stdin);
    // freopen("tree.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    for(int i=1,a,b;i<n;i++){
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addedge(b,a);
    }
    Px::solve();
    return 0;
}