#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<set>
#include<vector>
#define LL long long
#define M 100005
#pragma GCC optimize(3)
#pragma GCC O("inline")
using namespace std;
int n,m,q,A[M],h[M],tot;
struct edge{int nxt,to;}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
struct xl{int a,b;}T[M];
int fa[M],dep[M],sz[M],son[M],ID[M],ln[M],top[M],tt;
LL sum[M];
struct node{
	int l,r,v;
	bool operator < (const node& res)const{
		if(l!=res.l)return l<res.l;
		if(r!=res.r)return r<res.r;
		return v<res.v;
	}
};
set<node>S;
set<node>::iterator it1,it2,tmp;
vector<node>wk2;
struct BIT{
	LL C[M];
	void add(int x,LL d){
		x++;
		while(x<=m+1){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	LL sum(int x){
		x++;LL res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
void dfs(int x,int f,int d){
	dep[x]=d;fa[x]=f;sz[x]=1;son[x]=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1); 
		if(sz[u]>sz[son[x]])son[x]=u;
		sz[x]+=sz[u];
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;ID[x]=++tt;ln[tt]=x;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==son[x]||u==fa[x])continue;
		dfs_top(u,u);
	}
}
void Insert(int l,int r,int v){
	Tr.add(v,sum[r]-sum[l-1]);
	S.insert((node){l,r,v});
}
struct wkq{int l,r,v;};
vector<wkq>wk;
void Update(int l,int r,int v){
	wk.clear();
	it1=S.lower_bound((node){l,0,0});
	if(it1!=S.begin())it1--;
	while(1){
		if(it1==S.end())break;
		node e=*(it1);
		if(e.l>=l&&e.r<=r){
			Tr.add(e.v,-(sum[e.r]-sum[e.l-1]));
			it2=it1++;if(it1==S.end()){S.erase(it2);break;}S.erase(it2);
		}
		else if((e.l<=l&&e.r>=l)||(e.l<=r&&e.r>=r)){
			Tr.add(e.v,-(sum[e.r]-sum[e.l-1]));
			if(e.l<l)wk.push_back((wkq){e.l,l-1,e.v});
			if(e.r>r)wk.push_back((wkq){r+1,e.r,e.v});
			it2=it1++;if(it1==S.end()){S.erase(it2);break;}S.erase(it2);
		}
		else if(e.l>r)break;
		else it1++;
	}
	wk.push_back((wkq){l,r,v});
	for(int i=0;i<wk.size();i++)
		Insert(wk[i].l,wk[i].r,wk[i].v);
}
void update(int u,int v,int c){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			Update(ID[top[u]],ID[u],c);
			u=fa[top[u]];
		}
		else {
			Update(ID[top[v]],ID[v],c);
			v=fa[top[v]];
		}
	} 
	if(dep[u]>dep[v])Update(ID[v],ID[u],c);
	else Update(ID[u],ID[v],c);
}
struct que{int id,l;};
vector<que>Q[M];
LL ans[M];
int main(){
	scanf("%d%d%d",&n,&m,&q);S.clear();
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=m;i++)
		scanf("%d%d",&T[i].a,&T[i].b);
	dfs(1,0,0);dfs_top(1,1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[ln[i]];
	S.insert((node){1,n,0});Tr.add(0,sum[n]);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		Q[r].push_back((que){i,l});
	}
	for(int i=1;i<=m;i++){
		update(T[i].a,T[i].b,i);
		for(int j=0;j<Q[i].size();j++){
			int l=Q[i][j].l,id=Q[i][j].id;
			ans[id]=Tr.sum(i)-Tr.sum(l-1);
		}
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
