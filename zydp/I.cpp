#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,C[16][16];
LL dp[1<<16];
LL co[16][1<<16];
void Init(){
	for(int i=0;i<16;i++){
		for(int j=0;j<1<<n;j++){
			if(j&1<<i)continue;
			LL res=1;
			for(int k=0;k<n;k++)
				if(j&1<<k)
					res=res*C[i][k]%mod;
			co[i][j]=res;
		}
	}
}
void Add(LL &x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&C[i][j]);
	Init();
	for(int i=0;i<n;i++)dp[1<<i]=1;
	for(int i=0;i<1<<n;i++){
//		if(dp[i]==0)continue;
		for(int j=0;j<n;j++){
			if(i&1<<j)continue;
			for(int k=i;k;k=(k-1)&i)
				Add(dp[i|1<<j],dp[i^k]*C[j][k]%mod);
		}
	}
	printf("%lld\n",dp[(1<<n)-1]);
	return 0;
}
