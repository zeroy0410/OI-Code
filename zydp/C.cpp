#include<bits/stdc++.h>
#define LL long long
#pragma GCC optinize(3)
using namespace std;
char S[15];
int d,T,n;
LL dp[1<<10][1005];
int cnt[1<<10];
LL Pw[11];
LL fac[11];
int ct[15];
int main(){
	scanf("%d",&T);
	Pw[0]=1;fac[0]=1;
	for(int i=1;i<=10;i++){
		Pw[i]=Pw[i-1]*i;
		fac[i]=fac[i-1]*i;
	}
	while(T--){
		scanf("%s%d",S,&d);
		n=strlen(S);
		dp[0][0]=1;
		for(int i=1;i<1<<n;i++){
			cnt[i]=cnt[i>>1]+(i&1);
			for(int j=0;j<n;j++){
				if(i&1<<j){
					int s=(i^(1<<j));
					LL now=Pw[cnt[i]-1]*(S[j]-'0');
					for(int k=0;k<d;k++)
						dp[i][(k+now)%d]+=dp[s][k];
				}
			}
		}
		for(int i=0;i<n;i++)
	}	
	return 0;
}
