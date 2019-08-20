#include<bits/stdc++.h>
#define M 50005
using namespace std;
const int mod=10007;
int n,k,h[M],tt;
int now,A,B,Q;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
int dp[M][155];
int str[155][155],fac[M];
void Init(){
	str[0][0]=str[1][1]=1;
	for(int i=2;i<=K;i++)
		for(int j=1;j<=i;j++)
			str[i][j]=(str[i-1][j-1]+1LL*j*str[i-1][j])%mod;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1LL*fac[i-1]*i%mod;
}
void dfs(int x,int f){
	dp[x][0]=1;
	for(int i=h[x];i;i=G[i].nxt
}
int main(){
	// freopen("civilization.in","r",stdin);
	// freopen("civilization.out","w",stdout);
	scanf("%d%d",&n,&k);
	Init();
	scanf("%d%d%d%d",&now,&A,&B,&Q);
	int tmp,x,y;
	for(int i=1;i<n;i++){
	    now=(now*A+B)%Q,tmp=i<L?i:L;
	    x=i-now%tmp,y=i+1;
	    Add(x,y);Add(y,x);
	}
	return 0;
}
