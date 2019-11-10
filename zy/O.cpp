#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define M 3005
bool mark[M],no[M];
int pr[M],pc,p[M],pp;
void Init(){
	for(int i=2;i<M;i++){
		if(!mark[i]){
			pr[++pc]=i;
			for(int j=i+i;j<M;j+=i)
				mark[j]=1;
		}
	}
	for(int i=2;i*i<M;i++)
		for(int j=i*i;j<M;j+=i*i)
			no[j]=1;
}
bool num[M],mk[M];
struct node{
	int sp,mp;
	bool operator < (const node& res)const{
		return mp<res.mp;
	}
}A[M];
int T,n,m,tot,dp[1<<16],res[1<<16];
int main(){
	Init();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		memset(num,0,sizeof(num));
		for(int i=2;i<=n;i++){
			int x=i;
			for(int j=1;j<=pc&&pr[j]<=n;j++)
				while(x%pr[j]==0)num[j]^=1,x/=pr[j];
		}
		memset(mk,0,sizeof(mk)); 	
		for(int i=1;i<=pc&&pr[i]<=n;i++){
			if(num[i])continue;
			for(int j=pr[i];j<=n;j+=pr[i])mk[j]=1;
		}
		pp=0;
		for(int i=1;pr[i]*pr[i]<=n;i++)
			if(num[i])p[pp++]=pr[i];
		tot=0;
		for(int i=1;i<=n;i++){
			if(no[i]||mk[i])continue;
			++tot;int x=i;
			A[tot].sp=0;
			for(int j=0;j<pp;j++)
				if(x%p[j]==0)x/=p[j],A[tot].sp|=1<<j;
			A[tot].mp=x;
		}
		sort(A+1,A+tot+1);
		memset(dp,0,sizeof(dp));dp[0]=1;
		for(int i=1;i<=tot;i++){
			for(int j=(1<<pp)-1;j>=0;j--){
				if(!(A[i].sp&j)){
					if(A[i].mp==1)dp[j|A[i].sp]=(dp[j|A[i].sp]+dp[j])%m;
					else dp[j|A[i].sp]=(dp[j|A[i].sp]+res[j])%m;
				}
			}
			if(i!=tot&&A[i].mp!=A[i+1].mp){
				for(int j=0;j<(1<<pp);j++)
					res[j]=dp[j],dp[j]=0;
			}
		}
		printf("%d\n",dp[(1<<pp)-1]);
	}
	return 0;
}
