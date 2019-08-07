#include<bits/stdc++.h>
#define M 75
using namespace std;
const int inf=1e9;
int n,A[M],h[M],tt=1;
struct edge{
    int nxt,to,co;
}G[M*M*2];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
bool vis[M];
int dep[M],d
queue<int>Q;
bool SPFA(){
    for(int i=0;i<=n;i++)vis[i]=0,dis[i]=inf,Q.push(s);
    while(!Q.empty()){
        int x=Q.front();Q.pop();vis[x]=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(dis[u]>dis[x]+c&&dis
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    do{

    }while(Dinic())
    return 0;
}