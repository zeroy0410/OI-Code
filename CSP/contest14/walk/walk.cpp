#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<vector>
#pragma GCC optimize(3)
#define M 200005
using namespace std;
int n,m,A[M],dis[M];
vector<int>G[M],T[1<<20];
queue<int>Q;
bool vis[1<<20],mark[1<<20];
void dfs(int x,int v){
	if(mark[x])return;
	mark[x]=1;
	for(int i=0;i<T[x].size();i++){
		int u=T[x][i];
		if(!vis[u]){
			vis[u]=1;
			dis[u]=v+1;
			Q.push(u);
		}
	}
	for(int i=0;i<20;i++)if(x&1<<i)dfs(x^(1<<i),v);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		T[A[i]].push_back(i);
	}
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
	}
	memset(dis,-1,sizeof(dis));
	Q.push(1);dis[1]=0;vis[1]=1;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=0;i<G[x].size();i++){
			int u=G[x][i];
			if(!vis[u]){
				vis[u]=1;
				dis[u]=dis[x]+1;
				Q.push(u);
			}
		}
		dfs(A[x],dis[x]);
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",dis[i]);
	return 0;
}
