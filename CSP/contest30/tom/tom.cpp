#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,A,B,h[M],tt,sz[M],L[M],R[M],tot,rt,op,q1,q2,in[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f){
	L[x]=++tot;sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		sz[x]+=sz[u];
	}
	if(sz[x]==A){
		op=1;
		rt=x;
	}
	else if(sz[x]==B){
		op=2;
		rt=x;
	}
	R[x]=tot;
}
queue<int>Q;
int ans[M];
int main(){
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		in[a]++;in[b]++;
	}
	op=-1;
	dfs(1,0);
	if(op==-1)puts("-1");
	else {
		for(int i=1;i<=n;i++)if(in[i]==1)Q.push(i);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			if(L[x]>=L[rt]&&L[x]<=R[rt]){
				if(op==1)ans[x]=++q1;
				else ans[x]=--q2;
			}
			else {
				if(op==1)ans[x]=--q2;
				else ans[x]=++q1;
			}
			for(int i=h[x];i;i=G[i].nxt){
				int u=G[i].to;
				in[u]--;
				if(in[u]==1)Q.push(u);
			}
		}
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
	}
	return 0;
}
