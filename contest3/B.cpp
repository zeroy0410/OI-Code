#include<bits/stdc++.h>
#define M 70005
using namespace std;
int n,K,h[M],tot;
struct edge{
	int nxt,to,id;	
}G[M<<1];
void Add(int a,int b,int id){
	G[++tot]=(edge){h[a],b,id};
	h[a]=tot;
}
struct node{
	int l,r,mx,mi;
}tree[M<<2];
struct YD_tree{
	#define fa tree[p]
	#define lson tree[p<<1]
	#define rson tree[p<<1|1]
	void build(int l,int r,int p){
		fa.l=l;fa.r=r;fa.mx=1e9+7;fa.mi=-1e9-7;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
	}
	void down(int p){
		lson.mx=min(lson.mx,fa.mx);
		rson.mx=min(rson.mx,fa.mx);
		lson.mi=max(lson.mi,fa.mi);
		rson.mi=max(rson.mi,fa.mi);	
	}
	void update(int l,int r,int d,bool f,int p){
		if(l>r)return;
		if(fa.l==l&&fa.r==r){
			if(f)fa.mx=min(fa.mx,d);
			else fa.mi=max(fa.mi,d);
			return;	
		}
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(r<=mid)update(l,r,d,f,p<<1);
		else if(l>mid)update(l,r,d,f,p<<1|1);
		else {
			update(l,mid,d,f,p<<1);
			update(mid+1,r,d,f,p<<1|1);
		}
	}
	node query(int x,int p){
		if(fa.l==x&&fa.r==x)return fa;
		down(p);
		int mid=(fa.l+fa.r)>>1;
		if(x<=mid)return query(x,p<<1);
		else return query(x,p<<1|1);
	}
	#undef fa
	#undef lson
	#undef rson
}Tr;
int fa[M],son[M],top[M],sz[M],id[M],mp[M],ln[M],dep[M],tt;
void dfs(int x,int f,int d){
	fa[x]=f;son[x]=0;sz[x]=1;dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		mp[u]=G[i].id;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
		if(sz[u]>sz[son[x]])son[x]=u;
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;id[x]=++tt;ln[tt]=x;
	if(son[x])dfs_top(son[x],tp);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==fa[x]||u==son[x])continue;
		dfs_top(u,u);	
	}
}
char S[15];
int aa[M],bb[M];
bool vis[M];
int mk[M],mpp[M];
vector<int>GG[M];
vector<int>re; 
bool sp(int x){
	for(int i=0;i<GG[x].size();i++){
		int u=GG[x][i];
		if(!vis[u]){
			vis[u]=1;
			re.push_back(u);
			if(!mk[u]||sp(mk[u])){
				mk[u]=x;mpp[x]=u;
				return 1;
			}
		}
	}
	return 0;
}
void match(){
	for(int i=2;i<=n;i++){
		for(int j=0;j<re.size();j++)vis[re[j]]=0;
		re.clear();sp(i);
	}
}
int hs[M];
int main(){
//	freopen("minmaxtree.in","r",stdin);
//	freopen("minmaxtree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&aa[i],&bb[i]);
		Add(aa[i],bb[i],i);Add(bb[i],aa[i],i);
	}
	dfs(1,0,0);
	dfs_top(1,1);
	Tr.build(1,n,1);
	scanf("%d",&K);
	for(int i=1,u,v,d;i<=K;i++){
		scanf("%s%d%d%d",S+1,&u,&v,&d);hs[i]=d;
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
//				if(i==3)cout<<"haha: "<<top[u]<<' '<<u<<endl;
				Tr.update(id[top[u]],id[u],d,S[1]=='M',1);
				u=fa[top[u]];
			}
			else {
//				if(i==3)cout<<"haha: "<<top[v]<<' '<<v<<endl;
				Tr.update(id[top[v]],id[v],d,S[1]=='M',1);
				v=fa[top[v]];
			}
		}
		if(dep[u]>dep[v]){/*if(i==3)cout<<son[v]<<' '<<u<<endl;*/Tr.update(id[son[v]],id[u],d,S[1]=='M',1);}
		else {/*if(i==3)cout<<son[u]<<' '<<v<<endl;*/Tr.update(id[son[u]],id[v],d,S[1]=='M',1);}
	}
	sort(hs+1,hs+K+1);
	for(int i=2;i<=n;i++){
		node e=Tr.query(id[i],1);
//		cout<<i<<' '<<e.mx<<' '<<e.mi<<endl;
		if(e.mx!=1e9+7){
			int l=lower_bound(hs+1,hs+K+1,e.mx)-hs;
			GG[i].push_back(l);	
		}
		if(e.mi!=-1e9-7){
			int l=lower_bound(hs+1,hs+K+1,e.mi)-hs;
			GG[i].push_back(l);
		}
	}
	match();
	for(int i=2;i<=n;i++){
		if(mpp[i]==0){
			node e=Tr.query(id[i],1);
			printf("%d %d %d\n",aa[mp[i]],bb[mp[i]],(e.mx+e.mi)/2);
		}
		else printf("%d %d %d\n",aa[mp[i]],bb[mp[i]],hs[mpp[i]]);
			
	} 
	return 0;
}
