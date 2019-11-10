#include<bits/stdc++.h>
#define rint register int
using namespace std;
const int SZ=1<<18|5;
int n,m,K,base;
int bin[SZ],cnt[SZ],dp[SZ];
int rk[18];
bool mark[18][SZ];
int main(){
    //freopen("set.in","r",stdin);
    // freopen("set.out","w",stdout);
    scanf("%d%d%d",&n,&m,&K);
    cout<<n<<' '<<m<<' '<<K<<endl;
    base=(1<<n)-1;
    for(rint i=1;i<n;i++)bin[1<<i]=i;
    for(rint i=1,x;i<=m;i++){
        scanf("%d",&x);
        for(rint ii=x;ii;ii&=ii-1)
            mark[bin[ii&-ii]][x]=1;
    }
    for(rint i=0;i<n;i++)
        for(rint j=1;j<base;j++)
            if(mark[i][j])//预处理mark数组相当于把超集都覆盖掉
                for(rint ii=base^j;ii;ii&=ii-1)
                    mark[i][(1<<bin[ii&-ii])|j]=1;
    int ned=base-K;
    memset(dp,-1,sizeof(dp));
    for(rint i=0;i<base;i++){
        if(i)cnt[i]=cnt[i&(i-1)]+1;
        if(!i||dp[i]!=-1)    
            for(rint ii=i^base,j;ii;ii&=ii-1){
                j=bin[ii&-ii];
                if(((1<<cnt[i])&ned)&&mark[j][i|(1<<j)])continue;//判非法
                dp[i|(1<<j)]=j;
            }
    }
    if(dp[base]==-1)return puts("-1"),0;
    for(rint s=base,t=n;s;s^=1<<dp[s])rk[dp[s]]=--t;//然后根据dp得出优先级rk
    for(rint i=1;i<=base;i++){
        int mx=-1;
        for(rint ii=i,t;ii;ii&=ii-1){
            t=bin[ii&-ii];
            if(mx==-1||rk[t]>rk[mx])mx=t;//取优先级最大的那个"lowbit"
        }
        putchar((((1<<rk[mx])&K)>0)+'0');
    }putchar('\n');
    return 0;
}