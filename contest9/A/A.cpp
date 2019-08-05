#include<bits/stdc++.h>
#define M 300005
using namespace std;
//model 1
struct Graph{
	int h[M],tot;
	struct edge{
		int nxt,to;
	}G[M<<1];
	void Add(int a,int b){
		G[++tot]=(edge){h[a],b};
		h[a]=tot;
	}
}G1,G2;
int fa[M][20],L[M],R[M],ln[M],tt,dep[M],sz[M];
void dfs(int x,int f,int d){
	fa[x][0]=f;L[x]=++tt;ln[tt]=x;dep[x]=d;sz[x]=1;
	for(int j=1;j<20;j++)
		fa[x][j]=fa[fa[x][j-1]][j-1];
	for(int i=G1.h[x];i;i=G1.G[i].nxt){
		int u=G1.G[i].to;
		if(u==f)continue;
		dfs(u,x,d+1);
		sz[x]+=sz[u];
	}
	R[x]=tt;
}
int Up(int x,int step){
	for(int i=19;i>=0;i--)
		if(step&1<<i)x=fa[x][i];
	return x;
}
int LCA(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	b=Up(b,dep[b]-dep[a]);
	if(a==b)return a;
	for(int i=19;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return fa[a][0];
}
//model 2
int n,m,q,lm,A[M],mp[M],stk[M],top;
bool hav_1;
int ans[M];
void build(){
	if(!hav_1)A[++m]=1;
	sort(A+1,A+m+1);top=0;
	for(int i=1;i<m;i++)
		A[++m]=LCA(A[i],A[i+1]);
	sort(A+1,A+m+1);
	m=unique(A+1,A+m+1)-A-1;
	stk[++top]=A[1];
	for(int i=2;i<=m;i++){
		int x=A[i];
		while(top){
			if(L[x]>=L[stk[top]]&&L[x]<=R[stk[top]]){
				G2.Add(stk[top],x);
				break;
			}
			top--;
		}
		if(stk[top]!=x)stk[++top]=x;
	}
}
void redfs(int x){
	for(int i=G2.h[x];i;i=G2.G[i].nxt){
		int u=G2.G[i].to;
		 
int main(){
//	freopen("worldtree.in","r",stdin);
//	freopen("worldtree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		G1.Add(a,b);G1.Add(b,a);
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d",&m);hav_1=0;
		lm=m;
		for(int i=1;i<=m;i++){
			scanf("%d",&A[i]);
			mp[A[i]]=i;
			if(A[i]==1)hav_1=1;
		}
		build();
	return 0;
}
