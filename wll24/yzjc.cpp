#include<bits/stdc++.h>
#define M 305
using namespace std;
const int inf=1e9;
int s,t,m,n,h[M<<1],tt=1;
struct edge{
    int nxt,to,co;
}G[M*M*105];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
int dis[M<<1],pre[M<<1],ans;
queue<int>Q;
bool bfs(){
    memset(dis,-1,sizeof(dis));
    while(!Q.empty())Q.pop();
    Q.push(s);dis[s]=inf;
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(dis[u]!=-1||!c)continue;
            dis[u]=min(dis[x],c);
            pre[u]=i;
            if(u==t)return 1;
            Q.push(u);
        }
    }
    return 0;
}
void update(){
    ans-=dis[t];
    int x=t;
    while(x!=s){
        int i=pre[x];
        G[i].co-=dis[t];
        G[i^1].co+=dis[t];
        x=G[i^1].to;
    }
}
int main(){
    scanf("%d%d",&m,&n);
    s=0;t=m+n+1;ans=0;
    for(int i=1,x;i<=m;i++){//单位
        scanf("%d",&x);ans+=x;
        Add(s,i,x);Add(i,s,0);
    }
    for(int i=1,x;i<=n;i++){//桌子
        scanf("%d",&x);
        Add(m+i,t,x);Add(t,m+i,0);
        for(int j=1;j<=m;j++){
            Add(j,m+i,1);Add(m+i,j,0);
        }
    }
    while(bfs())update();
    // cout<<ans<<endl;
    if(ans!=0)puts("0");
    else {
        puts("1");
        for(int x=1;x<=m;x++){
            for(int i=h[x];i;i=G[i].nxt){
                int u=G[i].to,c=G[i].co;
                if(u>m&&!c)printf("%d ",u-m);
            }
            puts("");
        }
    }
    return 0;
}