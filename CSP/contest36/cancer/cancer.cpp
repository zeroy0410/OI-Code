#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,h[M],tt=1,in[M];
struct edge{
	int nxt,to;
}G[M<<1],H[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void Add2(int a,int b){
	
int dfn[M],low[M],ans,id;
bool mark[M];
void dfs(int x,int f){
	dfn[x]=low[x]=++id;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		if(!dfn[u]){
			dfs(u,x);
			low[x]=min(low[x],low[u]);
		}
		else low[x]=min(low[x],dfn[u]);
	}
	bool fl=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		if(dfn[u]<dfn[x])continue;
		if(low[u]==dfn[x])cout<<x<<' '<<u<<' '<<dfn[u]<<' '<<dfn[x]<<endl;
		if(low[u]>=dfn[x]){fl=0;break;}
	}
	if(fl&&m-in[x]==n-2)ans++,mark[x]=1;
}
int main(){
//	freopen("cancer.in","r",stdin);
//	freopen("cancer.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		in[a]++;in[b]++;
	}
	dfs(1,-1);
	if(!mark[1]&&m-in[1]==n-2)ans++,mark[1]=1;
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		if(mark[i])printf("%d ",i);
	puts("");
	return 0;
}
