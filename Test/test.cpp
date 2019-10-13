#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n;
LL A[M],B[M];
LL K,sum;
LL calc(int x){
	if(x<1||x>n)return 1e18;
	LL res=K;
	for(int i=1;i<=n;i++)B[i]=A[i];
	LL mx=-2e9,mi=2e9;
	for(int i=1;i<x;i++){
		LL ned=abs(B[i]-B[x]);
		if(res<ned){
			if(i<x)B[i]+=res;
			else B[i]-=res;
			res=0;
		}
		else res-=ned,B[i]=B[x];
		mi=min(mi,B[i]);
		mx=max(mx,B[i]);
	}
	for(int i=n;i>x;i--){
		LL ned=abs(B[i]-B[x]);
		if(res<ned){
			if(i<x)B[i]+=res;
			else B[i]-=res;
			res=0;
		}
		else res-=ned,B[i]=B[x];
		mi=min(mi,B[i]);
		mx=max(mx,B[i]);
	}
	return mx-mi;
}
int main(){
	scanf("%d%lld",&n,&K);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum+=A[i];
	sort(A+1,A+n+1);
	int l=1,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		LL t1=calc(mid),t2=calc(mid+1),t3=calc(mid-1);
		if(t1<=t2&&t1<=t3){
			ans=mid;
			break;
		}
		else if(t1>t2)l=mid+1;
		else r=mid-1;
	}
	LL as=calc(ans);
	cout<<as<<endl;
	return 0;
}
