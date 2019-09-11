#include<bits/stdc++.h>
#define M 1005
using namespace std;
int n,m,h[M],tot,st,ed,deg[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
double dp[M][M];
bool vis[M][M][5];
struct node{
	int st,x,step;
};
queue<node>Q;
void Init_DP(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dp[i][j]=1e9; 
	for(int i=1;i<=n;i++)Q.push((node){i,i,0});
	while(!Q.empty()){
		node e=Q.front();Q.pop();
		if(e.step==3)continue;
		if(vis[e.st][e.x][e.step])continue;
		vis[e.st][e.x][e.step]=1;
		if(e.step==0)dp[e.st][e.x]=0;
		else dp[e.st][e.x]=min(dp[e.st][e.x],1.0);
		for(int i=h[e.x];i;i=G[i].nxt){
			int u=G[i].to;
			Q.push((node){e.st,u,e.step+1});
		}
	}
}
int dis[M][M];//两点间的最短距离
bool mark[M];
int nxt[M][M];//聪聪会走到哪去 
void Init_DS(){
	for(int i=1;i<=n;i++){	
		while(!Q.empty())Q.pop();
		for(int j=1;j<=n;j++)dis[i][j]=1e9,mark[j]=0;
		Q.push((node){0,i,0});
		while(!Q.empty()){
			node e=Q.front();Q.pop();
			if(mark[e.x])continue;
			mark[e.x]=1;
			dis[i][e.x]=e.step;
			for(int j=h[e.x];j;j=G[j].nxt){
				int u=G[j].to;
				Q.push((node){0,u,e.step+1});
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(dp[i][j]!=1e9)continue;
			int now=i,v=0;dis[0][j]=1e9;
			for(int k=h[now];k;k=G[k].nxt){
				int u=G[k].to;
				if(dis[u][j]<dis[v][j]||(dis[u][j]==dis[v][j]&&u<v))v=u;
			}
			now=v;
			for(int k=h[now];k;k=G[k].nxt){
				int u=G[k].to;
				if(dis[u][j]<dis[v][j]||(dis[u][j]==dis[v][j]&&u<v))v=u;
			}
			now=v;
			nxt[i][j]=now;
		}
}
double dfs(int stt,int edd){
	if(dp[stt][edd]!=1e9)return dp[stt][edd];
	double& res=dp[stt][edd];
	int u=nxt[stt][edd];
	res=1;
	double pp=1.0/(deg[edd]+1);
	res+=pp*dfs(u,edd);
	for(int i=h[edd];i;i=G[i].nxt){
		int nt=G[i].to;
		res+=pp*dfs(u,nt);
	}
	return res;
}
int main(){
	freopen("cchkk.in","r",stdin);
	freopen("cchkk.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&st,&ed);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		deg[a]++;deg[b]++;
	}
	Init_DP();
	Init_DS();
	printf("%.3lf\n",dfs(st,ed));
	return 0;
}
