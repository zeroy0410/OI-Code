#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,W,h[M],tt;
int fa[M];
LL val[M];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
struct edge{
	int a,b,c;
	bool operator < (const edge& res)const{
		return c<res.c;
	}
}G[M<<1];
int main(){
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++)fa[i]=i,val[i]=0;
	for(int i=2;i<=n;i++)scanf("%lld",&val[i]);
	for(int i=1,a,b,c;i<n;i++)
		scanf("%d%d%d",&G[i].a,&G[i].b,&G[i].c);
	sort(G+1,G+n);
	LL co=0;
	for(int i=1;i<n;i++){
		if(val[getfa(1)]>=W)break;
		co=G[i].c;
		int a=G[i].a,b=G[i].b;
		a=getfa(a);b=getfa(b);
		fa[b]=a;val[a]+=val[b];
	}
	printf("%lld\n",co);
	return 0;
}
