#include<bits/stdc++.h>
#define M 25
#define LL long long
using namespace std;
int d,x,mod;
struct Matrix{
	int n,m,a[M][M];
	void clear(){memset(a,0,sizeof(a));}
	void resize(int _n,int _m){n=_n;m=_m;}
	Matrix operator *(const Matrix &_)const{
		Matrix res;res.resize(n,_.m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=_.m;j++){
				res.a[i][j]=0;
				for(int k=1;k<=m;k++){
					res.a[i][j]+=1LL*a[i][k]*_.a[k][j]%mod;
					if(res.a[i][j]>=mod)res.a[i][j]-=mod;	
				}
			}
		}
		return res;
	}
}Ma,F_d;
Matrix qkpow(Matrix a,int b){
	Matrix res;res.clear();res.resize(a.n,a.n);
	for(int i=1;i<=a.n;i++)res.a[i][i]=1;
	while(b){if(b&1)res=res*a;a=a*a;b>>=1;}
	return res;
}
int A[M],f[M];
int main(){
	while(scanf("%d%d%d",&d,&x,&mod)&&(d!=0&&x!=0&&mod!=0)){
		for(int i=1;i<=d;i++)scanf("%d",&A[i]),A[i]%=mod;
		for(int i=1;i<=d;i++)scanf("%d",&f[i]),f[i]%=mod;
		if(x<=d){printf("%d\n",f[x]);continue;}
		Ma.clear();Ma.resize(d,d);
		for(int i=2;i<=d;i++)Ma.a[i-1][i]=1;
		for(int i=1;i<=d;i++)Ma.a[d][i]=A[d-i+1];
		F_d.clear();F_d.resize(d,1);
		for(int i=1;i<=d;i++)F_d.a[i][1]=f[i];
		Matrix ans=qkpow(Ma,x-d)*F_d;
		printf("%d\n",ans.a[d][1]);
	}
	return 0;
}