#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define M 2005
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
int n,m,q,h[M],tt,ck[M][M];
int inf;
struct edge{
    int nxt,to;
    int co;
}G[M*5];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
struct que{
    int a,b;
}QQ[M*3];
struct P100{
    queue<int>Q;
    int fa[M][11],dep[M];
    int dis[M],H[M],ans[M*3];
    bool vis[M];
    void SPFA(){
        while(!Q.empty())Q.pop();
        memset(H,0x3f,sizeof(H));
        memset(vis,0,sizeof(vis));
        Q.push(0);vis[0]=1;H[0]=0;
        while(!Q.empty()){
            int x=Q.front();Q.pop();vis[x]=0;
            for(int i=h[x];i;i=G[i].nxt){
                int u=G[i].to;
                int c=G[i].co;
                if(H[u]>H[x]+c){
                    H[u]=H[x]+c;
                    if(!vis[u]){
                        vis[u]=1;
                        Q.push(u);
                    }
                }
            }
        }
    }
    struct node{
    	int id;
    	int v;
    	bool operator < (const node& res)const{
    		return v>res.v;
    	}
    };
    __gnu_pbds::priority_queue<node>P;
    void Dij(int st){
	    while(!P.empty())P.pop();
        memset(dis,0x3f,sizeof(dis));inf=dis[0];
        memset(vis,0,sizeof(vis));
        P.push((node){st,0});dis[st]=0;
        while(!P.empty()){
            int x=P.top().id;P.pop();
            if(vis[x])continue;
            vis[x]=1;
            for(int i=h[x];i;i=G[i].nxt){
                int u=G[i].to;
                int c=G[i].co+H[x]-H[u];
                if(dis[u]>dis[x]+c){
                    dis[u]=dis[x]+c;
                    P.push((node){u,dis[u]});
                }
            }
        }
    }
    void dfs(int x,int f,int d){
        dep[x]=d;fa[x][0]=f;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to;
            int c=G[i].co+H[x]-H[u];
            if(dis[u]==dis[x]+c&&dep[u]==-1){
                dfs(u,x,d+1);
            }
        }
    }
    int LCA(int a,int b){
        if(dep[a]>dep[b])swap(a,b);
        int step=dep[b]-dep[a];
        for(int i=10;i>=0;i--){
            if(step&1<<i)b=fa[b][i];
        }
        if(a==b)return a;
        for(int i=10;i>=0;i--)
            if(fa[a][i]!=fa[b][i])
                a=fa[a][i],b=fa[b][i];
        return fa[a][0];
    }
    void Work(int x){
        memset(dep,-1,sizeof(dep));
        Dij(x);
        dfs(x,0,0);
        for(int j=1;j<=10;j++)
            for(int i=1;i<=n;i++)
                fa[i][j]=fa[fa[i][j-1]][j-1];
        for(int i=1;i<=q;i++){
            int a=QQ[i].a,b=QQ[i].b;
            if(dis[a]==inf||dis[b]==inf)continue;
            int lca=LCA(a,b);
            ans[i]=max(ans[i],dis[lca]+H[lca]-H[x]);
        }
    }
    void solve(){
    	for(int i=1;i<=n;i++)Add(0,i,0);
    	SPFA();
        for(int i=1;i<=q;i++)ans[i]=-1;
        for(int i=1;i<=n;i++)Work(i);
        for(int i=1;i<=q;i++)
            printf("%d\n",ans[i]);
     }
}p100;
int main(){
    scanf("%d%d%d",&n,&m,&q);
    memset(ck,0x3f,sizeof(ck));inf=ck[0][0];
    for(int i=1,a,b,c;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);
        if(a==b)continue;
        if(c<ck[a][b])ck[a][b]=c;
    }
    for(int i=1;i<=n;i++)
        for(int j=n;j>=1;j--)
            if(ck[i][j]!=inf)Add(i,j,ck[i][j]);
    for(int i=1;i<=q;i++)
        scanf("%d%d",&QQ[i].a,&QQ[i].b);
    p100.solve();
    return 0;
}