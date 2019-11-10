#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const int mod=1e9+7;
int T,n,m,h[M],tt;
LL X;
struct edge{
	int a,b;
	LL v;
	bool operator < (const edge& res)const{
		return v<res.v;
	}
}E[M<<1];
struct node{
	int nxt,to;
	LL co;
}G[M<<1];
void Add(int a,int b,LL c){
	G[++tt]=(node){h[a],b,c};
	h[a]=tt;
}
bool vis[M<<1];
int fa[M];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int Fa[M],dep[M],sz[M],son[M],top[M],ID[M],tot,ln[M];
LL val[M];
void dfs(int x,int f,int d){
	Fa[x]=f;dep[x]=d;sz[x]=1;son[x]=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;LL v=G[i].co;
		if(u==f)continue;
		val[u]=v;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;ID[x]=++tot;ln[tot]=x;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==son[x]||u==Fa[x])continue;
		dfs_top(u,u);
	}
}
int LCA(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]])a=Fa[top[a]];
		else b=Fa[top[b]];
	}
	return dep[a]>dep[b]?b:a;
}
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
struct YD{
	struct YD_t{
		int l,r;
		LL mx;
	}tree[M<<2];
#define ff tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
	void up(int p){
		ff.mx=max(lson.mx,rson.mx);
	}
	void build(int l,int r,int p){
		ff.l=l;ff.r=r;
		if(l==r){
			ff.mx=val[ln[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		up(p);
	}
	LL query(int l,int r,int p){
		if(l>r)return -1;
		if(ff.l==l&&ff.r==r)return ff.mx;
		int mid=(ff.l+ff.r)>>1;
		if(r<=mid)return query(l,r,p<<1);
		else if(l>mid)return query(l,r,p<<1|1);
		return max(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
	}
}Tr;
LL Query(int u,int v){
	LL res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			res=max(res,Tr.query(ID[top[u]],ID[u],1));
			u=Fa[top[u]];
		}
		else {
			res=max(res,Tr.query(ID[top[v]],ID[v],1));
			v=Fa[top[v]];
		}
	} 
	if(dep[u]>dep[v])res=max(res,Tr.query(ID[v]+1,ID[u],1));
	else res=max(res,Tr.query(ID[u]+1,ID[v],1));
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		memset(fa,0,sizeof(fa));
		memset(Fa,0,sizeof(Fa));
		memset(vis,0,sizeof(vis));
		memset(dep,0,sizeof(dep));
		memset(h,0,sizeof(h));tt=tot=0;
		scanf("%d%d%lld",&n,&m,&X);
		for(int i=1;i<=m;i++)
			scanf("%d%d%lld",&E[i].a,&E[i].b,&E[i].v);
		for(int i=1;i<=n;i++)fa[i]=i;
		sort(E+1,E+m+1);
		LL res=0;
		for(int i=1;i<=m;i++){
			int a=E[i].a,b=E[i].b;
			LL v=E[i].v;
			int r1=getfa(a),r2=getfa(b);
			if(r1!=r2){
				res+=v;
				vis[i]=1;
				fa[r1]=r2;
				Add(a,b,v);Add(b,a,v);
			}
		}
		if(res>X){puts("0");continue;}
		dfs(1,0,0);
		dfs_top(1,1);int c1=0,c2=0;
		Tr.build(1,n,1);
		for(int i=1;i<=m;i++){
			if(!vis[i]){
				int a=E[i].a,b=E[i].b;
				int lca=LCA(a,b);
				LL mx=0;
				mx=max(mx,Query(a,lca));
				mx=max(mx,Query(b,lca));
				LL tmp=res+E[i].v-mx;
				if(tmp==X)c1++;
				else if(tmp<X)c2++;
			}
		}
		LL ans;
		if(res==X)ans=((qkpow(2,m)-2*qkpow(2,m-(n-1)-c1)%mod)%mod+mod)%mod;
		else ans=(2*(((qkpow(2,m-(n-1)-c2)-qkpow(2,m-(n-1)-c1-c2))%mod+mod)%mod)%mod+mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
