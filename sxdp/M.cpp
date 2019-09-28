#include<cstdio>
#include<algorithm>
#define M 1005
using namespace std;
const int mod=1e9+7;
int n,K,h[M],tt,A[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
	}
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);

	return 0;
}
