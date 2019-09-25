#include<cstdio>
#include<algorithm>
#include<cstring>
#define M 205
using namespace std;
int n,P;
struct node{
	int s,t;
	bool operator < (const node& res)const{
		if(s!=res.s)return s<res.s;
		return t>res.t;
	}
}A[M],B[M],C[M];
bool cmp1(node a,node b){
	return a.t-a.s>b.t-b.s;
}
int dp[M][M],m,c;
int sum[M];
int main(){
	scanf("%d%d",&n,&P);m=0;
	for(int i=1;i<=n;i++)scanf("%d%d",&A[i].s,&A[i].t);
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++){
		bool fl=0;
		for(int j=i+1;j<=n;j++){
			if(!(A[i].s==A[j].s&&A[i].t==A[j].t)&&A[i].s<=A[j].s&&A[i].t>=A[j].t){
				fl=1;
				break;
			}
		}
		if(fl)B[++m]=A[i];
		else C[++c]=A[i];
	}
	sort(B+1,B+m+1,cmp1);
	for(int i=1;i<=m;i++)sum[i]=sum[i-1]+B[i].t-B[i].s;
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	for(int j=1;j<=P;j++){
		for(int i=1;i<=c;i++){
			for(int k=0;k<i;k++){
				if(dp[k][j-1]==-1)continue;
				int l=C[i].s,r=C[k+1].t;
				if(l>=r)continue;
				dp[i][j]=max(dp[i][j],dp[k][j-1]+r-l);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=P;i++){
		if(dp[c][i]!=-1)
			ans=max(ans,dp[c][i]+sum[P-i]);
	}
	printf("%d\n",ans);
	return 0;
}
