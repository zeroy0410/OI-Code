#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int sz[M],son[M],top[M],dep[M],fa[M];
void dfs(int x,int f,int d){
	sz[x]=1;son[x]=0;dep[x]=d;fa[x]=f;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==son[x]||u==fa[x])continue;
		dfs_top(u,u);
	}
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
int dis(int u,int v){
	return dep[u]+dep[v]-2*dep[LCA(u,v)];
}
struct node{ int u,v; };
vector<node>wk[M];
node now[M];
int Fa[M],ans[M],Dep[M],Top;
int getfa(int x){return Fa[x]==x?x:getfa(Fa[x]);}
void Insert(int p,int L,int R,int l,int r,int u,int v){
	if(l<=L&&r>=R){
		wk[p].push_back((node){u,v});
		return;
	}
	int mid=(L+R)>>1;
	if(l<=mid)Insert(p<<1,L,mid,l,r,u,v);
	if(r>mid)Insert(p<<1|1,mid+1,R,l,r,u,v);
}
int t[5];
struct STK{
	int u,v,c;node tt;
}stk[M];
void merge(int u,int v,int &res){
	u=getfa(u),v=getfa(v);
	t[0]=now[u].u;t[1]=now[u].v;t[2]=now[v].u;t[3]=now[v].v;
	int tmp=-1;node tt;
	for(int i=0;i<4;i++){
		for(int j=i+1;j<4;j++){
			if(dis(t[i],t[j])>tmp){
				tmp=dis(t[i],t[j]);
				tt=(node){t[i],t[j]};
			}
		}
	}
	if(tmp>res)res=tmp;
	if(Dep[u]<Dep[v])swap(Dep[u],Dep[v]);
	stk[++Top]=(STK){u,v,0,now[u]};
	if(Dep[u]==Dep[v])++Dep[u],stk[Top].c=1;
	Fa[v]=u;now[u]=tt;
}
void del(int x){
    while(Top>x){
        Dep[stk[Top].u]-=stk[Top].c,Fa[stk[Top].v]=stk[Top].v;
        now[stk[Top].u]=stk[Top].tt,Top--;
    }
}
void Work(int p,int l,int r,int res){
	int tmp=Top;
	for(int i=0;i<wk[p].size();i++){
		merge(wk[p][i].u,wk[p][i].v,res);
	}
	if(l==r)ans[l]=res;
	else {
		int mid=(l+r)>>1;
		Work(p<<1,l,mid,res);
		Work(p<<1|1,mid+1,r,res);
	}
	del(tmp);
}
int main(){
	freopen("speed.in","r",stdin);
	freopen("speed.out","w",stdout);
	scanf("%d%d",&n,&m);Top=0;
	for(int i=1,u,v,l,r;i<n;i++){
		scanf("%d%d%d%d",&u,&v,&l,&r);
		Add(u,v);Add(v,u);
		Insert(1,1,n,l,r,u,v);
	}
	dfs(1,0,0);dfs_top(1,1);
	for(int i=1;i<=n;i++){Fa[i]=i;now[i]=(node){i,i};}
	Work(1,1,n,0);
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
