#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,m;
int P[M];
LL A[M],B[M],C[M];
struct BIT{
	LL C[M];
	void clear(){
		memset(C,0,sizeof(C));
	}
	void add(int x,int d){
		x++;
		while(x<=n+1){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	void update(int l,int r){
		add(l,1);add(r+1,-1);
	}
	LL query(int x){
		x++;LL res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
int main(){
	scanf("%d%d",&n,&m);Tr.clear();
	for(int i=1;i<=m;i++)scanf("%d",&P[i]);
	for(int i=1;i<n;i++)scanf("%lld%lld%lld",&A[i],&B[i],&C[i]);
	for(int i=1;i<m;i++){
		if(P[i]==P[i+1])continue;
		int a=P[i],b=P[i+1];
		if(a>b)swap(a,b);
		Tr.update(a,b-1);
	}
	LL ans=0;
	for(int i=1;i<n;i++){
		LL ct=Tr.query(i);
		ans+=min(ct*A[i],C[i]+ct*B[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
