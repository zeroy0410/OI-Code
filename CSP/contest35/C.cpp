#include<bits/stdc++.h>
#define M 105
#define LL long long
const int mod=998244353;
using namespace std;
int n,m,p,q;
LL C[M][M],S[M][M],fac[M];
void Add(LL& x,LL y){
	x+=y;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
void Init(){
	C[0][0]=1;
	for(int i=1;i<M;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	S[0][0]=1;
	for(int i=1;i<M;i++){
		for(int j=1;j<=i;j++)
			S[i][j]=(1LL*S[i-1][j]*j%mod+S[i-1][j-1])%mod;
	}
	fac[0]=1;
	for(int i=1;i<M;i++)
		fac[i]=1LL*fac[i-1]*i%mod;
}
struct P1{
	LL dp[M][M];
	void solve(){
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=p;i++)
			dp[1][i]=1LL*C[p][i]*S[n][i]%mod*fac[i]%mod;
		for(int i=2;i<=m;i++){
			for(int j=1;j<=p;j++){
				for(int k=0;k<=j;k++){//same
					for(int r=0;r<=p-j;r++)//unsame
						if(r+j>=q)
							Add(dp[i][k+r],1LL*C[j][k]*C[p-j][r]%mod*dp[i-1][j]%mod*S[n][k+r]%mod*fac[k+r]%mod);
				}
			}
		}
		LL ans=0;
		for(int i=1;i<=p;i++)
			Add(ans,dp[m][i]);
		printf("%lld\n",ans);
	}
}p1;
struct Matrix{
    int n,m;
	LL a[M][M];
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
};
Matrix qkpow(Matrix a,int b){
	Matrix res;res.resize(p,p);
	for(int i=1;i<=p;i++)
		res.a[i][i]=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
struct P2{
	Matrix trans,Ans;
	void solve(){
		trans.clear();Ans.clear();
		trans.resize(p,p);Ans.resize(1,p);
		for(int i=1;i<=p;i++)
			Ans.a[1][i]=1LL*C[p][i]*S[n][i]%mod*fac[i]%mod;
		for(int j=1;j<=p;j++){
			for(int k=0;k<=j;k++){//same
				for(int r=0;r<=p-j;r++)//unsame
					if(r+j>=q)
						Add(trans.a[j][k+r],1LL*C[j][k]*C[p-j][r]%mod*S[n][k+r]%mod*fac[k+r]%mod);
			}
		}
		Ans=Ans*qkpow(trans,m-1);
		LL ans=0;
		for(int i=1;i<=p;i++)
			Add(ans,Ans.a[1][i]);
		printf("%lld\n",ans);
	}

}p2;
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	Init();
	scanf("%d%d%d%d",&n,&m,&p,&q);
	p2.solve();
	return 0;
}
