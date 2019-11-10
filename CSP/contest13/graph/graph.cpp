#include<stdio.h>
#include<algorithm>
#pragma GCC optimize(3)
#define M 100005
#define LL long long
using namespace std;

int n,m;
struct edge{
	int a,b;
	LL v;
}G[M*5];
int fa[M];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
bool mark[M*5];
LL ans=0;
int main(){
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++)
		scanf("%d%d%lld",&G[i].a,&G[i].b,&G[i].v);
	for(register int i=1;i<=m;i++)mark[i]=1;
	for(int j=63;j>=0;j--){
		for(register int i=1;i<=n;i++)fa[i]=i;
		for(register int i=1;i<=m;i++){
			if(!mark[i])continue;
			int a=G[i].a,b=G[i].b;
			LL v=G[i].v;
			if(v&1LL<<j)
				fa[getfa(a)]=getfa(b);
		}
		if(getfa(1)==getfa(n)){
			ans|=1LL<<j;
			for(register int i=1;i<=m;i++)
				if(mark[i]&&!(G[i].v&1LL<<j))mark[i]=0;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
