#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,q,h[M],tt,rt;
bool ca[M];
struct YD_tree{
	struct YD{
		int l,r,mark,sum,len;
		void reset(){
			if(mark==0)sum=0;
			else sum=len;
		}
	}tree[M<<2];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void down(int p){
		if(fa.mark!=-1){
			lson.mark=fa.mark;
			rson.mark=fa.mark;
			lson.reset();rson.reset();
			fa.mark=-1;
		}
	}
	void up(int p){
		fa.sum=lson.sum+rson.sum;
	}
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.mark=-1;fa.sum=0;
		fa.len=r-l+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,int d,int p){
		if(fa.l==l&&fa.r==r){
			fa.mark=d;
			fa.reset();
			return;
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,d,p<<1);
		else if(l>mid)update(l,r,d,p<<1|1);
		else {
			update(l,mid,d,p<<1);
			update(mid+1,r,d,p<<1|1);
		}
		up(p);
	}
	int query(int l,int r,int p){
		if(fa.l==l&&fa.r==r)return fa.sum;
		int mid=(fa.l+fa.r)>>1;
		down(p);
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return query(l,mid,p<<1)+query(mid+1,r,p<<1|1);
	}
#undef fa
#undef lson
#undef rson
}Tr;
struct edge{
	int nxt,to;
}G[M];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int sz[M],son[M],top[M],L[M],R[M],tot,fa[M],dep[M];
void dfs(int x,int f,int d){
	son[x]=0;sz[x]=1;fa[x]=f;dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;L[x]=++tot;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==son[x])continue;
		dfs_top(u,u);
	}
	R[x]=tot;
}
int query(int u,int v){
	int sum=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			sum+=Tr.query(L[top[u]],L[u],1);
			u=fa[top[u]];
		}
		else {
			sum+=Tr.query(L[top[v]],L[v],1);
			v=fa[top[v]];
		}
	}
	if(dep[v]>=dep[u])sum+=Tr.query(L[u],L[v],1);
	else sum+=Tr.query(L[v],L[u],1);
	return sum;
}
void update(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			Tr.update(L[top[u]],L[u],1,1);
			u=fa[top[u]];
		}
		else {
			Tr.update(L[top[v]],L[v],1,1);
			v=fa[top[v]];
		}
	}
	if(dep[v]>=dep[u])Tr.update(L[u],L[v],1,1);
	else Tr.update(L[v],L[u],1,1);
}
char S[55];
int main(){
	freopen("manager.in","r",stdin);
	freopen("manager.out","w",stdout);
	scanf("%d",&n);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x);x++;
		Add(x,i);ca[i]=1;
	}
	for(int i=1;i<=n;i++)
		if(!ca[i]){rt=i;break;}
	dfs(rt,0,1);
	dfs_top(rt,rt);
	Tr.build(1,n,1);
	scanf("%d",&q);
	while(q--){
		int x;
		scanf("%s",S+1);
		if(S[1]=='i'){
			scanf("%d",&x);x++;
			printf("%d\n",dep[x]-query(rt,x));
			update(rt,x);
		}
		else {
			scanf("%d",&x);x++;
			printf("%d\n",Tr.query(L[x],R[x],1));
			Tr.update(L[x],R[x],0,1);
		}
	}
	return 0;
}
