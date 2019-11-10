#include<bits/stdc++.h>
using namespace std;
int T,n,m,_A[20];
int dp[1<<15],cnt[1<<15];
bool mark[1<<15];
int* A=_A+1;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%d",&T);
	for(int i=1;i<1<<15;i++)
		cnt[i]=cnt[i&(i-1)]+1;
	while(T--){
		memset(mark,0,sizeof(mark));
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d",&A[i]);
		sort(A,A+n,cmp);
		for(int i=1;i<n;i++)A[i]+=A[i-1];
		scanf("%d",&m);
		for(int i=1,x;i<=m;i++){
			scanf("%d",&x);
			int res=0;
			for(int j=1,y;j<=x;j++){
				scanf("%d",&y);
				res|=1<<y-1;
			}
			mark[res]=1;
		}
		memset(dp,60,sizeof(dp));
		dp[0]=0;
		for(int i=0;i<1<<n;i++){
			int S=((1<<n)-1)^i;
			for(int j=S;j;j=(j-1)&S)
				dp[i|j]=min(dp[i|j],dp[i]+A[cnt[i|j]-mark[j]-1]-A[cnt[i]-1]);
		}
		printf("%d\n",dp[(1<<n)-1]);
	}
	return 0;
}
