//By zcy
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)
const int M=5005;
int n;
int h[M],nx[M<<1],to[M<<1],v[M<<1],tot;
void add(int a,int b,int c){
	to[++tot]=b;v[tot]=c;
	nx[tot]=h[a];h[a]=tot;
}
struct Tree{
	int fa[M],val[M],mxdis,mndis,dis[M],id,no;
	void dfs(int x,int f,int d){
		fa[x]=f;
		dis[x]=max(dis[x],d);
		if(mxdis<d)mxdis=d,id=x;
		for(int i=h[x];i;i=nx[i])
			if(to[i]!=f&&to[i]!=no)dfs(to[i],x,d+(val[to[i]]=v[i]));
	}
	void solve(int s,int t){
		no=t;
		memset(dis,-1,sizeof(dis));
		mxdis=-1,dfs(s,0,0);
		mxdis=-1,dfs(id,0,0);
		mxdis=-1,dfs(id,0,0);
		mndis=1e9;
		for(int i=1;i<=n;i++)
			if(dis[i]!=-1)mndis=min(mndis,dis[i]);
	}
}A,B,C;
int main(){
	scanf("%d",&n);
	for(int a,b,c,i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
	}
	A.solve(1,0);
	int ans=1e9;
	for(int i=A.id;A.fa[i];i=A.fa[i]){
		B.solve(i,A.fa[i]);
		C.solve(A.fa[i],i);
		ans=min(ans,max(max(B.mxdis,C.mxdis),B.mndis+C.mndis+A.val[i]));
	}
	printf("%d\n",ans);
	return 0;
}
