#include<bits/stdc++.h>
#define M 305
using namespace std;
const int inf=1e9;
int n,m,K,s,t,tt=1,h[M];
int dis[M][M];
void Floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                if(k<=j&&dis[i][k]+dis[k][j]<dis[i][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                dis[j][i]=dis[i][j];
    }
}
struct edge{int nxt,to,co,fe;}G[M*M];
void Add(int a,int b,int c,int d){
    G[++tt]=(edge){h[a],b,c,d};h[a]=tt;
    G[++tt]=(edge){h[b],a,0,-d};h[b]=tt;
}
int ds[M],pre[M],mi[M];
bool vis[M];
queue<int>Q;
bool SPFA(){
    for(int i=s;i<=t;i++)
        vis[i]=0,ds[i]=inf;
    Q.push(s);vis[s]=1;ds[s]=0;mi[s]=inf;
    while(!Q.empty()){
        int x=Q.front();Q.pop();vis[x]=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co,fe=G[i].fe;
            if(ds[u]>ds[x]+fe&&c){
                ds[u]=ds[x]+fe;
                pre[u]=i;
                mi[u]=min(c,mi[x]);
                if(!vis[u]){
                    vis[u]=1;
                    Q.push(u);
                }
            }
        }
    }
    return ds[t]!=inf;
}
int ans=0,ans2=0;
void Update(){
    ans+=mi[t];
    ans2+=ds[t]*mi[t];
    int x=t;
    while(x!=s){
        int i=pre[x];
        G[i].co-=mi[t];
        G[i^1].co+=mi[t];
        x=G[i^1].to;
    }
}
int main(){
    // freopen("save.in","r",stdin);
    // freopen("save.out","w",stdout);
    memset(dis,0x3f,sizeof(dis));
    scanf("%d%d%d",&n,&m,&K);n++;
    for(int i=1;i<=n;i++)dis[i][i]=0;
    for(int i=1,a,b,c;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);a++;b++;
        if(a>b)swap(a,b);
        dis[a][b]=dis[b][a]=min(dis[a][b],c);
    } 
    Floyd();
    s=0,t=2*n+1;
    Add(s,1,K,0);
    for(int i=2;i<=n;i++){
        Add(s,i,1,0);
        Add(i+n,t,1,0);
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
		    if(dis[i][j]<1e9)
			    Add(i,j+n,1,dis[i][j]);
    while(SPFA())Update();
    printf("%d\n",ans2);
    return 0;
}