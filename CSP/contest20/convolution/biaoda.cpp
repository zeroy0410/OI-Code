#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[1<<16],b[1<<16],f[16][16],c[1<<16],sum1[1<<16][16],sum2[1<<16][16];
ll sum[1<<16][16];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int len=1<<n;
	for(int i=0;i<len;++i)scanf("%d",&a[i]);
	for(int i=0;i<len;++i)scanf("%d",&b[i]);
	for(int i=0;i<len;++i)sum1[i][a[i]]=1,sum2[i][b[i]]=1;
	for(int i=0;i<m;++i)
		for(int j=0;j<m;++j)scanf("%d",&f[i][j]);
	for(int i=0;i<n;++i)
		for(int j=0;j<len;++j)
			if((1<<i)&j)
				for(int k=0;k<m;++k)sum1[j][k]+=sum1[j-(1<<i)][k],sum2[j][k]+=sum2[j-(1<<i)][k];
	for(int i=0;i<len;++i)
		for(int j=0;j<m;++j)
			for(int k=0;k<m;++k)
				sum[i][f[j][k]]+=1ll*sum1[i][j]*sum2[i][k];
	for(int i=0;i<n;++i)
		for(int j=0;j<len;++j)
			if((1<<i)&j)
				for(int k=0;k<m;++k)sum[j][k]-=sum[j-(1<<i)][k];
	for(int i=0;i<len;++i){
		int w=0;
		for(int j=0;j<m;++j)if(sum[i][j])w=j;
		printf("%d ",w);
	}
	return 0;
}
