#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,q,A[M];
struct que{int l,id;};
vector<que>wk[M];
int ans[M];
LL Pow[M],sum[M];
LL Val[M],qs[M];
int pre[M],fa[M];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
LL get(int l,int r){
	LL res=(sum[l]-sum[r+1]*Pow[r-l+1])%mod;
	if(res<0)res+=mod;
	return res;
}
void merge(int x,int y){
	int len=x-pre[x];
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		wk[r].push_back((que){l,i});
	}
	Pow[0]=1;
	for(int i=1;i<=n;i++)fa[i]=i,Pow[i]=Pow[i-1]*2%mod;
	for(int i=n;i>=1;i--)sum[i]=(sum[i+1]*2+A[i])%mod;
	return 0;
}
