#include<bits/stdc++.h>
using namespace std;
#define LL long long
const double eps=1e-7;
const int Maxn=800;
const double inf=2147483647;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}
int h[Maxn],st,ed,n,m,n1,m1;
struct Edge{int y,next;double d;}e[210000];
struct Edge1{int y,s,t,next;}e1[100010];
int len=1,last[Maxn];
void ins(int x,int y,double d)
{
    int t=++len;
    e[t].y=y;e[t].d=d;
    e[t].next=last[x];last[x]=t;
}
int len1=0,last1[Maxn];
void ins1(int x,int y,int s,int t)
{
    int t1=++len1;
    e1[t1].y=y;e1[t1].s=s;e1[t1].t=t;
    e1[t1].next=last1[x];last1[x]=t1;
}
void addedge(int x,int y,double d){ins(x,y,d);ins(y,x,0);}
bool bfs()
{
    queue<int>q;
    memset(h,0,sizeof(h));h[st]=1;
    q.push(st);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=last[x];i;i=e[i].next)
        if(e[i].d>eps&&!h[e[i].y])h[e[i].y]=h[x]+1,q.push(e[i].y);
    }
    return h[ed];
}
double dfs(int x,double f)
{
    if(x==ed)return f;
    double s=0.0,t;
    for(int i=last[x];i;i=e[i].next)
    {
        int y=e[i].y;
        if(h[y]==h[x]+1&&e[i].d>eps&&s<f)
        {
            t=dfs(y,min(f-s,e[i].d));
            s+=t;e[i^1].d+=t;e[i].d-=t;
        }
    }
    if(s<=eps)h[x]=0;
    return s;
}
double f[Maxn],dis[Maxn];
bool in[Maxn];
bool spfa(int Ed,double v)
{
    memset(in,false,sizeof(in));
    for(int i=1;i<=n;i++)dis[i]=inf;dis[n]=0.0;
    queue<int>q;
    q.push(n);
    while(!q.empty())
    {
        int x=q.front();q.pop();in[x]=false;
        for(int i=last1[x];i;i=e1[i].next)
        {
            int y=e1[i].y;double d=(double)(e1[i].t)-(double)(e1[i].s)*v;
            if(dis[x]+d<dis[y])
            {
                dis[y]=dis[x]+d;
                if(dis[Ed]<=eps)return true;
                if(!in[y])in[y]=true,q.push(y);
            }
        }
    }return dis[Ed]<=eps;
}
bool same(double x,double y){return abs(x-y)<=eps;}
int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        int a=read(),b=read(),t=read(),s=read();
        ins1(a,b,s,t);
    }
    m1=read();n1=read();
    for(int i=1;i<=n1;i++)
    {
        double l=0.0,r=10.0;
        while(r-l>eps)
        {
            double mid=(l+r)/2.0;
            if(spfa(i,mid))r=mid-eps;
            else l=mid+eps;
        }
        if(same(dis[i],inf))f[i]=inf;
        else f[i]=r+eps;
        cout<<f[i]<<endl;
    }
    st=n1+1;ed=st+1;
    for(int i=1;i<=m1;i++)
    {
        int u=read(),v=read();
        addedge(u,v,inf);
        if(same(f[u],inf)&&same(f[v],inf)){puts("-1");return 0;}
    }
    for(int i=1;i<=n1;i++)
    if(i&1)addedge(st,i,f[i]);
    else addedge(i,ed,f[i]);
    double ans=0.0;
    while(bfs())ans+=dfs(st,inf);
    printf("%.1lf",ans);
}
