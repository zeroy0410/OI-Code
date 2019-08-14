#include<bits/stdc++.h>
#define M 1005
#define LL long long
using namespace std;
const int mod=1000000007;
int n;char S[M];
struct P0{
    struct Matrix{
        LL a[2][2];
        void clear(){memset(a,0,sizeof(a));}
        Matrix operator * (Matrix res){
            Matrix ans;ans.clear();
            for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                    for(int k=0;k<2;k++)
                        ans.a[i][j]=(ans.a[i][j]+a[i][k]*res.a[k][j]%mod)%mod;
            return ans;
        }
        Matrix operator + (Matrix res){
            Matrix ans;ans.clear();
            for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                    ans.a[i][j]=(a[i][j]+res.a[i][j])%mod;
            return ans;
        } 
    }Ma,F[M];
    Matrix qkpow(Matrix a,LL b){
        Matrix res;res.clear();
        res.a[0][0]=res.a[1][1]=1;
        while(b){
            if(b&1)res=res*a;
            a=a*a;
            b>>=1;
        }
        return res;
    }
    void solve(){
        for(int i=1;i<=n;i++)S[i]-='0';
        Ma.a[0][1]=Ma.a[1][0]=Ma.a[1][1]=1;
        F[n+1].a[0][0]=F[n+1].a[1][1]=1;
        for(int i=n;i>=1;i--){
            Matrix tmp=qkpow(Ma,S[i]);
            for(int j=i+1;j<=n+1;j++){
                F[i]=F[i]+(F[j]*tmp);
                tmp=qkpow(tmp,10)*qkpow(Ma,S[j]);
            }
        }
        printf("%lld\n",F[1].a[0][0]);
    }
}p0;
int main(){
    freopen("cell.in","r",stdin);
    freopen("cell.out","w",stdout);
    scanf("%d%s",&n,S+1);
    p0.solve();
    return 0;
}