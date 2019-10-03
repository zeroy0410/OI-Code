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
};
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
	return 0;
}
