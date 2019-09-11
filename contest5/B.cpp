#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
int n,A[M],B[M];
struct BIT{
	int C[M];
	void clear(){
		memset(C,0,sizeof(C));
	}
	void add(int x,int d){
		while(x<=n){C[x]+=d;x+=(x&-x);}
	}
	int sum(int x){
		int res=0;while(x){res+=C[x];x-=(x&-x);}
		return res;
	}
}Tr,TT;
struct P100{
	LL l[M],r[M]; 
	void solve(){
		LL ans=0;Tr.clear();TT.clear();
		for(int i=1;i<=n;i++)l[i]=i-1-Tr.sum(A[i]),Tr.add(A[i],1);
		for(int i=n;i>=1;i--)r[i]=n-i-TT.sum(A[i]),TT.add(A[i],1);
		for(int i=1;i<=n;i++)ans+=min(l[i],r[i]); 
		printf("%lld\n",ans);
	}
}p100;
int main(){
	freopen("funny.in","r",stdin);
	freopen("funny.out","w",stdout);
	scanf("%d",&n);A[0]=0;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),B[i]=A[i];
	sort(B+1,B+n+1);
	for(int i=1;i<=n;i++)A[i]=lower_bound(B+1,B+n+1,A[i])-B;
	p100.solve();
	return 0;	
}
