#include<cstdio>
#include<algorithm>
#pragma GCC optimize(2)
#define M 100005
using namespace std;
bool mm1;
int n,m,A[M],B[M],C[M],f[25][25];
struct P15{
	void solve(){
		for(int i=0;i<1<<n;i++)
			for(int j=0;j<1<<n;j++)
				C[i|j]=max(C[i|j],f[A[i]][B[j]]);
		for(int i=0;i<1<<n;i++)
			printf("%d ",C[i]);
		puts("");
	}
}p15;
struct P100{
	int dp[43046721],Pow[16];
	void dfs(int x,int sb,int s){
		if(x==n){
			if(sb==-1)return;
			dp[s]=(dp[s+Pow[sb]]|dp[s+Pow[sb]*2]);	
			return;
		}
		dfs(x+1,sb,s+2*Pow[n-x-1]);
		dfs(x+1,sb,s+Pow[n-x-1]);
		if(sb==-1)sb=n-x-1;
		dfs(x+1,sb,s);
	}
	int del[1<<16],mp[1<<16],mx[16][1<<16];
	void Init(){
		for(int i=0;i<1<<n;i++)
			for(int j=0;j<n;j++)
				if(i&1<<j)
					del[i]+=2*Pow[j];
		for(int i=0;i<m;i++){
			for(int j=0;j<1<<m;j++){
				for(int k=0;k<m;k++)
					if(j&1<<k)
						mx[i][j]=max(mx[i][j],f[i][k]);
			}
		}
	}
	void solve(){
		Pow[0]=1;
		for(int i=1;i<=15;i++)Pow[i]=Pow[i-1]*3;
		Init();
		for(int i=0;i<1<<n;i++){
			int s=0;
			for(int j=0;j<n;j++)
				if(i&1<<j)s+=Pow[j]*2;
				else s+=Pow[j];
			dp[s]=(1<<B[i]);
			mp[i]=s;
		}
		dfs(0,-1,0);
		for(int i=0;i<1<<n;i++){
			for(int j=i;;j=(j-1)&i){
				int s=mp[i]-del[j];
				C[i]=max(C[i],mx[A[j]][dp[s]]);
				if(j==0)break;
			}
		}
		for(int i=0;i<1<<n;i++)
			printf("%d ",C[i]);
		puts("");
	}
}p100;
bool mm2;
int main(){
	freopen("convolution.in","r",stdin);
	freopen("convolution.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<1<<n;i++)scanf("%d",&A[i]);
	for(int i=0;i<1<<n;i++)scanf("%d",&B[i]);
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&f[i][j]);
	if(n<=10)p15.solve();
	else p100.solve();
	return 0;
}
