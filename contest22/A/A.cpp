#include<bits/stdc++.h>
#define M 255
#define LL long long
using namespace std;
const int inf=1e9;
bool mm1;
int n,m,C[M];
int A[M][M];
vector<int>T[M],W[M];
struct P30{
    struct node{
        int x;
        bool operator < (const node& res)const{
            return W[x][0]<W[res.x][0];
        }
    }Q[M];
    bool mark[M];
    void solve(){
        for(int i=1;i<=m;i++)Q[i].x=i;
        sort(Q+1,Q+m+1);
        LL ans=0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(A[Q[i].x][j]){
                    if(!mark[j]){
                        mark[j]=1;
                        ans+=1LL*C[j]*W[Q[i].x][0];
                    }
                }
            }
        }
        printf("%lld\n",ans);
    }
}p30;
struct P0{
    int h[M*M*10],tt;
    struct edge{
        int nxt,to;
        LL co,fe;
    }G[M*M*10];
    void Add(int a,int b,int c,int d){
        G[++tt]=(edge){h[a],b,c,d};
        h[a]=tt;
        G[++tt]=(edge){h[b],a,0,-d};
        h[b]=tt;
    }
    LL dis[M*M*10],mi[M*M*10];
    int s,t,tot,pre[M*M*10];
    bool vis[M*M*10];
    queue<int>Q;
    bool SPFA(){
        for(int i=s;i<=t;i++)
            vis[i]=0,dis[i]=inf;
        Q.push(s);vis[s]=1;dis[s]=0;mi[s]=inf;
        while(!Q.empty()){
            int x=Q.front();Q.pop();vis[x]=0;
            for(int i=h[x];i;i=G[i].nxt){
                int u=G[i].to;
                LL c=G[i].co,fe=G[i].fe;
                if(dis[u]>dis[x]+fe&&c){
                    dis[u]=dis[x]+fe;
                    mi[u]=min(c,mi[x]);
                    pre[u]=i;
                    if(!vis[u]){
                        vis[u]=1;
                        Q.push(u);
                    }
                }
            }
        }
        return dis[t]!=inf;
    }
    LL ans=0,ans2=0;
    void Update(){
        ans+=mi[t];
        ans2+=dis[t]*mi[t];
        int x=t;
        while(x!=s){
            int i=pre[x];
            G[i].co-=mi[t];
            G[i^1].co+=mi[t];
            x=G[i^1].to;
        }
    }
    void EK(){
        while(SPFA())Update();
    }
    void solve(){
        tt=1;s=0;
        for(int i=1;i<=n;i++){Add(s,i,C[i],0);}tot=n;
        for(int i=1;i<=m;i++){
            for(int k=0;k<T[i].size()-1;k++){
                tot++;
                int tmp=T[i][k+1]-T[i][k];
                for(int j=1;j<=n;j++){
                    if(A[i][j])
                        Add(j,tot,inf,0);
                }
                tot++;
                Add(tot-1,tot,tmp,W[i][k]);
            }
        }
        t=tot+1;
        for(int i=n+2;i<=tot;i+=2)Add(i,t,inf,0);
        EK();
        printf("%lld\n",ans2);
    }
}p0;
bool mm2;
int main(){
    freopen("job.in","r",stdin);
    freopen("job.out","w",stdout);
    // printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)scanf("%d",&C[i]);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&A[i][j]);
    }
    bool fl1=1;
    for(int i=1,s;i<=m;i++){
        scanf("%d",&s);if(s!=0)fl1=0;
        T[i].push_back(0);
        for(int j=1,x;j<=s;j++){
            scanf("%d",&x);
            T[i].push_back(x);
        }
        T[i].push_back(inf);
        for(int j=1,x;j<=s+1;j++){
            scanf("%d",&x);
            W[i].push_back(x);
        }
    }
    if(fl1)p30.solve();
    else p0.solve();
    return 0;
}