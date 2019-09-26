#include<stdio.h>
#include<algorithm>
#define M 20005
using namespace std;
int n,m,A,B,Q,h[M],tt;
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
	scanf("%d%d%d%d%d",&n,&m,&A,&B,&Q);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);
	}
	return 0;
}
