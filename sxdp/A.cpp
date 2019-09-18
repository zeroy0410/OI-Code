#include<stdio.h>
#include<algorithm>
#define M 10005
using namespace std;
int m,n,C[M],h[M],tt,rt,in[M];
int dp[M][2];
struct edge{
    int nxt,to;
}G[M<<1];
void Add(int a,int b){
    G[++tt]=(edge){h[a],b};
    h[a]=tt;
}
void dfs(int x,int f){
    if(x<=n)return;
    for(int i=h[x];i;i=G[i].nxt){
        int u=G[i].to;
        if(u==f)continue;
        dfs(u,x);
        dp[x][0]+=min(dp[u][0]-1,dp[u][1]);
        dp[x][1]+=min(dp[u][1]-1,dp[u][0]);
    }
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)scanf("%d",&C[i]);
    for(int i=1,a,b;i<m;i++){
        scanf("%d%d",&a,&b);
        Add(a,b);Add(b,a);
        in[a]++;in[b]++;
    }
    for(int i=n+1;i<=m;i++)
        if(in[i]>1){
            rt=i;
            break;
        }
    for(int i=1;i<=m;i++){
        dp[i][0]=dp[i][1]=1;
        if(i<=n)dp[i][!C[i]]=1e9;
    }
    dfs(rt,0);
    printf("%d\n",min(dp[rt][0],dp[rt][1]));
    return 0;
}
