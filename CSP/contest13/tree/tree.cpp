#include<stdio.h>
#include<algorithm>
#define LL long long
#define M 300005
using namespace std;
int n,m,A[M],fa[M];
LL sum[M];
struct edge{
	int a,b,v;
	bool operator < (const edge &res)const{
		return v<res.v;
	}
}G[M];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
struct P40{
	void solve(){
		LL ans=0;
		for(int i=1;i<=n;i++){fa[i]=i;sum[i]=A[i];}
		for(int i=n-1;i>=0;i--){
			int a=G[i].a,b=G[i].b,v=G[i].v;
			int rt1=getfa(a),rt2=getfa(b);
			if(rt1!=rt2){
				sum[rt2]+=sum[rt1];
				fa[rt1]=rt2;
			}
			ans=max(ans,v*sum[rt2]);
		}
		printf("%lld\n",ans);
	}
}p40;
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<n;i++)
		scanf("%d%d%d",&G[i].a,&G[i].b,&G[i].v);
	sort(G+1,G+n);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		A[x]=y;
		p40.solve();
	}
	return 0;
}
