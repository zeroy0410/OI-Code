#include<cstdio>
#include<algorithm>
#include<string.h>
#include<set>
#include<vector>
#define M 300005
using namespace std;
int n,m,A[M],h[M],dep[M],tt,ans;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
vector<int>wk[M];
multiset<int>S[M];
multiset<int>::iterator it;
void Init_dfs(int x,int f,int d){
	dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		Init_dfs(u,x,d+1);
	}
}
void dfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		if(S[u].size()>S[x].size())swap(S[u],S[x]);
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		for(it=S[u].begin();it!=S[u].end();it++)S[x].insert(*it);
		S[u].clear();
	}
	while(1){
		it=S[x].upper_bound(dep[x]);
		if(it==S[x].end())break;
		S[x].erase(it);
		ans++;
	}
	for(int i=0;i<wk[x].size();i++)S[x].insert(wk[x][i]);
	while(S[x].size()>A[x])S[x].erase(S[x].begin());
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	Init_dfs(1,0,0);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		if(dep[a]>dep[b])swap(a,b);
		wk[b].push_back(dep[a]);
	}
	dfs(1,0);
	printf("%d\n",ans+S[1].size());
	return 0;
}
