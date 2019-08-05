#include<bits/stdc++.h>
#define M 200005
#define LL long long
using namespace std;
const int mod=16777216;
int n,A[M],L[M],R[M];
struct BIT{
	int C[M];
	void clear(){memset(C,0,sizeof(C));}
	void add(int x,int d){
		for(x++;x<=n+1;x+=(x&-x))
			C[x]+=d;	
	}
	int sum(int x){
		int res=0;
		for(x++;x;x-=(x&-x))
			res+=C[x];
		return res;	
	}
}T;
LL ans;
int main(){
	freopen("totem.in","r",stdin);
	freopen("totem.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++){
		L[i]=T.sum(A[i]);
		R[i]=A[i]-1-L[i];
		T.add(A[i],1);
	}
	for(int i=1;i<=n;i++){
		LL t=n-i-R[i];
		ans-=t*(t-1)*(t-2)/6%mod;
		ans=(ans+mod)%mod;
	}T.clear();
	for(int i=1;i<=n;i++){
		LL t=n-i-R[i];
		ans+=t*(L[i]*(i-1)-T.sum(A[i])-L[i]*(L[i]-1)/2)%mod;
		ans%=mod;
		T.add(A[i],i);
	}T.clear();
	for(int i=1;i<=n;i++){
		LL t=n-i-R[i];
		ans+=t*(L[i]*(A[i]-1)-T.sum(A[i])-L[i]*(L[i]-1)/2)%mod;	
		ans%=mod;
		T.add(A[i],A[i]);
	}T.clear();
//	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		LL t=n-i-R[i];
		ans+=t*T.sum(A[i]);
		ans%=mod;
		T.add(A[i],L[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
