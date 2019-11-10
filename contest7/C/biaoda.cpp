#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 2e5+1;
const ll inf = 2e15;
int fa[N],n,tp,head[N],cnt;
int sz[N],mx[N],tot,rt,q[N],qq[N];
ll p1[N],q1[N],w[N],l[N],d[N],f[N];
bool vis[N];
struct nd{
    int ne,to,w;
}e[N*2];
void in(int x,int y,ll w){
    e[++cnt].to=y;e[cnt].ne=head[x];head[x]=cnt;e[cnt].w=w;
}
bool cmp(int x,int y){
    return l[x]>l[y];
}
void getrt(int x,int f){
    sz[x]=1;mx[x]=0;
    for(int i=head[x];i;i=e[i].ne)
    if(e[i].to!=f&&!vis[e[i].to]){
        int y=e[i].to;
        getrt(y,x);
        sz[x]+=sz[y];
        mx[x]=max(mx[x],sz[y]);
    }
    mx[x]=max(mx[x],tot-sz[x]);
    if(mx[x]<mx[rt])rt=x;
}
void dfs1(int x,int f){
    sz[x]=1;
    for(int i=head[x];i;i=e[i].ne)
    if(e[i].to!=f&&!vis[e[i].to]){
        dfs1(e[i].to,x);
        sz[x]+=sz[e[i].to];
    }
}
void dfs2(int x,int f){
    q[++q[0]]=x;
    for(int i=head[x];i;i=e[i].ne)
    if(e[i].to!=f&&!vis[e[i].to]){
        dfs2(e[i].to,x);
    }
}
db k(int x,int y){
    return (db)(f[x]-f[y])/(d[x]-d[y]);
}
void CDQ(int y,int x){
    dfs1(x,-1);//处理出以当前x为根的sz关系
    vis[x]=1;
    if(x!=1&&!vis[fa[x]]){//算x答案时，其fa的答案必须先算出来
        tot=sz[fa[x]];
        rt=0;
        getrt(fa[x],-1);
    :    CDQ(y,rt);
    }
    q[0]=0;dfs2(x,fa[x]);
    sort(q+1,q+q[0]+1,cmp);
    int top=0;
    for(int i=1,now=fa[x];i<=q[0];++i){
        while(now!=fa[y]&&l[q[i]]<=d[now]){
            while(top>1&&k(qq[top-1],qq[top])<=k(qq[top],now))top--;
            qq[++top]=now;now=fa[now];
        }
        if(!top)continue;
        int l=1,r=top;
        while(l!=r){
            int mid=l+r>>1;
            if(k(qq[mid],qq[mid+1])<p1[q[i]])r=mid;
            else    l=mid+1;
        }
        int j=q[i];
        f[j]=min(f[j],f[qq[l]]+(d[j]-d[qq[l]])*p1[j]+q1[j]);
    }
    for(int i=1;i<=q[0];++i)
    if(q[i]!=x&&l[q[i]]<=d[x]){
        int j=q[i];
        f[j]=min(f[j],f[x]+(d[j]-d[x])*p1[j]+q1[j]);
    }
    for(int i=head[x];i;i=e[i].ne)
    if(!vis[e[i].to]&&e[i].to!=fa[x]){
        tot=sz[e[i].to];
        rt=0;
        getrt(e[i].to,x);
        CDQ(e[i].to,rt);
    }
}
int main(){
//    freopen("ex_ticket2.in","r",stdin);
//    freopen("ex_ticket2.out","w",stdout);
    mx[0]=1e9;
    memset(f,0x3f,sizeof(f));
    f[1]=0;
    scanf("%d%d",&n,&tp);
    for(int i=2;i<=n;++i){
        scanf("%d%lld%lld%lld%lld",&fa[i],&w[i],&p1[i],&q1[i],&l[i]);
        in(fa[i],i,w[i]);in(i,fa[i],w[i]);
        d[i]=d[fa[i]]+w[i];
    }
    for(int i=2;i<=n;++i)l[i]=d[i]-l[i];
    tot=n;
    getrt(1,-1);
    CDQ(1,rt);
    for(int i=2;i<=n;++i)printf("%lld\n",f[i]);
	return 0;
}
