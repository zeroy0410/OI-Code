#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,m,T,K;
struct Matrix{
	double a[30][30];
	Matrix(){
		memset(a,0,sizeof(a));
	}
	Matrix operator * (Matrix& res){
		Matrix ans;
		for(int i=1;i<=25;i++){
			for(int j=1;j<=25;j++){
				if(a[i][j]==0)continue;
				for(int k=1;k<=25;k++)
					ans.a[i][k]+=a[i][j]*res.a[j][k];
			}
		}
		return ans;
	}
}ans;
Matrix qkpow(Matrix a,int b){
	Matrix res;
	for(int i=1;i<=25;i++)res.a[i][i]=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&T,&K);
	ans.a[1][1]=1;int nxt;
	for(int i=1;i<=T;i=nxt+1){
		nxt=T/(T/i);
		Matrix tmp;
		double p1=(T/i)*1.0/T;
		double p2=1-p1;
		for(int j=1;j<=m-n;j++)tmp.a[j][j]=p2,tmp.a[j+1][j]=p1;
		tmp.a[m-n+1][m-n+1]=1;
		for(int j=1;j<=m-n+1;j++)tmp.a[m-n+2][j]=n+j-1;
		tmp.a[m-n+2][m-n+2]=1;
		ans=qkpow(tmp,nxt-i+1)*ans;
	}
	printf("%.6lf\n",ans.a[m-n+2][1]*K);
	return 0;
}
