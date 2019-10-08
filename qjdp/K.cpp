#include<bits/stdc++.h>
#define M 1005
using namespace std;
int n,P;
int dp[M][M][2];
struct node{
	int x,y,v;
	bool operator < (const node& res)const{
		return x<res.x;
	}
}A[M];
int sum[M],tt;
int S(int l,int r){return sum[r]-sum[l-1];}
int main(){
	memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&P);
	for(int i=1;i<=n;i++)scanf("%d",&A[i].x);
	for(int i=1;i<=n;i++)scanf("%d",&A[i].y),tt+=A[i].y;
	for(int i=1;i<=n;i++)scanf("%d",&A[i].v);
	A[++n].x=P;
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i].v;
	for(int i=1;i<=n;++i)if(A[i].v==0&&A[i].x==P)dp[i][i][0]=dp[i][i][1]=0;
    for(int k=1;k<n;++k)for(int i=1,j=i+k;i<=n&&j<=n;++i,j=i+k){
        dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(S(1,i)+S(j+1,n))*(A[i+1].x-A[i].x));
        dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(S(1,i)+S(j+1,n))*(A[j].x-A[i].x));
        dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(S(1,i-1)+S(j,n))*(A[j].x-A[j-1].x));
        dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(S(1,i-1)+S(j,n))*(A[j].x-A[i].x));
    }
	printf("%.3lf\n",1.0*(tt-min(dp[1][n][0],dp[1][n][1]))/1000);
    return 0;
}
