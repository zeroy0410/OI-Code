#include<bits/stdc++.h>
using namespace std;

#define reg register
typedef long long ll;
#define rep(i,a,b) for(reg int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(reg int i=a,i##end=b;i>=i##end;--i)

char IO;
int rd(){
    int s=0,f=0;
    while(!isdigit(IO=getchar())) if(IO=='-') f=1;
    do s=(s<<1)+(s<<3)+(IO^'0');
    while(isdigit(IO=getchar()));
    return f?-s:s;
}

const int N=1e6+10;

int buf[22],l=0;
void wt(ll x){
    l=0;
    if(!x) {
        puts("0");
        return;
    }
    while(x) buf[++l]=x%10,x/=10;
    drep(i,l,1) putchar(buf[i]^'0');
    putchar('\n');
}



int n,m;
struct Edge{
    int from,to,nxt;
} e[N<<1];
int head[N],ecnt;
void AddEdge(int u,int v){
    e[++ecnt]=(Edge){u,v,head[u]};
    head[u]=ecnt;
}
#define erep(u,i) for(int i=head[u];i;i=e[i].nxt)

inline int Rev(int id){ return (id&1)?id+1:id-1; }
int isroot[N],vis[N],fa[N],fe[N],mk[N<<1],s[N],dfn;

void pre_dfs(int u,int f){
    vis[u]=++dfn;fa[u]=f;
    erep(u,i) {
        int v=e[i].to;
        if(v==f) continue;
        if(vis[v]) {
            if(vis[v]>vis[u]) continue;
            mk[i]=1;
            mk[Rev(i)]=1;
            s[u]++,s[v]--; // 预处理是否是环边
        } else {
            fe[v]=i;
            pre_dfs(v,u),s[u]+=s[v];
        }
    }
    if(s[u]) mk[fe[u]]=1,mk[Rev(fe[u])]=1;
}





int dp[N][2];

void dfs(int u,int f){
    dp[u][0]=1;
    erep(u,i) {
        int v=e[i].to;
        if(v==f) continue;
        if(fa[v]==u) dfs(v,u);  //暴力dp子树
        if(vis[v]<vis[u]) continue;
        if(!mk[i]) { //非环边
            dp[u][0]+=dp[v][0];
            dp[u][1]+=dp[v][1];
        } else { // 环边+1
            dp[u][1]+=dp[v][0];
        }
    }
}

int g[N][3];

void dfs2(int u,int f){
    erep(u,i) {
        int v=e[i].to;
        if(v==f) {
            if(mk[fe[u]]) g[u][1]+=dp[f][0]+g[f][0];
            else {
                g[u][0]+=g[f][0]+dp[f][0]-dp[u][0];
                g[u][1]+=g[f][1]+dp[f][1]-dp[u][1];
            }
        } else if(vis[v]<vis[u]) g[u][1]+=dp[v][0]+g[v][0];
    }      //换根dp，同样要考虑非树边
    erep(u,i) {
        int v=e[i].to;
        if(v==f) continue;
        if(fa[v]==u) dfs2(v,u);
    }
}




int main(){
    n=rd(),m=rd();
    rep(i,1,m) {
        int u=rd(),v=rd();
        AddEdge(u,v);
        AddEdge(v,u);
    }
    rep(i,1,n) if(!vis[i]) isroot[i]=1,pre_dfs(i,0);
    rep(i,1,n) if(isroot[i]) {
        dfs(i,0);
        dfs2(i,0);
    }
    rep(i,1,m) {
        int id=i*2-1,x=e[id].from,y=e[id].to;
        if(vis[x]>vis[y]) swap(x,y);
        ll res=0;
        if(mk[id]) res=1ll*(g[x][0]+dp[x][0])*dp[y][0];
        else {
            res=1ll*(g[x][0]+dp[x][0]-dp[y][0])*(dp[y][0]+dp[y][1]);
            res+=1ll*(g[x][1]+dp[x][1]-dp[y][1])*dp[y][0];
        }
        wt(res);
    }
    return 0;
}

