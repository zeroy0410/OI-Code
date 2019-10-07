//minamoto
#include<bits/stdc++.h>
#define R register
#define pi pair<int,int>
#define fi first
#define se second
#define ls (p<<1)
#define rs (p<<1|1)
#define fp(i,a,b) for(R int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(R int i=a,I=b-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
#define gg(u) for(vector<eg>::iterator it=pos[u].begin();it!=pos[u].end();++it)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
int read(){
    R int res=1,f=1;R char ch;
    while((ch=getc())>'9'||ch<'0')(ch=='-')&&(f=-1);
    for(res=ch-'0';(ch=getc())>='0'&&ch<='9';res=res*10+ch-'0');
    return res*f;
}
char sr[1<<21],z[21];int K=-1,Z=0;
inline void Ot(){fwrite(sr,1,K+1,stdout),K=-1;}
void print(R int x){
    if(K>1<<20)Ot();if(x<0)sr[++K]='-',x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++K]=z[Z],--Z);sr[++K]='\n';
}
const int N=1e5+5,M=N<<5;
struct Gr{
    struct eg{int v,nx;}e[N<<1];int head[N],tot;
    inline void add(R int u,R int v){e[++tot]={v,head[u]},head[u]=tot;}
    int dep[N],top[N],fa[N],sz[N],son[N];
    void dfs1(int u){
        sz[u]=1,dep[u]=dep[fa[u]]+1;
        go(u)if(v!=fa[u]){
            fa[v]=u,dfs1(v),sz[u]+=sz[v];
            if(sz[v]>sz[son[u]])son[u]=v;
        }
    }
    void dfs2(int u,int t){
        top[u]=t;if(!son[u])return;
        dfs2(son[u],t);
        go(u)if(!top[v])dfs2(v,v);
    }
    int LCA(int u,int v){
        while(top[u]!=top[v]){
            if(dep[top[u]]<dep[top[v]])swap(u,v);
            u=fa[top[u]];
        }
        return dep[u]<dep[v]?u:v;
    }
    inline int dis(R int u,R int v){return dep[u]+dep[v]-(dep[LCA(u,v)]<<1);}
}G;
struct node{
    int x,y,v;pi p;
    node(){}
    node(R int X,R int Y,R int V,R pi P):x(X),y(Y),v(V),p(P){}
}st[N];
struct eg{
    int u,v;
    eg(){}
    eg(R int u,R int v):u(u),v(v){}
};
pi li[N];vector<eg>pos[M];
int fa[N],ans[N],dep[N];
int n,m,top;
int find(int x){return fa[x]==x?x:find(fa[x]);}
void ins(int p,int l,int r,int ql,int qr,int u,int v){
    if(ql<=l&&qr>=r)return pos[p].push_back(eg(u,v)),void();
    int mid=(l+r)>>1;
    if(ql<=mid)ins(ls,l,mid,ql,qr,u,v);
    if(qr>mid)ins(rs,mid+1,r,ql,qr,u,v);
}
void merge(int u,int v,int &ans){
//  printf("%d %d ",u,v);
    u=find(u),v=find(v);
    int a=li[u].fi,b=li[u].se,c=li[v].fi,d=li[v].se,res=-1;
//  printf("%d %d %d %d\n",a,b,c,d);
    pi p;
    if(cmax(res,G.dis(a,b)))p=pi(a,b);
    if(cmax(res,G.dis(a,c)))p=pi(a,c);
    if(cmax(res,G.dis(a,d)))p=pi(a,d);
    if(cmax(res,G.dis(b,c)))p=pi(b,c);
    if(cmax(res,G.dis(b,d)))p=pi(b,d);
    if(cmax(res,G.dis(c,d)))p=pi(c,d);
    cmax(ans,res);
    if(dep[u]<dep[v])swap(u,v);
    st[++top]=node(u,v,0,li[u]);
    if(dep[u]==dep[v])++dep[u],st[top].v=1;
    fa[v]=u,li[u]=p;
//  printf("%d\n",res);
}
void del(int cur){
    while(top>cur){
        dep[st[top].x]-=st[top].v,fa[st[top].y]=st[top].y;
        li[st[top].x]=st[top].p,--top;
    }
}
void solve(int p,int l,int r,int res){
    int now=top;
    gg(p)merge(it->u,it->v,res);
    if(l==r)ans[l]=res;
    else{
        int mid=(l+r)>>1;
        solve(ls,l,mid,res);
        solve(rs,mid+1,r,res);
    }
    del(now);
}
int x;
int main(){
//  freopen("testdata.in","r",stdin);
    freopen("speed.in","r",stdin);
    freopen("speed.out","w",stdout);
    n=read(),m=read();
    fp(i,1,n-1){
        int u=read(),v=read(),l=read(),r=read();
        G.add(u,v),G.add(v,u);
        ins(1,1,n,l,r,u,v);
    }
    G.dfs1(1),G.dfs2(1,1);
    fp(i,1,n)fa[i]=i,li[i]=pi(i,i);
    solve(1,1,n,0);
    while(m--)x=read(),print(ans[x]);
    return Ot(),0;
}