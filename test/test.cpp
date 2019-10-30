#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n=10000,m,K,fa[M],h[M],tt;
bool vis[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
vector<int>lop;
int mi,mx;
void dfs(int x,int f){
	if(vis[x])return;
	vis[x]=1;mi=min(x,mi);mx=max(x,mx);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
	}
}
int R[M];
int main(){
	scanf("%d",&K);
	for(int i=1;i<=n;i++)R[i]=10001;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1,a,b;i<=K;i++){
		scanf("%d%d",&a,&b);
		if(getfa(a)==getfa(b))lop.push_back(a);
		else {
			Add(a,b);Add(b,a);
			fa[getfa(a)]=getfa(b);
		}
	}
	for(int i=0;i<lop.size();i++)dfs(lop[i],0);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			mi=1e9;mx=-1e9;
			dfs(i,0);
			R[mi]=min(R[mi],mx);
		}
	}
	for(int i=n-1;i>=1;i--)R[i]=min(R[i+1],R[i]);
	printf("%d\n",R[1]-1);
	return 0;
}
