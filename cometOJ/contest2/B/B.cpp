#include<bits/stdc++.h>
#define M 2005
#define LL long long
using namespace std;
LL dp[M][M];
int n,A[M],P,sum[M];
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%P;
		a=a*a%P;
		b>>=1;
	}
	return res;
}
void Add(LL &x,LL y){
	x+=y;
	if(x>=P)x-=P;
}
LL fac[M],Ifac[M],tmp[M][M];
LL C(LL x,LL y){
	return fac[x]*Ifac[x-y]%P*Ifac[y]%P;
}
vector<int>son[M];
void Init(){
	fac[0]=fac[1]=1;Ifac[0]=Ifac[1]=1;
	for(int i=2;i<=n;i++){
		fac[i]=fac[i-1]*i%P;
		Ifac[i]=Ifac[i-1]*qkpow(i,P-2)%P;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			son[j].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<(int)son[i].size();j++){
			int x=son[i][j];
			LL res=1,now=i;
			for(int k=1;k<=i/x;k++){
				res=res*C(now,x)%P;
				now-=x;
			}
			res=res*Ifac[i/x]%P;
			tmp[i][i/x]=res;
		}
	}
	tmp[0][0]=1;
}
int main(){
	scanf("%d%d",&n,&P);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),sum[i]=sum[i-1]+A[i];
	sum[n+1]=sum[n];
	Init();
	dp[n+1][0]=1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<=sum[n+1]-sum[i];j++){
			int res=j+A[i];
			for(int k=0;;k++){
				if(k*i>res)break;
				Add(dp[i][res-k*i],dp[i+1][j]*C(res,k*i)%P*tmp[k*i][k]%P);
			}
		}
	}
	printf("%lld\n",dp[1][0]);
	return 0;
}
