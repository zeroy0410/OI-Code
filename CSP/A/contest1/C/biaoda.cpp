#include<iostream>
#include<cstdio>
using namespace std;
#define M 100005
//#pragma comment(linker, "/STACK:1024000000,1024000000")
typedef long long LL;
template<class T>void tomax(T &x,T y){
    if(x<y)x=y;
}
template<class T>bool tomin(T &x,T y){
    if(x>y)return x=y,1;
    return 0;
}
bool MM1;
struct Edge{
    int to,nx;
}edge[M<<1];
int h[M],TT_E;
void link(int a,int b){
    edge[++TT_E].to=b;
    edge[TT_E].nx=h[a];
    h[a]=TT_E;
}
#define DEG(i,st) for(int i=h[st];i;i=edge[i].nx)
int A[M],n;
char Op[10],ty[10];
struct P1{
    int ans,dis[M];
    void dfs(int F,int now){
        dis[now]=dis[F]+A[now];
        DEG(i,now){
            int to=edge[i].to;
            if(to==F)continue;
            dfs(now,to);
        }
    }
    void solve(){
        while(scanf("%s",Op)&&Op[0]!='D'){
            int u,to;
            scanf("%d",&u);
            if(Op[0]=='C'){
                scanf("%d",&to);
                A[u]=to;
            }else{
                dis[u]=0,dfs(0,u);
                ans=-1e9;
                for(int i=1;i<=n;i++)
                    tomax(ans,dis[i]);
                printf("%d\n",ans);
            }
        }
    }
}p1;
int V[M];
struct YD{
    int Lson[M*120],Rson[M*120],Val[M*120],Add[M*120],Tt;
    void Up(int rt){
        Val[rt]=max(Val[Lson[rt]],Val[Rson[rt]])+Add[rt];
    }
    void build(int L,int R,int &rt){
        rt=++Tt;
        if(L==R){
            Val[rt]=V[L];
            return;
        }
        int mid=L+R>>1;
        build(L,mid,Lson[rt]);
        build(mid+1,R,Rson[rt]);
        Up(rt);
    }
    void Update(int L,int R,int l,int r,int ad,int rt){
        if(L==l&&R==r){
            Add[rt]+=ad;
            if(l!=r)Up(rt);
            else Val[rt]+=ad;
            return;
        }
        int mid=L+R>>1;
        if(r<=mid)Update(L,mid,l,r,ad,Lson[rt]);
        else if(l>mid)Update(mid+1,R,l,r,ad,Rson[rt]);
        else {
            Update(L,mid,l,mid,ad,Lson[rt]);
            Update(mid+1,R,mid+1,r,ad,Rson[rt]);
        }
        Up(rt);
    }
    int Query(int L,int R,int l,int r,int rt){
        if(L==l&&R==r)return Val[rt];
        int mid=L+R>>1;
        if(r<=mid)return Query(L,mid,l,r,Lson[rt])+Add[rt];
        else if(l>mid)return Query(mid+1,R,l,r,Rson[rt])+Add[rt];
        else return max(Query(L,mid,l,mid,Lson[rt]),Query(mid+1,R,mid+1,r,Rson[rt]))+Add[rt];
    }
}T;
struct P2{
    int Mx,Mid,sz[M],TT,Vis[M];
    void Get(int F,int now){TT++;
        sz[now]=1;
        DEG(i,now){
            int to=edge[i].to;
            if(to==F||Vis[to])continue;
            Get(now,to);
            sz[now]+=sz[to];
        }
    }
    void Find(int F,int now){
        int Son=TT-sz[now];
        DEG(i,now){
            int to=edge[i].to;
            if(to==F||Vis[to])continue;
            Find(now,to);
            tomax(Son,sz[to]);
        }
        if(Mid==-1||Son<Mx)Mx=Son,Mid=now;
    }
    int ID[M],L[M][18],R[M][18],belong[M][18],_id,fa[M],RT[M],Dep[M];
    void DFS(int F,int now,int dep){
        L[now][dep]=++_id;
        V[_id]=V[L[F][dep]]+A[now];
        belong[now][dep]=belong[F][dep];
        DEG(i,now){
            int to=edge[i].to;
            if(to==F||Vis[to])continue;
            DFS(now,to,dep);
        }
        R[now][dep]=_id;
    }
    void Solve(int F,int Rt,int dep){
        TT=0,Mid=-1;
        Get(0,Rt),Find(0,Rt);
        int Now=Mid;
        fa[Now]=F,Dep[Now]=dep;
        V[1]=A[Now],_id=1;
        L[Now][dep]=1;
        Vis[Now]=1;
        DEG(i,Now){
            int to=edge[i].to;
            if(Vis[to])continue;
            belong[Now][dep]=to;
            DFS(Now,to,dep);
        }
        belong[Now][dep]=0;
        R[Now][dep]=ID[Now]=_id;
        T.build(1,_id,RT[Now]);
        DEG(i,Now){
            int to=edge[i].to;
            if(Vis[to])continue;
            Solve(Now,to,dep+1);
        }
        Vis[Now]=0;
    }
    void Update(int x,int to){
        int ds=to-A[x];
        for(int i=x,d=Dep[x];i;i=fa[i],d--)
            T.Update(1,ID[i],L[x][d],R[x][d],ds,RT[i]);
        A[x]=to;
    }
    int Ask(int x){
        int ret=-1e9;
        tomax(ret,T.Query(1,ID[x],1,ID[x],RT[x]));
        for(int i=fa[x],d=Dep[fa[x]];i;i=fa[i],d--){
            int l=L[belong[x][d]][d],r=R[belong[x][d]][d];
             
             
            int res=T.Query(1,ID[i],L[x][d],L[x][d],RT[i])-A[i];
             
            if(l!=1)tomax(ret,T.Query(1,ID[i],1,l-1,RT[i])+res);
            if(r!=ID[i])tomax(ret,T.Query(1,ID[i],r+1,ID[i],RT[i])+res);
             
        }
        return ret;
    }
    void solve(){
        Solve(0,1,0);
        while(scanf("%s",Op)&&Op[0]!='D'){
            int u,to;
            scanf("%d",&u);
            if(Op[0]=='C'){
                scanf("%d",&to);
                Update(u,to);
            }else printf("%d\n",Ask(u));
        }
    }
}p2;
bool MM2;
int main(){
//  int size = 32 << 20; // 32MB
//  char *psdaasd = (char*)malloc(size) + size;
//  __asm__("movl %0, %%esp\n" :: "r"(psdaasd));
//  printf("%lf\n",(&MM2-&MM1)/1024.0/1024.0);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    for(int a,b,i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        link(a,b),link(b,a);
    }
    if(n<=1000)p1.solve();
    else p2.solve();
    return 0;
}
