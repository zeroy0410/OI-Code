#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int M=3e5+5;
const double eps=1e-7;
 
void Rd(int &r)
{
    static char c;
    for(c=0;c<48;c=getchar());
    for(r=0;c>47;c=getchar())r=(r<<1)+(r<<3)+(c^48);
}
 
int n,m,A[M];
struct tree_edge
{
    int u,v,c;
    bool operator <(const tree_edge &b)const{return c>b.c;}
}Te[M];
 
namespace PCFish
{
    const int M=6e5+5;
    const int SQ=10005;
    struct Edge{int v,to;}E[M];int Head[M],e_tot;
    void Link(int u,int v){E[++e_tot]=(Edge){v,Head[u]},Head[u]=e_tot;}
    int Fa[M],dep[M],siz[M],son[M],tp[M],dfn[M],Dfnc;
 
    int fa[M];long long dsum[M];
    int getfa(int u){return fa[u]?fa[u]=getfa(fa[u]):u;}
    int tot;
    struct node
    {
        long long x,y;
        bool operator <(const node &b)const
        {
            if(x!=b.x)return x<b.x;
            return y>b.y;
        }
    }B[M];
    bool Fish(node &a,node &b,node &c){return 1.0*(b.y-a.y)/(b.x-a.x) - 1.0*(c.y-b.y)/(c.x-b.x) <= eps;}
    long long Calc(node &a,long long k){return k*a.x+a.y;}
    bool Btt(node &a,node &b,long long k){return Calc(a,k)>=Calc(b,k);}
    void Init_Tree()
    {
        tot=n;
        for(int i=1;i<n;i++)
        {
            ++tot;
            int u=getfa(Te[i].u),v=getfa(Te[i].v);
            fa[u]=fa[v]=tot;
            Link(tot,u);Link(tot,v);
        }
    }
    void Init_B()
    {
        for(int i=1;i<=tot;i++)dsum[i]=A[i],fa[i]=0;
        int fktot=n;
        for(int i=1;i<n;i++)
        {
            int u=getfa(Te[i].u),v=getfa(Te[i].v);
            ++fktot;
            fa[u]=fa[v]=fktot;dsum[fktot]=dsum[u]+dsum[v];
			cout<<dfn[fktot]<<' '<<Te[i].c<<' '<<dsum[fktot]*Te[i].c<<endl;
            B[dfn[fktot]]=(node){Te[i].c,dsum[fktot]*Te[i].c};
        }
    }
 
    void dfs_Init(int u)
    {
        siz[u]=1;
        for(int i=Head[u];i;i=E[i].to)
        {
            int v=E[i].v;
            Fa[v]=u;dep[v]=dep[u]+1;
            dfs_Init(v);
            siz[u]+=siz[v];if(siz[v]>siz[son[u]])son[u]=v;
        }
    }
    void re_dfs_Init(int u)
    {
        dfn[u]=++Dfnc;
        if(son[u])tp[son[u]]=tp[u],re_dfs_Init(son[u]);
        for(int i=Head[u];i;i=E[i].to)
        {
            int v=E[i].v;if(v==son[u])continue;
            tp[v]=v;re_dfs_Init(v);
        }
    }
 
    int sq;
    node Q[SQ][M/SQ];int Top[SQ],S[SQ],T[SQ];long long Lz[SQ];
    node Tmp[SQ];int nc;long long Nowans[SQ];
    long long Queryk(int x,long long k)
    {
        int L=1,R=Top[x]-1,ans=Top[x];
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(Btt(Q[x][mid],Q[x][mid+1],k))ans=mid,R=mid-1;
            else L=mid+1;
        }
        return Calc(Q[x][ans],k);
    }
    void Down(int k)
    {
        for(int i=S[k];i<=T[k];i++)B[i].y+=B[i].x*Lz[k];
        Lz[k]=0;
    }
    void Requeue(int k)
    {
        nc=0;Down(k);
        for(int i=S[k];i<=T[k];i++)Tmp[++nc]=B[i];
        sort(Tmp+1,Tmp+nc+1);
        Top[k]=0;
        for(int i=1;i<=nc;i++)
        {
            if(i>1 && Tmp[i].x==Tmp[i-1].x)continue;
            while(Top[k]>=2 && Fish(Q[k][Top[k]-1],Q[k][Top[k]],Tmp[i]))Top[k]--;
            Q[k][++Top[k]]=Tmp[i];
        }
        Nowans[k]=Queryk(k,0);
    }
 
    void Updateks(int L,int R,long long k)
    {
        int lk=L/sq,rk=R/sq;
        if(lk==rk)
        {
            Down(lk);
            for(int i=L;i<=R;i++)B[i].y+=k*B[i].x;
            Requeue(lk);
            return;
        }
        Down(lk);Down(rk);
        for(int i=L;i/sq==lk;i++)B[i].y+=k*B[i].x;
        for(int i=R;i/sq==rk;i--)B[i].y+=k*B[i].x;
        for(int i=lk+1;i<rk;i++)Lz[i]+=k,Nowans[i]=Queryk(i,Lz[i]);
        Requeue(lk),Requeue(rk);
    }
 
    void Update(int u,long long x)
    {
        long long delta=x-A[u];
        for(int g=u;g;g=Fa[tp[g]])
        {
            int t=tp[g];
            Updateks(dfn[t],dfn[g],delta);
        }
        A[u]=x;
    }
 
    long long Query()
    {
        long long ans=0;
        for(int i=0;i<=tot/sq;i++)ans=max(ans,Nowans[i]);
        return ans;
    }
 
    void Init()
    {
        Init_Tree();
        dfs_Init(tot);tp[tot]=tot;re_dfs_Init(tot);
        Init_B();
        sq=sqrt(tot+0.5)*0.2+1;
        for(int i=0;i<=tot/sq;i++)S[i]=max(1,i*sq),T[i]=min(tot,i*sq+sq-1),Requeue(i);
    }
 
    void Solve()
    {
        Init();
        for(int i=1;i<=m;i++)
        {
            int u,val;Rd(u),Rd(val);
            Update(u,val);
            printf("%lld\n",Query());
        }
    }
};
 
int main()
{
    Rd(n),Rd(m);
    for(int i=1;i<=n;i++)Rd(A[i]);
    for(int i=1;i<n;i++)Rd(Te[i].u),Rd(Te[i].v),Rd(Te[i].c);
    sort(Te+1,Te+n);
    PCFish::Solve();
    return 0;
}
