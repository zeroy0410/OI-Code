#include<bits/stdc++.h>
#define LL long long
#define M 200005
using namespace std;
int T,n,m,K,a;
LL A[M];
bool check(LL x){
	
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d",&n,&m,&K,&a);
		for(int i=1;i<=n;i++)scanf("%d",&A[i]);
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