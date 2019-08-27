#include<bits/stdc++.h>
using namespace std;
const int INF=1890000;
inline int read(){}
int n,m,Lim;
int dp[2200][2200],sum[75];
struct node{int h,w;}a[75];
inline bool cmp(node x,node y){return x.h>y.h;}
inline void Do(int &x,int y){if(x>y)x=y;} 
int main(){
    n=read();
    for(register int i=1;i<=n;i++){
        a[i].h=read(),a[i].w=read();
        Lim+=a[i].w;
    }
    sort(a+1,a+n+1,cmp);
    for(register int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i].w;
    for(register int i=0;i<=Lim;i++)for(register int j=0;j<=Lim;j++)dp[i][j]=INF;
    dp[0][0]=0;
    for(register int i=2;i<=n;i++){
        for(register int j=sum[i];j>=0;j--)for(register int k=sum[i];k>=0;k--){
            if(a[i].w<j)Do(dp[j][k],dp[j-a[i].w][k]);
            else if(j==a[i].w)Do(dp[j][k],dp[0][k]+a[i].h);
            if(a[i].w<k)Do(dp[j][k],dp[j][k-a[i].w]);
            else if(k==a[i].w)Do(dp[j][k],dp[j][0]+a[i].h);
        }
    }
    int ans=INF;
    for(register int i=1;i<=Lim;i++)for(register int j=1;j<=Lim;j++){
        if(dp[i][j]==INF)continue;
        int H=dp[i][j]+a[1].h,W=max(Lim-i-j,max(i,j));
        Do(ans,H*W);
    }
    printf("%d\n",ans);
}
