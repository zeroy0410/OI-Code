#include<bits/stdc++.h>
using namespace std;
const int M=5e4+5,N=1e6+5;
int n,m,T;
int w[M],v[M];
int fa[M];
int gf(int v){
	return fa[v]==v?v:fa[v]=gf(fa[v]);
}
struct node{
	int w,v;
	bool operator <(const node &_)const{
		return v>_.v;
	}
}a[N];
int nxt[M];
int c1[M],c2[M];
bool check(int K){
	for(int i=1;i<=n+1;i++)fa[i]=i,c1[i]=0;
	for(int i=1;i<=m;i++)c2[i]=0;
	for(int j=1,i=1;i<=T;i++){
		int to=gf(nxt[i]);
		if(to!=n+1){
			c1[to]++;
			if(c1[to]==K)fa[to]=gf(to+1);
		}else {
			if(a[i].v>=v[j])return false;
			c2[j]++;
			if(c2[j]==K)j++;
			if(i!=T&&j==m+1)return false;
		}
	}
	return true;
}
int main(){
//	freopen("robots.in","r",stdin);
//	freopen("robots.out","w",stdout);
	scanf("%d%d%d",&n,&m,&T);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	sort(w+1,w+1+n);
	for(int i=1;i<=m;i++)scanf("%d",&v[i]);
	sort(v+1,v+1+m,greater<int>());
	for(int i=1;i<=T;i++)
		scanf("%d%d",&a[i].w,&a[i].v);
	sort(a+1,a+1+T);
	for(int i=1;i<=T;i++)
		nxt[i]=upper_bound(w+1,w+1+n,a[i].w)-w;
	int l=1,r=T,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}

