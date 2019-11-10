#include<bits/stdc++.h>
#define M 100005
#define LL long long 
#pragma GCC optimize(2)
const int mod=1e9+1;
int n,len[25],m=0;
LL dp[25][1<<12],ans=1;
bool mark[M],ca[M];
void solve(int x){
	memset(len,0,sizeof(len));m=0;
	memset(dp,0,sizeof(dp));
	for(int i=x;i<=n;i<<=1){
		for(int j=i;j<=n;j=j*3)
			len[m]++,mark[j]=1;
		m++;
	}
    for(int i=0;i<(1<<len[0]);i++)dp[0][i]=ca[i];
    for(int i=1;i<m;i++)
        for(int j=0;j<(1<<len[i-1]);j++)
            for(int k=0;k<(1<<len[i]);k++)
                if(ca[j]&&ca[k]&&!(j&k))dp[i][k]=(dp[i][k]+dp[i-1][j])%mod;
	LL res=0;
	for(int k=0;k<1<<len[m-1];k++)
		res=(res+dp[m-1][k])%mod;
	ans=ans*res%mod;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<1<<12;i++)
		if(i&(i>>1))ca[i]=0;
		else ca[i]=1;
	for(int i=1;i<=n;i++)
		if(!mark[i])
			solve(i);
	printf("%lld\n",ans);
	return 0;
}
