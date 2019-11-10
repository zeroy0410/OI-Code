#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<iostream>
#pragma GCC optimize(3)
#define M 600005
#define LL long long
const double esp=1e-7;
using namespace std;
void read(int &x){
	static char c;
	x=0;
	int f=1;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
	do x=(x<<3)+(x<<1)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	x*=f;
}
int n,m,A[M],fa[M],id;
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
struct Edge{
	int a,b,v;
	bool operator < (const Edge& res)const{
		return v>res.v;
	}
}E[M];
struct node{
	LL x,y;
	bool operator < (const node& res)const{
		if(x!=res.x)return x<res.x;
		return y>res.y;
	}
}B[M];
bool check(node &a,node &b,node &c){return 1.0*(c.y-a.y)/(c.x-a.x)>=1.0*(a.y-b.y)/(a.x-b.x);}
LL calc(node &a,LL k){return a.x*k+a.y;}
int h[M],tot;
struct edge{int nxt,to;}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
int sz[M],son[M],dep[M],Fa[M],top[M],ID,dfn[M],sq;
LL sum[M];
void dfs_init(int x,int f,int d){
	Fa[x]=f;dep[x]=d;sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs_init(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;dfn[x]=++ID;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==Fa[x]||u==son[x])continue;
		dfs_top(u,u);
	}
}
#define SQ 10005
node Q[SQ][M/SQ];
int S[SQ],T[SQ],Top[SQ];
LL lzy[SQ];
node tmp[SQ];
int nc;
LL nowans[SQ];
LL query(int x,LL k){
	int L=1,R=Top[x]-1,ans=Top[x];
	while(L<=R){
		int mid=(L+R)>>1;
		if(calc(Q[x][mid],k)>=calc(Q[x][mid+1],k)){
			ans=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	return calc(Q[x][ans],k);
}
void down(int x){
	if(lzy[x]==0)return;
	for(int i=S[x];i<=T[x];i++)
		B[i].y+=lzy[x]*B[i].x;
	lzy[x]=0;
}
void rebuild(int x){
	nc=0;down(x);
	for(int i=S[x];i<=T[x];i++)tmp[++nc]=B[i];
	sort(tmp+1,tmp+nc+1);
	Top[x]=0;
	for(int i=1;i<=nc;i++){
		if(i>1&&tmp[i].x==tmp[i-1].x)continue;
		while(Top[x]>=2&&check(Q[x][Top[x]],Q[x][Top[x]-1],tmp[i]))Top[x]--;
		Q[x][++Top[x]]=tmp[i];
	}
	nowans[x]=query(x,0);
}
void Update(int L,int R,LL k){
	int lk=L/sq,rk=R/sq;
	if(lk==rk){
		down(lk);
		for(int i=L;i<=R;i++)B[i].y+=B[i].x*k;
		rebuild(lk);
		return;
	}
	down(lk);down(rk);
	for(int i=L;i/sq==lk;i++)B[i].y+=B[i].x*k;
	for(int i=R;i/sq==rk;i--)B[i].y+=B[i].x*k;
	for(int i=lk+1;i<rk;i++)lzy[i]+=k,nowans[i]=query(i,lzy[i]);
	rebuild(lk);rebuild(rk);
}
void update(int x,LL d){
	LL del=d-A[x];
	for(int u=x;u;u=Fa[top[u]]){
		int t=top[u];
		Update(dfn[t],dfn[u],del);
	}
	A[x]=d;
}
LL query_ans(){
	LL ans=0;
	for(int i=0;i<=tot/sq;i++)ans=max(ans,nowans[i]);
	return ans;
}
void Init(){
	for(int i=1;i<=tot;i++)
		sum[i]=A[i],fa[i]=i;
	int tt=n;
	for(int i=1;i<n;i++){
		int a=getfa(E[i].a),b=getfa(E[i].b);
		++tt;
		fa[a]=fa[b]=tt;sum[tt]=sum[a]+sum[b];
		B[dfn[tt]]=(node){E[i].v,E[i].v*sum[tt]};
	}
	for(int i=0;i<=tt/sq;i++)S[i]=max(1,i*sq),T[i]=min(tt,i*sq+sq-1),rebuild(i);
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)read(A[i]);
	for(int i=1;i<n;i++)
		read(E[i].a),read(E[i].b),read(E[i].v);
	sort(E+1,E+n);id=n;
	for(int i=1;i<=n*2;i++)fa[i]=i;
	for(int i=1;i<n;i++){
		int a=getfa(E[i].a),b=getfa(E[i].b);
		++id;
		fa[a]=id;fa[b]=id;
		Add(id,a);Add(id,b);
	}
	sq=sqrt(id+0.5)*0.2+1;
	dfs_init(id,0,0);
	dfs_top(id,id);
	Init();
	while(m--){
		int u,v;
		read(u);read(v);
		update(u,v);
		printf("%lld\n",query_ans());
	}
	return 0;
}
