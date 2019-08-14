#include<bits/stdc++.h>
#define M 35
using namespace std;
int n,m,A[M][M],clo[M][M],h[M*M],tt=1,s,t,ans;
const int inf=1e9;
struct edge{
	int nxt,to,co;
}G[M*M*5];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int id(int x,int y){return (x-1)*m+y;}
int dxy[4][2]={1,0,0,1,-1,0,0,-1};
queue<int>Q;
bool vis[M*M];
int dep[M*M],cur[M*M];
bool bfs(){
    for(int i=1;i<=n*m+2;i++){
        vis[i]=0;dep[i]=inf;
        cur[i]=h[i];
    }
    dep[s]=0;Q.push(s);vis[s]=1;
    while(!Q.empty()){
        int e=Q.front();Q.pop();
        for(int i=h[e];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(vis[u]||!c)continue;
            dep[u]=dep[e]+1;
			vis[u]=1;
			Q.push(u);
        }
    }
    if(dep[t]!=inf)return 1;
    return 0;
}
int dfs(int x,int mi){
    int rlow=0;
    if(x==t){
        ans-=mi;
        return mi;
    }
    int used=0;
    for(int i=cur[x];i;i=G[i].nxt){
        cur[x]=i;
        int u=G[i].to,c=G[i].co;
        if(dep[u]!=dep[x]+1||!c)continue;
        if(rlow=dfs(u,min(mi-used,c))){
            used+=rlow;
            G[i].co-=rlow;
            G[i^1].co+=rlow;
            if(used==mi)break;
        }
    }
    return used;
}
void Dinic(){
    while(bfs())dfs(s,inf);
}
int main(){
	scanf("%d%d",&n,&m);
	s=n*m+1,t=n*m+2,ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&A[i][j]);ans+=A[i][j];
			if(j==1)clo[i][j]=!clo[i-1][j];
			else clo[i][j]=!clo[i][j-1];
			if(clo[i][j])Add(s,id(i,j),A[i][j]),Add(id(i,j),s,0);
			else {
                Add(id(i,j),t,A[i][j]),Add(t,id(i,j),0);
                for(int d=0;d<4;d++){
                    int x=i+dxy[d][0];
                    int y=j+dxy[d][1];
                    if(x>=1&&x<=n&&y>=1&&y<=m){
                        Add(id(x,y),id(i,j),inf);
                        Add(id(i,j),id(x,y),0);
                    }
                }
            }
		}
	}
	Dinic();
	printf("%d\n",ans);
	return 0;
}