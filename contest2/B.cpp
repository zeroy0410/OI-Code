#include <bits/stdc++.h>
#define M 200005
#define LL long long
using namespace std;
const int inf=1e9+7;
int a[M],f[M],g[M],n,m;
int merge(int a,int b,int c){
	int x[3]={a,b,c};
	sort(x,x+3);
	return x[0]+x[1];
}
bool check(int mid){
	int cnt=0;
	for(int i=m+1;i<=n;i++)if(a[i]>=mid)cnt++;
	for(int i=1;i<=n;i++){
		if(g[i]==-1)f[i]=1;
		else if(g[i]>=mid)f[i]=0;
		else f[i]=inf;
	}
	int l=1,r=n;
	while(l<r){
		int t=merge(f[l],f[l+1],f[l+2]);
		if(t>inf)t=inf;
		l+=3;
		f[++r]=t;
	}
	return f[l]<=cnt;
}
int main(){
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	cin>>n>>m;
	memset(g,-1,sizeof(g));
	int mx=0;
	for(int i=1,p;i<=m;i++){
		scanf("%d%d",&a[i],&p);
		g[p]=a[i];
	}
	for(int i=m+1;i<=n;i++)scanf("%d",&a[i]),mx=max(a[i],mx);
	int l=0,r=mx,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
