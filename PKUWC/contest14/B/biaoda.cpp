#include<bits/stdc++.h>
#define M 300005
using namespace std;
int n,A[M],L[M],R[M];
int cnt[M],all[M];
int dp[M];
int stk[M],top;
int main(){
	for(int _=(scanf("%d",&_),_);_;_--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			cnt[i]=all[i]=dp[i]=0;
			L[i]=2e9,R[i]=-2e9;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&A[i]);
			L[A[i]]=min(L[A[i]],i);
			R[A[i]]=max(R[A[i]],i);
			all[A[i]]++;
		}
		top=0;
		for(int i=1;i<=n;i++){
			cnt[i]=cnt[i-1];
			if(L[A[i]]==i){
				stk[++top]=A[i];
				cnt[i]+=all[A[i]];
			}
			if(R[stk[top]]==i){
				while(top&&R[stk[top]]<=i)top--;
				int ll=L[stk[top+1]]-1;
				if(ll<=i&&cnt[i]-cnt[ll]==i-ll)//得全满 
					dp[i]=dp[ll]+1;
			}
		}
		long long ans=0;
		for(int i=1;i<=n;i++)ans+=dp[i];
		printf("%lld\n",ans);
	}
	return 0;
}
