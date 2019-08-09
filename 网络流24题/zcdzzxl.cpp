#include<bits/stdc++.h>
#define M 505
using namespace std;
const int inf=1e9;
int s,t,n,A[M<<1],h[M<<1],tt=1;
struct edge{
    int nxt,to,co;
}G[M*M*105];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
queue<int>Q;
int dep[M<<1],cur[M<<1],ans;
bool bfs(){
    memset(dep,-1,sizeof(dep));
    for(int i=0;i<=n*2+1;i++)cur[i]=h[i];
    Q.push(s);dep[s]=0;
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(dep[u]!=-1||!c)continue;
            dep[u]=dep[x]+1;
            Q.push(u);
        }
    }
    return dep[t]!=-1;
}
int dfs(int x,int mi){
    if(x==t||!mi)return mi;
    int rlow=0,used=0;
    for(int &i=cur[x];i;i=G[i].nxt){
        int u=G[i].to,c=G[i].co;
        if(dep[u]!=dep[x]+1||!c)continue;
        if(rlow=dfs(u,min(mi-used,c))){
            used+=rlow;
            G[i].co-=rlow;
            G[i^1].co+=rlow;
            if(used==mi)break;
        }
    }
    return used;
}
void Dinic(){
    while(bfs()){ans+=dfs(s,inf);}
}
int dp[M],cnt[M];
int ans1,ans2;
int main(){
    scanf("%d",&n);
    s=0;t=n*2+1;
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    for(int i=1;i<=n;i++)dp[i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++)
            if(A[i]>=A[j])dp[i]=max(dp[i],dp[j]+1);
        ans1=max(ans1,dp[i]);
        if(dp[i]==1)cnt[i]=1;
    }
    printf("%d\n",ans1);
    if(ans1==1){printf("%d\n%d\n",n,n);return 0;}
    for(int i=1;i<=n;i++){Add(i,i+n,1);Add(i+n,i,0);}
    for(int i=1;i<=n;i++){
        if(dp[i]==1){Add(s,i,1);Add(i,s,0);}
        if(dp[i]==ans1){Add(i+n,t,1);Add(t,i+n,0);}
        for(int j=1;j<i;j++){
            if(A[j]<=A[i]&&dp[i]==dp[j]+1){
                Add(j+n,i,1);
                Add(i,j+n,0);
            }
        }
    }ans=0;
    Dinic();
    printf("%d\n",ans);
    tt=1;
    memset(h,0,sizeof(h));
    for(int i=1;i<=n;i++){Add(i,i+n,(i==1||i==n)?inf:1);Add(i+n,i,0);}
    for(int i=1;i<=n;i++){
        if(dp[i]==1){Add(s,i,(i==1||i==n)?inf:1);Add(i,s,0);}
        if(dp[i]==ans1){Add(i+n,t,(i==1||i==n)?inf:1);Add(t,i+n,0);}
        for(int j=1;j<i;j++){
            if(A[j]<=A[i]&&dp[i]==dp[j]+1){
                Add(j+n,i,1);
                Add(i,j+n,0);
            }
        }
    }ans=0;
    Dinic();
    printf("%d\n",ans);
    return 0;
}