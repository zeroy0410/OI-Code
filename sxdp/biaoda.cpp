#include<iostream>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
ll mod=1000000007;
int n,tot;
char ss[105];
ll f[105][105],g[105][105],tmp[105],c[105][105];
int h[105],to[105],ne[105],sum[105];
void add(int x,int y){tot++;to[tot]=y;ne[tot]=h[x];h[x]=tot;}
void dfs(int x){
	int l=x<<1,r=l|1;
	if(l<=n)add(x,l);
	if(r<=n)add(x,r);
	int i,j,k;
	g[x][1]=f[x][1]=sum[x]=1;
	for(i=h[x];i;i=ne[i]){
		dfs(to[i]);
		for(j=1;j<=sum[x]+sum[to[i]];j++)tmp[j]=0;//临时数组
		for(j=1;j<=sum[x];j++)
			for(k=0;k<=sum[to[i]];k++){
				if(ss[to[i]]=='>')
					tmp[j+k]+=f[x][j]*g[to[i]][k]%mod
						*c[j+k-1][j-1]%mod*c[sum[x]+sum[to[i]]-j-k][sum[x]-j]%mod;
				else tmp[j+k]+=f[x][j]*(g[to[i]][sum[to[i]]]-g[to[i]][k]+mod)%mod
					*c[j+k-1][j-1]%mod*c[sum[x]+sum[to[i]]-j-k][sum[x]-j]%mod;
			}
		sum[x]+=sum[to[i]];
		for(j=1;j<=sum[x];j++)//前缀和
			f[x][j]=tmp[j]%mod,g[x][j]=(g[x][j-1]+f[x][j])%mod;
	}
}
int main(){
	int i,j,x=0,bj=2;
	scanf("%d%s",&n,ss+2);
	c[0][0]=1;
	for(i=1;i<=n;i++){//组合数
		c[i][0]=1;
		for(j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	dfs(1);printf("%lld",g[1][sum[1]]);
	return 0;
}
