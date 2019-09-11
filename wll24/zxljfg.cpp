#include<bits/stdc++.h>
#define M 205
using namespace std;
int n,m,h[M],tt=1;
struct edge{
    int nxt,to;
}G[M*605];
void Add(int a,int b){
    G[++tt]=(edge){h[a],b};
    h[a]=tt;
}
int mk[M],nxt[M];
bool vis[M];
bool sp(int x){
    for(int i=h[x];i;i=G[i].nxt){
        int u=G[i].to;
        if(vis[u])continue;
        vis[u]=1;
        if(mk[u]==-1||sp(mk[u])){
            mk[u]=x;
            nxt[x]=u;
            return 1;
        }
    }
    return 0;
}
int ans=0;
int main(){
    memset(mk,-1,sizeof(mk));
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++){
        scanf("%d%d",&a,&b);
        Add(a,b);
    }
    for(int i=1;i<=n;i++){
        sp(i);
        memset(vis,0,sizeof(vis));
    }
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        int x=i;
        while(x){
            vis[x]=1;
            printf("%d ",x);
            x=nxt[x];
        }
        ans++;
        printf("\n");
    }
    printf("%d\n",ans);
    return 0;
}