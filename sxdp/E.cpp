#include<stdio.h>
#include<string.h>
#include<algorithm>
#define M 100005
using namespace std;
int n,m,h[M],tt=1;
struct edge{int nxt,to;}G[M<<2];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int ret[2][M],dep[M],tot[2];
void dfs(int x,int d,int id){
	dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(i==(id^1))continue;
		if(dep[u]!=-1){
			if(dep[u]>dep[x])continue;
			ret[~(dep[x]-dep[u])&1][x]++;
			ret[~(dep[x]-dep[u])&1][u]--;
			tot[~(dep[x]-dep[u])&1]++;
		}
		else dfs(u,d+1,i);
	}
}
bool vis[M];
int ans,rt;
void redfs(int x){
	vis[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(vis[u])continue;
		redfs(u);
		ret[0][x]+=ret[0][u];
		ret[1][x]+=ret[1][u];
	}
}
int main(){
	memset(dep,-1,sizeof(dep));
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=n;i++){
		if(dep[i]==-1){
			rt=i;
			dfs(i,0,-1);
			redfs(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(dep[i]!=0&&ret[1][i]==tot[1]&&!ret[0][i])ans++;
	}
	if(tot[1]==1)ans++;
	printf("%d\n",ans);
	return 0;
}
