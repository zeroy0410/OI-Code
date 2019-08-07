#include<bits/stdc++.h>
using namespace std;
const int mod=30031;
int n,K,P;
struct P40{
    int dp[1005][1<<10];
    int sum[1005][1<<10];
    void Add(int &x,int y){
        x+=y;
        if(x>=mod)x-=mod;
    }
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
// struct P100{

//     void solve(){

//     }
// }p100;
int main(){
    // freopen("bus.in","r",stdin);
    // freopen("bus.out","w",stdout);
    scanf("%d%d%d",&n,&K,&P);
    p40.solve();
    return 0;
}