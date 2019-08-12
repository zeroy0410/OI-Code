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
int n,m;
namespace P100{
    const int maxn=1755;
    const int maxs=7;
    const int maxm=1600*250+5;
    const int Inf=2e9;
    int s,t;
    int C[maxn];
    bool ok[maxn][maxn];
    int S[maxn],T[maxn][maxs],W[maxn][maxs];
    struct Edge{
        int e,to,f,c;
    }edge[maxm<<1];
    int head[maxn],tot=1;
    void Add(int x,int y,int f,int c){
        edge[++tot]=(Edge){y,head[x],f,c};head[x]=tot;
        edge[++tot]=(Edge){x,head[y],0,-c};head[y]=tot;
        // pf("Add %d %d %d %d\n",x,y,f,c);
    }
    queue<int>q;
    int dis[maxn];
    bool vis[maxn];
    bool SPFA(){
        FOR(i,s,t){
            vis[i]=0;
            dis[i]=Inf;
        }
        q.push(s);
        dis[s]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            vis[u]=0;
            EGOR(u,v,w)if(edge[u_].f&&tomin(dis[v],dis[u]+w)&&!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
        // pf("dis=%d\n",dis[t]);
        return dis[t]<2e9;
    }
    ll ans;
    int ansf;
    int dfs(int u,int f){
        if(u==t||!f){
            ansf+=f;
            // if(f)pf("dfs %d\n",f);
            return ans+=(ll)dis[u]*f,f;
        }
        int F,used=0;
        vis[u]=1;
        EGOR(u,v,w)if(dis[v]==dis[u]+w&&!vis[v]&&(F=dfs(v,min(f-used,edge[u_].f)))){
            edge[u_].f-=F;
            edge[u_^1].f+=F;
            if((used+=F)==f)break;
        }return used;
    }
    bool Dinic(){
        FOR(i,s,t)vis[i]=0;
        return dfs(s,Inf);
    }
    void solve(){
        int sum=0;
        FOR(i,1,m){
            read(C[i]);
            sum+=C[i];
        }
        // pf("sum=%d\n",sum);
        FOR(i,1,n)FOR(j,1,m)read(ok[i][j]);
        t=m;
        FOR(i,1,n){
            read(S[i]);
            T[i][S[i]+1]=Inf;
            FOR(j,1,S[i])read(T[i][j]);
            FOR(j,0,S[i])read(W[i][j]);
            FOR(j,0,S[i]){
                Add(s,++t,T[i][j+1]-T[i][j],W[i][j]);
                FOR(k,1,m)if(ok[i][k])Add(t,k,Inf,0);
            }
        }
        // pf("%d\n",t);
        ++t;
        FOR(i,1,m)Add(i,t,C[i],0);
        while(SPFA())while(Dinic());
        if(sum!=ansf)puts("-1");
        else pf("%lld",ans);
        // pf("%d",ansf);
    }
}
bool mem2;
int main(){
    // cerr<<(&mem2-&mem1)/1024.0/1024<<endl;
    // freopen("in.txt","r",stdin);
    // freopen("my.txt","w",stdout);
    freopen("job.in","r",stdin);
    freopen("job.out","w",stdout);
    srand(time(NULL));
    read2(n,m);
    P100::solve();
    return 0;
}