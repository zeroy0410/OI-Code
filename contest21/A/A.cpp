#include<bits/stdc++.h>
using namespace std;
const int mod=30031;
int n,K,P;
void Add(int &x,int y){
    x+=y;
    if(x>=mod)x-=mod;
}
struct P40{
    int dp[1005][1<<10];
    int sum[1005][1<<10];
    void solve(){
        dp[1][(1<<(K-1))-1]=1;
        for(int i=1;i<=n;i++){
            for(int S=0;S<1<<P;S++){
                int tmp=S,x=0;
                while(tmp){
                    x+=tmp&-tmp;
                    Add(dp[i][S],sum[i][x]);
                    tmp-=tmp&-tmp;   
                }
                if(i>=n-K+1)continue;
                if(!dp[i][S])continue;
                int to=P;if(!(S&1))to=1;
                int las=0;
                for(int j=1;j<=to;j++){
                    if(i+j>n)break;
                    if(S&1<<(j-1)){if(!las)las=i+j;continue;}
                    int mb=las?las:i+j;
                    int tomov=(S>>(mb-i));
                    if(i+j-mb-1>=0)
                        tomov|=(1<<(i+j-mb-1));
                    Add(sum[mb][tomov],dp[i][S]);
                }
            }
        }
        for(int i=1;i<=n-K+1;i++)
            printf("%d ",dp[i][(1<<(K-1))-1]);
        puts("");
        // printf("%d\n",dp[n-K+1][(1<<(K-1))-1]);
    }
}p40;
struct P100{
    struct Matrix{
        int nn,mm,a[155][155];
        void clear(){memset(a,0,sizeof(a));}
        void resize(int _n,int _m){nn=_n;mm=_m;}
        Matrix operator *(const Matrix &_){
            Matrix res;res.clear();res.resize(nn,_.mm);
            for(int i=1;i<=nn;i++){
                for(int j=1;j<=_.mm;j++){
                    res.a[i][j]=0;
                    for(int k=1;k<=mm;k++)
                        Add(res.a[i][j],a[i][k]*_.a[k][j]%mod);
                }
            }
            return res;
        }
        friend Matrix operator ^(Matrix a,int b){
            Matrix res;res.clear();res.nn=a.nn;res.mm=a.mm;
            for(int i=1;i<=res.nn;i++)res.a[i][i]=1;
            while(b){
                if(b&1)res=res*a;
                a=a*a;
                b>>=1;
            }
            return res;
        }
    }Ma,F_d;
    int sta[1<<10],scnt;
    void solve(){
        scnt=0;
        for(int i=(1<<P-1);i<(1<<P);i++){
            int ct=0;for(int j=0;j<P;j++)if(i&1<<j)ct++;
            if(ct==K)sta[++scnt]=i;
        }
        Ma.resize(scnt,scnt);F_d.resize(scnt,1);
        for(int i=1;i<=scnt;i++){
            for(int j=1;j<=scnt;j++){
                int S1=sta[i],S2=sta[j];
                S1=S1-(1<<P-1)<<1;
                for(int k=0;k<P;k++) 
                    if(!((S1>>k)&1)&&S1+(1<<k)==S2)
                        Ma.a[j][i]=1;
            }
        }
        F_d.a[scnt][1]=1;Ma=(Ma^(n-K))*F_d;
        printf("%d\n",Ma.a[scnt][1]);
    }
}p100;
int main(){
    freopen("bus.in","r",stdin);
    freopen("bus.out","w",stdout);
    scanf("%d%d%d",&n,&K,&P);
    p100.solve();
    return 0;
}
