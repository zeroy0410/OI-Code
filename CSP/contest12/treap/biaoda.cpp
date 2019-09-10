#include<bits/stdc++.h>
using namespace std;
const int N=1001000,mod=998244353;
typedef long long ll;
int ksm(ll a,int b,int c=1){
    for(;b;b/=2,a=a*a%mod)
        if(b&1)c=c*a%mod;
    return c;
}
int f[N],inv[N],p,n,G[N],to[N*2],ne[N*2],xb;
void init(){
    inv[1]=1;f[1]=(p+1)%mod;
    for(int i=2;i<=n;++i){
        inv[i]=mod-mod/i*(ll)inv[mod%i]%mod;
        f[i]=((ll)inv[i]*p+1)%mod;
    }
}
void add(int x,int y){ne[xb]=G[x];to[xb]=y;G[x]=xb++;}
int ansx=0,ansy=1,tmpx=1,tmpy=1,zer=0;
int sz[N],fa[N];
void dfs(int x){
    sz[x]=1;
    for(int i=G[x],u;~i;i=ne[i])if((u=to[i])!=fa[x]){
        fa[u]=x;dfs(u);sz[x]+=sz[u];
    }
    if(!f[sz[x]])++zer;else tmpx=(ll)tmpx*f[sz[x]]%mod;
}
void dfs2(int x){
    if(!zer){
        ansx=((ll)ansx*tmpy+(ll)ansy*tmpx)%mod;
        ansy=(ll)ansy*tmpy%mod;
    }
    int tx=tmpx,ty=tmpy,tz=zer;
    for(int i=G[x],u;~i;i=ne[i])if((u=to[i])!=fa[x]){
        tmpx=tx;tmpy=ty;zer=tz;
        if(!f[sz[u]])--zer;else tmpy=(ll)tmpy*f[sz[u]]%mod;
        if(!f[n-sz[u]])++zer;else tmpx=(ll)tmpx*f[n-sz[u]]%mod;
        dfs2(u);        
    }
}
int main(){
//  freopen("treap.in","r",stdin);
//  freopen("treap.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    memset(G,-1,sizeof G);
    cin>>n>>p;p=(p+mod-1)%mod;init();
    for(int i=1;i<n;++i){
        int x,y;cin>>x>>y;
        add(x,y);add(y,x);
    }
    dfs(1);
    dfs2(1);
    ansy=(ll)ansy*n%mod;
    cout<<ksm(ansy,mod-2,ansx)<<endl;
    return 0;
}
