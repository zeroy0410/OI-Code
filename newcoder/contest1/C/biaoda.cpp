#include<bits/stdc++.h>
 
#define FOG(x,y,z) for(register int x=y,x##_=z;x<=x##_;++x)
#define DOG(x,y,z) for(register int x=y,x##_=z;x>=x##_;--x)
#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;++x)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;--x)
#define FOR_(x,y,z,s) for(int x=y,x##_=z;x<=x##_;x+=s)
#define FOR__(x,y,z) for(int x=y,x##_=z;x<=x##_;x<<=1)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)
#define EOD(x,y,z) for(int &x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)
#define While(x) for(;x;)
#define clr(x,y) memset(x,y,sizeof(x))
#define szf(x) sizeof(x)
#define min3(x,y,z) min(min(x,y),z)
#define max3(x,y,z) max(max(x,y),z)
 
#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read(x),read(y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define reads(str) sf("%s",str)
 
#define ts (*this)
#define sf scanf
#define pf printf
 
#define ll long long
#define ull unsigned long long
#define db double
#define ct clock_t
#define ck() clock()
#define rd rand()
#define rmx RAND_MAX
#define RD T*(rd*2-rmx)
 
 
using namespace std;
 
template<class T>bool tomin(T &x,T y){return y<x?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
template<class T>void read(T &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
bool mem1;
const db Pi=acos(-1);
const int maxn=6005;
const int maxm=6005;
int n,m,Q;
struct Edge{
    int e,to,c;
}edge[maxm];
int head[maxn],tot;
void Add(int x,int y,int z){
    edge[++tot]=(Edge){y,head[x],z};
    head[x]=tot;
}
int dis[maxn];
bool ok[maxm];
namespace Build{
    int q[maxn];
    struct node{
        int e,c,id;
        bool operator <(const node &A)const
        {
            return e<A.e;
        }
    };
    vector<node>eg[maxn];
    void Init(){
        FOR(u,1,n){
            EGOR(u,v,w)if(v!=u)eg[u].push_back((node){v,w,u_});
            sort(eg[u].begin(),eg[u].end());
        }
    }
    bool vis[maxn];
    void dfs(int u){
        vis[u]=1;
        FOR(i,0,(int)eg[u].size()-1){
            int v=eg[u][i].e,w=eg[u][i].c;
            if(dis[v]==dis[u]+w&&!vis[v]){
                dfs(v);
                ok[eg[u][i].id]=1;
            }
        }
    }
    void solve(int s){
        clr(ok,0);
        clr(vis,0);
        dfs(s);
    }
}
namespace P0{
    int req[maxm][2];
    int ans[maxm];
    bool vis[maxn];
    queue<int>q;
    int cnt[maxn];
    int sz[maxn],son[maxn],dep[maxn],top[maxn],fa[maxn];
    void dfs(int u){
        vis[u]=1;
        sz[u]=1;
        son[u]=0;
        EOR(u,v)if(ok[u_]){
            dep[v]=dep[u]+1;
            fa[v]=u;
            dfs(v);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]])son[u]=v;
        }
    }
    void dfs_top(int u,int tp){
        top[u]=tp;
        EOR(u,v)if(ok[u_])dfs_top(v,v==son[u]?tp:v);
    }
    int LCA(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]])x=fa[top[x]];
            else y=fa[top[y]];
        }return dep[x]>dep[y]?y:x;
    }
    void Calc(int s){
        clr(dis,67);
        clr(vis,0);
        q.push(s);
        dis[s]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            vis[u]=0;
            EGOR(u,v,w)if(tomin(dis[v],dis[u]+w)&&!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
        Build::solve(s);
        dfs(s);
        dfs_top(s,s);
        FOR(i,1,Q)if(vis[req[i][0]]&&vis[req[i][1]])
            tomax(ans[i],dis[LCA(req[i][0],req[i][1])]);
    }
    void solve(){
        Build::Init();
        clr(ans,-1);
        FOR(i,1,Q)read2(req[i][0],req[i][1]);
        FOR(i,1,n)Calc(i);
        FOR(i,1,Q){
            pf("%d",ans[i]);
            if(i<Q)pf("\n");
        }
    }
}
bool mem2;
int main(){
    // ct S=ck();
    // freopen("c.in","r",stdin);
    // freopen("c.out","w",stdout);
    // cerr<<(&mem2-&mem1)/1024.0/1024<<endl;
    srand(time(NULL));
    read3(n,m,Q);
    int x,y,z;
    FOR(i,1,m){
        read3(x,y,z);
        Add(x,y,z);
    }
    P0::solve();
    // cerr<<ck()-S<<endl;
    return 0;
}