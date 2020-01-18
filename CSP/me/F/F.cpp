#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
int T,n,h[M],tt=1;
struct BIT{
	int C[M<<1];
	void clear(){ memset(C,0,sizeof(C)); }
	void add(int x,int d){
		x++;
		while(x<=2*n+1){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	int sum(int x){
		if(x<=0)return 0;
		x++;int res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int sz[M],son[M],rt=0,sdd[M],cnt[M],su,sv,L[M],R[M],tot;
void dfs_Init(int x,int f){
	sz[x]=1;son[x]=0;L[x]=++tot;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_Init(u,x);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
	int mx=max(sz[son[x]],n-sz[x]);
	if(mx*2<=n&&rt==0)rt=x;
	R[x]=tot;
}
void dfs_pre(int x,int f){
	if(x!=rt)Tr.add(sz[x],1);
	int pr=Tr.sum(n-2*sz[son[x]])-Tr.sum(n-2*sz[x]);
	if(L[x]>L[su]&&L[x]<=R[su])cnt[rt]+=(sz[x]<=n-2*sz[sv]);
	else cnt[rt]+=(sz[x]<=n-2*sz[su]);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_pre(u,x);
	}
	int nt=Tr.sum(n-2*sz[son[x]])-Tr.sum(n-2*sz[x]);
	sdd[x]=nt-pr;
}
void dfs_solve(int x,int f){
	if(x!=rt){
		Tr.add(sz[x],-1);Tr.add(n-sz[x],1);
		cnt[x]=Tr.sum(n-2*sz[son[x]])-Tr.sum(n-2*sz[x])-sdd[x];
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_solve(u,x);
	}
	if(x!=rt){ Tr.add(sz[x],1);Tr.add(n-sz[x],-1);}
}
int main(){
//	freopen("centroid.in", "r", stdin);
//	freopen("centroid.out", "w", stdout);
	scanf("%d",&T);
	while(T--){
		memset(h,0,sizeof(h));tt=1;
		Tr.clear();rt=su=sv=0;
		scanf("%d",&n);
		for(int i=1,a,b;i<n;i++){
			scanf("%d%d",&a,&b);
			Add(a,b);Add(b,a);
		}
		dfs_Init(1,0);tot=0;dfs_Init(rt,0);
		for(int i=h[rt];i;i=G[i].nxt){
			int u=G[i].to;
			if(sz[u]>sz[su]){sv=su;su=u;}
			else if(sz[u]>sz[sv])sv=u;
		}
		dfs_pre(rt,0);dfs_solve(rt,0);
		LL ans=0;
		for(int i=1;i<=n;i++)
			ans+=1LL*cnt[i]*i;
		printf("%lld",ans);
	}
	return 0;
}
