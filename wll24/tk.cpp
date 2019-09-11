#include<bits/stdc++.h>
#define M 105
using namespace std;
const int inf=1e9;
int n,m,h[M],tt=1;
int s,t,A[M];
struct edge{
    int nxt,to,co;
}G[M*M*2];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};h[a]=tt;
}
int dep[M],ans,cur[M];
queue<int>Q;
bool bfs(){
    for(int i=0;i<=n+m+1;i++){
        cur[i]=h[i];dep[i]=-1;
    }
    while(!Q.empty())Q.pop();
    Q.push(s);dep[s]=0;
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(dep[u]!=-1||!c)continue;
            dep[u]=dep[x]+1;
            Q.push(u);
            if(u==t)return 1;
        }
    }
    return 0;
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
            if(used==mi)return used;
        }
    }
    return used;
}
void Dinic(){
    while(bfs())ans-=dfs(s,inf);
}
char tool[10000];
int main(){
    scanf("%d%d",&m,&n);
    s=0;t=n+m+1;
    for(int i=1;i<=m;i++){
        scanf("%d",&A[i]);Add(s,i,A[i]),Add(i,s,0),ans+=A[i];
        memset(tool,0,sizeof(tool));
        cin.getline(tool,10000);
        int ulen=0,tmp;
        while(sscanf(tool+ulen,"%d",&tmp)==1){
            Add(i,m+tmp,inf),Add(m+tmp,i,0);
            if(tmp==0)ulen++;
            else {
                while(tmp){
                    tmp/=10;
                    ulen++;
                }
            }
			ulen++;
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&A[i+m]);
        Add(i+m,t,A[i+m]);
        Add(t,i+m,0);
    }
    Dinic();
    bool fl=0;
    for(int i=1;i<=m;i++){
        if(dep[i]!=-1){
            if(fl)printf(" ");
            fl=1;
            printf("%d",i);
        }
    }
    puts("");
    fl=0;
    for(int i=1;i<=n;i++){
        if(dep[m+i]!=-1){
            if(fl)printf(" ");
            fl=1;
            printf("%d",i);
        }
    }
    puts("");
    printf("%d",ans);
    return 0;
}