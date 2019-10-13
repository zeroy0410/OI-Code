#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,A[M];LL K,sum[M];
LL S(int l,int r){return sum[r]-sum[l-1];}
LL calc(int j){ return S(j,n)-1LL*(n-j+1)*A[j]; }
LL calc2(int i){return 1LL*i*A[i]-S(1,i);}
int main(){
	scanf("%d%lld",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i];
	int cur=n;
	LL ans=1e18;
	for(int i=1;i<=n;i++){
		LL ned=calc2(i);
		if(ned>K)break;
		while(ned+calc(cur-1)<=K)cur--;
		while(ned+calc(cur)>K)cur++;
		LL res=K-ned-calc(cur);
		LL tmp=A[cur]-A[i];
		if(calc2(i+1)-calc2(i)<=res)continue;
		if(i<n-cur+1)tmp-=res/i;
		else tmp-=res/(n-cur+1);
		tmp=max(tmp,0LL);
		ans=min(ans,tmp);
	}
	if(ans==1e18)ans=0;
	printf("%lld\n",ans);
	return 0;
}
