#include<bits/stdc++.h>
#define M 105
using namespace std;
const int mod=30011;
int n,m;
struct Matrix{
	int a[M][M],n,m;
	Matrix(){memset(a,0,sizeof(a));}
	void resize(int _n,int _m){n=_n;m=_m;}
	Matrix operator * (const Matrix& res){
		Matrix ans;ans.resize(n,res.m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=res.m;j++)
				for(int k=1;k<=m;k++)
					ans.a[i][j]=(ans.a[i][j]+1LL*a[i][k]*res.a[k][j]%mod)%mod;
		return ans;
	}
};
Matrix trans,st;
int id(int x,int f){ if(!f)return x;return x+n; }
Matrix qkpow(Matrix a,int b){
	Matrix res;res.resize(2*n,2*n);
	for(int i=1;i<=2*n;i++)res.a[i][i]=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	trans.resize(2*n,2*n);
	for(int i=1;i<=n;i++)
		for(int f=0;f<=1;f++){
			trans.a[id(i,f)][id(i,!f)]=1;
			if(i>1)trans.a[id(i-1,f)][id(i,!f)]=1;
			if(i<n)trans.a[id(i+1,f)][id(i,!f)]=1;
		}
	st.resize(n,1);
	st.a[id(1,1)][1]=1;
	st=st*qkpow(trans,m-1);
	cout<<st.a[id(1,1)][1]<<endl;
	printf("%d\n",st.a[id(n,m&1)][1]);
	return 0;
}
