#include<bits/stdc++.h>
#define M 15
#define LL long long
using namespace std;
int n,K;
LL dp[M][1<<9][105],cnt[1<<9];
vector<int>wk[1<<9];
bool check(int i,int j,int k){
	if(i&1<<k){
		if(j&1<<k)return 0;
		if(k>0&&(j&(1<<(k-1))))return 0;
		if(k<n-1&&(j&(1<<(k+1))))return 0;
	}
	return 1;
}
void Print(int x){
	for(int i=0;i<n;i++)
		if(x&1<<i)printf("1");
		else printf("0");
	puts("");
}
bool mark[1<<9];
void Init(){
	for(int i=0;i<1<<n;i++)
		if(i&(i>>1))mark[i]=1;
	for(int i=0;i<1<<n;i++){
		if(mark[i])continue;
		for(int j=0;j<1<<n;j++){
			bool fl=1;if(mark[j])continue;
			for(int k=0;k<n;k++){
				if(!check(i,j,k)){
					fl=0;
					break;
				}
			}
			if(fl){
				wk[i].push_back(j);
//				Print(i);Print(j);
//				puts("");
			}
		}
	}
	cnt[0]=0;
	for(int i=1;i<1<<n;i++)
		cnt[i]=cnt[i>>1]+(i&1);
}
int main(){
	scanf("%d%d",&n,&K);
	Init();
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<1<<n;j++){
			for(int k=0;k<=K;k++){
				if(dp[i-1][j][k]==0)continue;
				for(int r=0;r<wk[j].size();r++){
					int s=wk[j][r];
					dp[i][s][k+cnt[s]]+=dp[i-1][j][k];
				}
			}
		}
	}
	LL ans=0;
	for(int j=0;j<1<<n;j++)
		ans+=dp[n][j][K];
	printf("%lld\n",ans);
	return 0;
}
