#include<bits/stdc++.h>
#define M 200005
using namespace std;
int h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int n,m,dep[M],son[M],col[M],len[M],ans[M];
int st,ed,mxdis;
void dfs_ZJ(int x,int f,int w){
	if(w>mxdis){
		mxdis=w;
		ed=x;
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_ZJ(u,x,w+1);
	}
}
void dfs_Len(int x,int f,int d){
	dep[x]=d;son[x]=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_Len(u,x,d+1);
		if(len[u]>len[son[x]])son[x]=u;
	}
	len[x]=len[son[x]]+1;
}

int stk[M],sum,cnt[M],top;
void Push(int x){
	stk[++top]=x;
	cnt[col[x]]++;
	sum+=(cnt[col[x]]==1);
}
void Pop(){
	int x=stk[top];top--;
	sum-=(cnt[col[x]]==1);
	cnt[col[x]]--;
}

void dfs_Solve(int x,int f){
	if(son[x]==0){ans[x]=max(ans[x],sum);return;}
	int mx=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f||u==son[x])continue;
		mx=max(mx,len[u]);
	}
	while(top&&mx>=dep[x]-dep[stk[top]])Pop();Push(x);
	dfs_Solve(son[x],x);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f||u==son[x])continue;
		while(top&&len[son[x]]>=dep[x]-dep[stk[top]])Pop();
		Push(x);
		dfs_Solve(u,x);
	}
	while(top&&len[son[x]]>=dep[x]-dep[stk[top]])Pop();
	ans[x]=max(ans[x],sum);
}

int main(){
//	freopen("city.in","r",stdin);
//	freopen("city.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=n;i++)scanf("%d",&col[i]);mxdis=-1e9;
	dfs_ZJ(1,0,0);st=ed;mxdis=-1e9;
	dfs_ZJ(st,0,0);
	dfs_Len(st,0,0);dfs_Solve(st,0);
	dfs_Len(ed,0,0);dfs_Solve(ed,0);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
