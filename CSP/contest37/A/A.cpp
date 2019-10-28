#include<bits/stdc++.h>
#define M 400005
#define MM 1000005
#define LL long long
#pragma GCC optimize(3)
using namespace std;
int n,h[M],h2[M],tt,tt2;
struct Edge{
	int a,b,c;
}E[M];
struct edge{
	int nxt,to,co;
}G[M<<1],H[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
void Add2(int a,int b){
	H[++tt2]=(edge){h2[a],b};
	h2[a]=tt2;
}
vector<int>son[MM];
vector<int>wk[MM];
int Q[M<<1],qc,ans[M];
void Init(){
	int mx=0,t=0;
	for(int i=1;i<MM;i++){
		for(int j=i;j<MM;j+=i)
			son[j].push_back(i);
	}
}
int L[M],tot;
void dfs(int x,int f){
	L[x]=++tot;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
	}
}
bool vis[M];
int ed,mxdis;
void dfs_zj(int x,int f,int w){
	vis[x]=1;
	if(w>mxdis)mxdis=w,ed=x;
	for(int i=h2[x];i;i=H[i].nxt){
		int u=H[i].to;
		if(u==f)continue;
		dfs_zj(u,x,w+1);
	}
}
int main(){
//	freopen("walk.in","r",stdin);
//	freopen("walk.out","w",stdout);
	Init();
	scanf("%d",&n);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
		E[i].a=a;E[i].b=b;E[i].c=c;
		for(int j=0,e=son[c].size();j<e;j++){
			int u=son[c][j];
			wk[u].push_back(i);
		}
	}
	dfs(1,0);
	for(int i=MM-5;i>=1;i--){
		if((int)wk[i].size()==0)continue;
		qc=0;
		for(int j=0,e=wk[i].size();j<e;j++){
			int u=wk[i][j];
			Add2(E[u].a,E[u].b);Add2(E[u].b,E[u].a);
			Q[++qc]=E[u].a;Q[++qc]=E[u].b;
		}
		for(int j=1;j<=qc;j++){
			if(!vis[Q[j]]){
				ed=0;mxdis=-1;
				dfs_zj(Q[j],0,0);
				mxdis=-1;
				dfs_zj(ed,0,0);
				ans[mxdis]=max(ans[mxdis],i);
			}
		}
		for(int j=1;j<=qc;j++)
			vis[Q[j]]=0,h2[Q[j]]=0;
		tt2=0;
	}
	for(int i=n;i>=1;i--)
		ans[i]=max(ans[i+1],ans[i]);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
