#include<bits/stdc++.h>
using namespace std;
const int maxn=20,P=1e9+7;
bool cur1;
int n,K,L;
int A[20];
int dp[20][1<<16];
int cnt[1<<16];
void init(){
	for(int i=1;i<1<<16;i++)
		cnt[i]=cnt[i&i-1]+1;
}
void add(int &a,int b){
	a+=b;
	if(a>=P)a-=P;
}
int into[1<<16][17];
void Solve(){
	for(int S=0;S<1<<n;S++){
		for(int i=1;i<=K;i++){
			int res=S;
			for(int j=1;j<=n;j++){
				if(A[j]!=i)continue;
				if(1<<j-1&S)continue;
				res^=1<<j-1;
				for(int k=j+1;k<=n;k++){
					j=k;
					if(1<<k-1&S){
						res^=1<<k-1;
						break;
					}
				}
			}
			into[S][i]=res;
		}
	}
}
bool cur2;
int main(){
	init();
	for(int _=(cin>>_,_);_--;){
		scanf("%d%d%d",&n,&K,&L);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		Solve();
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int S=0;S<1<<n;S++){
				for(int j=1;j<=K;j++){
					add(dp[i][into[S][j]],dp[i-1][S]);
				}
			}
		}
		int ans=0;
		for(int i=0;i<1<<n;i++){
			if(cnt[i]==L){
				add(ans,dp[n][i]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
