#include<bits/stdc++.h>
#define LL long long
#define M 200005
using namespace std;
int T,n,m,K,a;
LL A[M];
vector<int>wk[M];
priority_queue<int>Q;
int ret[M];
bool check(LL x){
	while(!Q.empty())Q.pop();
	int now=0,cnt=0;
	memset(ret,0,sizeof(ret));
	for(int i=1;i<=n;i++){
		for(int j=0;j<wk[i].size();j++)Q.push(wk[i][j]);
		now+=ret[i];
		while(now+A[i]<x){
			if(Q.empty())return 0;
			int u=Q.top();Q.pop();
			if(u<i)continue;
			now+=a;ret[u+1]-=a;cnt++;
		}
	}
	return cnt<=K;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d",&n,&m,&K,&a);
		for(int i=1;i<=n;i++)wk[i].clear();
		for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
		for(int i=1,l,r;i<=m;i++){
			scanf("%d%d",&l,&r);
			wk[l].push_back(r);
		}
		LL l=1,r=1e18,ans=-1;
		while(l<=r){
			LL mid=(l+r)>>1;
			if(check(mid))ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
