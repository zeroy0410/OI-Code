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
const int N=5010,P=998244353;
bool be;
int n,m;
struct Edge{
    int to,nxt;
} e[N<<1];
int head[N],ecnt;
void AddEdge(int u,int v) {
    e[++ecnt]=(Edge){v,head[u]};
    head[u]=ecnt;
}
#define erep(u,i) for(int i=head[u];i;i=e[i].nxt) 
ll Inv[N],fac[N];
inline ll C(int n,int m) {
    if(n<m||n<0||m<0) return 0;
    return fac[n]*Inv[m]%P*Inv[n-m]%P;
}
int sz[N];
ll dp[N][N],tmp[N];
void dfs(int u,int f) {
    sz[u]=0;
    dp[u][0]=1;
    erep(u,i) {
        int v=e[i].to;
        if(v==f) continue;
        dfs(v,u);
        rep(j,0,sz[u]) tmp[j]=dp[u][j],dp[u][j]=0;
        rep(j,0,sz[u]) 
            rep(k,0,sz[v]) 
                dp[u][j+k]=(dp[u][j+k]+tmp[j]*dp[v][k]%P*C(j+k,k)%P*C(sz[u]-j+sz[v]-k,sz[u]-j))%P; 
                //合并时注意要乘上组合数
        sz[u]+=sz[v]; 
    }
    rep(j,0,sz[u]) tmp[j]=dp[u][j],dp[u][j]=0;
    rep(j,0,sz[u]) dp[u][j+1]=tmp[j]*(j+1)%P; // 分离 1
    drep(j,sz[u],1) tmp[j-1]=(tmp[j-1]+tmp[j])%P;
    rep(j,0,sz[u]) dp[u][j]=(dp[u][j]+tmp[j]*m)%P;  // 分离2，前缀和即可
    sz[u]++;
}
bool ed;
int main(){
    freopen("random.in","r",stdin),freopen("random.out","w",stdout);
    n=rd(),m=rd();
    fac[0]=Inv[0]=fac[1]=Inv[1]=1;
    rep(i,2,n) {
        fac[i]=fac[i-1]*i%P;
        Inv[i]=(P-P/i)*Inv[P%i]%P;
    }
    rep(i,2,n) Inv[i]=Inv[i-1]*Inv[i]%P;
    rep(i,2,n) {
        int u=rd(),v=rd();
        AddEdge(u,v);
        AddEdge(v,u);
    }
    dfs(1,0);
    printf("%lld\n",dp[1][0]);
    fclose(stdin),fclose(stdout);
    return 0;
}
