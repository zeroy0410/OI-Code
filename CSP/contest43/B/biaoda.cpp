#include<bits/stdc++.h>
using namespace std;
#define M 55
#define N 10005
#define ll long long
int a[M],dis[10005],n,m,L,c,w=0;
bitset<300005>dp[32];
bool cmp(int x,int y){return x>y;}
int sk[N*20],us[N];
void spfa(){
	int l=1,r=0;
	for(int i=0;i<=a[n];++i)if(dis[i]<1e9)sk[++r]=i,us[i]=1;
	while(l<=r){
		int p=sk[l++];
		us[p]=0;
		for(int i=n;i>=1;--i){
			if(a[i]>=L)break;
			int v=(a[i]+p)%a[n];
			if(dis[v]>dis[p]+a[i]){
				dis[v]=dis[p]+a[i];
				if(!us[v])sk[++r]=v;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	sort(a+1,a+n+1,cmp);
	scanf("%d%d",&L,&c);
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		if(a[i]<L)break;
		w+=a[i];
		for(int j=1;j<=c;++j)dp[j]|=dp[j-1]<<a[i];
	}memset(dis,63,sizeof(dis));
	for(int i=0;i<=c;++i)dp[c]|=dp[i];
	for(int i=0;i<=w;++i)if(dp[c][i])dis[i%a[n]]=min(dis[i%a[n]],i);
	spfa();ll x;
	for(int i=1;i<=m;++i){
		scanf("%lld",&x);
		int v=x%a[n];
		cout<<v<<endl;
		if(dis[v]<1e9&&dis[v]<=x)puts("Yes");
		else puts("No");
	}
}

