#include<bits/stdc++.h>
#define M 200005
#define LL long long
using namespace std;
bool __2;
inline void Rd(int &x){
    x=0;char c;int f=1;
    while((c=getchar())<48)if(c=='-')f=0;
    do x=(x<<3)+(x<<1)+(c^48);
    while((c=getchar())>47);
    if(!f)x=-x;
}
const LL mod=1e9+7; 
int n,m;
LL X,Pw2[M];
struct Road{
    int u,v,w;
    void read(){Rd(u),Rd(v),Rd(w);}
    bool operator <(const Road &_)const{
        return w<_.w;
    }
}ro[M];
struct edge{
    int to,co,fr;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b,int c){
    E[++tote]=(edge){b,c,lst[a]};
    lst[a]=tote;
}
bool cho[M];
int ff[M];
int fa[M][18],mx[M][18],dep[M];
int getff(int x){
    return ff[x]==x?x:ff[x]=getff(ff[x]);
}
void dfs(int v,int f){
    dep[v]=dep[f]+1;
    for(int i=lst[v];i;i=E[i].fr){
        int u=E[i].to;
        if(u==f)continue;
        fa[u][0]=v;
        mx[u][0]=E[i].co;
        dfs(u,v);
    }
}
void Up(int &res,int &a,int stp){
    for(int i=0;i<18;i++)
        if((1<<i)&stp){
            res=max(res,mx[a][i]);
            a=fa[a][i];
        }
}
int LCA(int a,int b){
    int res=0;
    if(dep[a]<dep[b])swap(a,b);
    Up(res,a,dep[a]-dep[b]);
    if(a==b)return res;
    for(int i=17;i>=0;i--)
        if(fa[a][i]!=fa[b][i]){
            res=max(res,max(mx[a][i],mx[b][i]));    
            a=fa[a][i],b=fa[b][i];
        }
    res=max(res,max(mx[a][0],mx[b][0]));
    return res;
}
void solve(){
    LL all=0;
    for(int i=1;i<=n;i++)ff[i]=i;
    for(int i=1;i<=m;i++)cho[i]=0;
    for(int i=1;i<=m;i++){
        int a=ro[i].u,b=ro[i].v;
        int f1=getff(a),f2=getff(b);
        if(f1==f2)continue;
        all+=ro[i].w;
        ff[f1]=f2;
        addedge(a,b,ro[i].w);
        addedge(b,a,ro[i].w);
        cho[i]=1;
    }
    dfs(1,0);
    for(int i=1;i<18;i++)
        for(int j=1;j<=n;j++){
            fa[j][i]=fa[fa[j][i-1]][i-1];
            mx[j][i]=max(mx[j][i-1],mx[fa[j][i-1]][i-1]);
        }
    LL res=0;
    int c1=0,c2=0;
    if(all==X)res=(Pw2[n-1]-2)*Pw2[m-n+1]%mod;
    for(int i=1;i<=m;i++)if(!cho[i]){
        int a=ro[i].u,b=ro[i].v;
        int mi=LCA(a,b);
        LL ne=all-mi+ro[i].w;
        if(ne==X)c1++;
        if(ne>=X)c2++;
    }
    if(c1){
        res=(res+2*(Pw2[c1]-1)*Pw2[c2-c1])%mod;
    }
    printf("%lld\n",(res%mod+mod)%mod);
}
int main(){
//  printf("%lf\n",(&__1-&__2)/1024.0/1024);
//  freopen("zhuzhu.in","r",stdin);
//  freopen("zhuzhu.out","w",stdout);
    Pw2[0]=1;
    for(int i=1;i<M;i++)Pw2[i]=Pw2[i-1]*2%mod;
    for(int _=(scanf("%d",&_),_);_;_--){
        scanf("%d%d%lld",&n,&m,&X);
        for(int i=1;i<=n;i++)lst[i]=0;tote=0;
        for(int i=1;i<=m;i++)ro[i].read();
        sort(ro+1,ro+m+1);
        solve();
    }
    return 0;
}
