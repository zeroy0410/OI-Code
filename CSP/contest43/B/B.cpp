#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
int n,m,L,C,A[55],W;
bool cmp(int a,int b){return a>b;}
bitset<M>dp[35];
queue<int>Q;
int dis[M];
bool vis[M];
void SPFA(){
	for(int i=0;i<=A[n];i++){
		vis[i]=0;
		if(dis[i]<1e9){
			Q.push(i);
			vis[i]=1;
		}
	}
	while(!Q.empty()){
		int x=Q.front();Q.pop();vis[x]=0;
		for(int i=n;i>=1;i--){
			if(A[i]>=L)break;
			int to=(A[i]+x)%A[n];
			if(dis[to]>dis[x]+A[i]){
				dis[to]=dis[x]+A[i];
				if(!vis[to]){
					vis[to]=1;
					Q.push(to);
				}
			}
		}
	}
}
int main(){
//	freopen("bag.in","r",stdin);
//	freopen("bag.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	scanf("%d%d",&L,&C);
	sort(A+1,A+n+1,cmp);
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		if(A[i]<L)break;
		W+=A[i];
		for(int j=1;j<=C;j++)dp[j]|=dp[j-1]<<A[i];
	}
	for(int i=0;i<=C;i++)dp[C]|=dp[i];
	memset(dis,0x3f,sizeof(dis));
	for(int i=0;i<=W;i++)
		if(dp[C][i])
			dis[i%A[n]]=min(i,dis[i%A[n]]);
	SPFA();
	for(int i=1;i<=m;i++){
		LL x;
		scanf("%lld",&x);
		int v=x%A[n];
		if(dis[v]<1e9&&dis[v]<=x)puts("Yes");
		else puts("No");
	}
	return 0;
}
