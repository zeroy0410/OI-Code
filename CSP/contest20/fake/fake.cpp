#include<cstdio>
#include<algorithm>
#include<string.h>
#define M 300005
using namespace std;
int n,m,A[M],h[M],tt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct node{int a,b;}F[M];
void dfs(int x,int f){

}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}
	for(int i=1;i<=m;i++)
		scanf("%d%d",&F[i].a,&F[i].b);

	return 0;
}
