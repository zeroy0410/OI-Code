#include<bits/stdc++.h>
#define M 505
using namespace std;
const int inf=1e9;
int n,K,h[M<<1],s,t,tt=1;
struct edge{int nxt,to,co,fe;}G[M*M];
void Add(int a,int b,int c,int d){
    G[++tt]=(edge){h[a],b,c,d};h[a]=tt;
    G[++tt]=(edge){h[b],a,0,-d};h[b]=tt;
}
int B[M<<1],bc;
int L[M],R[M];
bool vis[M<<1];
int dis[M<<1],pre[M<<1],mi[M<<1],ans,ans2;
queue<int>Q;
bool SPFA(){
    for(int i=s;i<=t;i++)
        dis[i]=inf,vis[i]=0;
    while(!Q.empty())Q.pop();
    Q.push(s);vis[s]=1;dis[s]=0;mi[s]=inf;
    while(!Q.empty()){
        int x=Q.front();Q.pop();vis[x]=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co,fe=G[i].fe;
            if(dis[u]>dis[x]+fe&&c){
                dis[u]=dis[x]+fe;
                pre[u]=i;
                mi[u]=min(c,mi[x]);
                if(!vis[u]){
                    Q.push(u);
                    vis[u]=1;
                }
            }
        }
    }
    return dis[t]!=inf;
}
void Update(){
    ans+=mi[t];
    ans2+=dis[t]*mi[t];
    int x=t;
    while(x!=s){
        int i=pre[x];
        G[i].co-=mi[t];
        G[i^1].co+=mi[t];
        x=G[i^1].to;
    }
}
int main(){
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&L[i],&R[i]);
        if(L[i]>R[i])swap(L[i],R[i]);
        B[++bc]=L[i];B[++bc]=R[i];
    }
    sort(B+1,B+bc+1);bc=unique(B+1,B+bc+1)-B-1;
    for(int i=1;i<=n;i++){
        L[i]=lower_bound(B+1,B+bc+1,L[i])-B;
        R[i]=lower_bound(B+1,B+bc+1,R[i])-B;
    }
    s=0;t=bc+1;
    Add(s,1,K,0);Add(bc,t,K,0);
    for(int i=2;i<=bc;i++)Add(i-1,i,inf,0);
    for(int i=1;i<=n;i++)
        Add(L[i],R[i],1,-(B[R[i]]-B[L[i]]));
    while(SPFA())Update();
    printf("%d\n",-ans2);
    return 0;
}