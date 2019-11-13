#include<bits/stdc++.h>
#define M 2000005
#define LL long long
using namespace std;
int T,n,A[M];
LL ans;
int main(){
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		ans=0;
		bool flz=0,flf=0;
		int mi=1e9;
		for(int i=1;i<=n;i++){
			scanf("%d",&A[i]);mi=min(mi,A[i]);
			ans+=abs(A[i]);
			if(A[i]>=0)flz=1;
			if(A[i]<=0)flf=1;
		}
		if(flf){
			LL Ans=-1e9;
			for(int i=1;i<=n;i++){
				if(A[i]>=0)Ans=max(Ans,ans);
				else Ans=max(Ans,ans+2*A[i]);
			}
			printf("%lld\n",Ans);
		}
		else {
			if(n==1)printf("%lld\n",ans);
			else printf("%lld\n",ans-2*mi);
		}
	}
	return 0;
}
