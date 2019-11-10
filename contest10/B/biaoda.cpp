#include<bits/stdc++.h>
#define REP(i,a,b) for(int i=(a);i<=(b);i++)
#define PER(i,a,b) for(int i=(a);i>=(b);i--)
#define RVC(i,S) for(int i=0;i<(S).size();i++)
#define RAL(i,u) for(int i=fr[u];i!=-1;i=e[i].next)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
} 
struct edge {
    int next,to;
};
const int maxn=(int)(2e5)+5;
const double eps=1e-8;
int fr[maxn];
int vi[maxn];
int col[maxn];
int stk[maxn];
int dep[maxn];
int fa[maxn][22];
int ai[maxn],bi[maxn];
edge e[maxn<<1];
int tote,top,co;
inline void addone(int u,int v) {
    ++tote;
    e[tote].next=fr[u];fr[u]=tote;e[tote].to=v;
}
inline void addedge(int u,int v) {
    addone(u,v);addone(v,u);
}
int rt;
void _dfs(int x,int f) {
    vi[x]=1;
    RAL(i,x) if(e[i].to!=f) {
        if(!vi[e[i].to]) _dfs(e[i].to,x); else rt=x;
    }
}
int pi[maxn],tot;
void dfs(int x,int f) {
    stk[++top]=x;fa[x][0]=f;
    RAL(i,x) if(e[i].to!=f) {
        if(stk[1]==e[i].to) {
            tot=top;REP(i,1,tot) pi[i]=stk[i];
        } else dfs(e[i].to,x);
    } top--;
}
 
struct node {
    int a[6];
 
    node() {memset(a,0,sizeof(a));}
 
    inline void add(int x,int y) {
        a[0]++;a[1]+=x;a[2]+=y;
        a[3]+=x*x;a[4]+=y*y;a[5]+=x*y;
    }
} c[maxn],g[maxn];
 
node operator + (node a,node b) {
    REP(i,0,5) a.a[i]+=b.a[i];return a;
}
 
node operator - (node a,node b) {
    REP(i,0,5) a.a[i]-=b.a[i];return a;
}
 
node operator * (node a,int x) {
    REP(i,0,5) a.a[i]*=x;return a;
}
 
void chk(int x,int f) {
    fa[x][0]=f;col[x]=co;dep[x]=dep[f]+1;
    c[x]=c[f];c[x].add(ai[x],bi[x]);
    REP(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    RAL(i,x) if(e[i].to!=f && !vi[e[i].to]) chk(e[i].to,x);
}
inline int LCA(int u,int v) {
    if(dep[u]>dep[v]) swap(u,v);
    PER(i,20,0) if(dep[u]<=dep[fa[v][i]]) v=fa[v][i];
    if(u==v) return u;
    PER(i,20,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
 
inline double calc(node u) {
    double n=u.a[0],X=u.a[1],Y=u.a[2],X2=u.a[3],Y2=u.a[4],S=u.a[5];
    double Xb=X/n,Yb=Y/n;
    double A=X2+n*Xb*Xb-2*X*Xb;
    double B=2*X*Yb-2*n*Xb*Yb-2*S+2*Xb*Y;
    double C=Yb*Yb*n-2*Y*Yb+Y2;
    double ai=-4,bi=4*(A+C),ci=B*B-4*A*C;
    return (-bi+sqrt(bi*bi-4*ai*ci))/2/ai;
}
 
int main() {
	freopen("inv6.in","r",stdin);
	freopen("inv.out","w",stdout);
    int n,m;
    read(n);read(m);
    memset(fr,-1,sizeof(fr));
    REP(i,1,n) read(ai[i]),read(bi[i]);
    REP(i,1,m) {
        int u,v;
        read(u);read(v);
        addedge(u,v);
    } rt=1;_dfs(1,0);dfs(rt,0);if(!tot) pi[tot=1]=1;
    memset(vi,0,sizeof(vi));
    REP(i,1,tot) cout<<pi[i]<<endl,vi[pi[i]]=1;
    REP(i,1,tot) co=i,chk(pi[i],0),g[i]=g[i-1],g[i].add(ai[pi[i]],bi[pi[i]]);
    int q;
    read(q);
    REP(i,1,q) {
        int u,v;
        read(u);read(v);
        if(col[u]==col[v]) {
            int h=LCA(u,v);
            node s=c[u]+c[v]-c[fa[h][0]]-c[h];
            printf("%.5lf\n",calc(s));
        } else {
            if(col[u]>col[v]) swap(u,v);
            node s=c[u]+c[v]+g[col[v]-1]-g[col[u]];
            node t=c[u]+c[v]+g[tot]-g[col[v]]+g[col[u]-1];
            printf("%.5lf\n",min(calc(s),calc(t)));
        }
    }
    return 0;
}
