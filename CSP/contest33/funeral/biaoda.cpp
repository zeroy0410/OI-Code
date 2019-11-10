#include<bits/stdc++.h>
#define M 100005
using namespace std;
bool __1;
inline void Rd(int &x){
    char c;x=0;
    while((c=getchar())<48);
    do x=(x<<3)+(x<<1)+(c^48);
    while((c=getchar())>47);
}
int n,m;
struct edge{
    int to,fr;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b){
    E[++tote]=(edge){b,lst[a]};
    lst[a]=tote;
}
int top[M],sz[M],son[M],fa[M],dep[M];
int L[M],R[M],dfnt,dfnID[M];
void dfs1(int v,int f){
    sz[v]=1;
    for(int i=lst[v];i;i=E[i].fr){
        int u=E[i].to;
        if(u==f)continue;
        fa[u]=v;dep[u]=dep[v]+1;
        dfs1(u,v);
        sz[v]+=sz[u];
        if(sz[son[v]]<sz[u])son[v]=u;
    }
}
void dfs2(int v,int tp){
    L[v]=++dfnt;dfnID[dfnt]=v;top[v]=tp;
    if(son[v])dfs2(son[v],tp);
    for(int i=lst[v];i;i=E[i].fr){
        int u=E[i].to;
        if(u==son[v]||u==fa[v])continue;
        dfs2(u,u);
    }
    R[v]=dfnt;
}
int LCA(int a,int b){
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]])swap(a,b);
        a=fa[top[a]];
    }
    return dep[a]>dep[b]?b:a;
}
int Up(int a,int to){
    while(dep[top[a]]>to)a=fa[top[a]];
    return dfnID[L[a]-(dep[a]-to)];
}
void init(){
    dfs1(1,0);
    dfs2(1,1);
}
namespace Pbl{
#define lson T[p<<1]
#define rson T[p<<1|1]
    struct Seg1{
        struct Tree{
            int L,R;
            int cnt[3],sz;
            int cov;
            void clr(){cnt[0]=cnt[1]=cnt[2]=0;}
        }T[M<<2];
        void Up(int p){
            T[p].cnt[0]=lson.cnt[0]+rson.cnt[0];
            T[p].cnt[1]=lson.cnt[1]+rson.cnt[1];
            T[p].cnt[2]=lson.cnt[2]+rson.cnt[2];
        }
        void Down(int p){
            int&t=T[p].cov;
            if(t==-1)return;
            lson.cov=rson.cov=t;
            lson.clr();rson.clr();
            lson.cnt[t]=lson.sz;
            rson.cnt[t]=rson.sz;
            t=-1;
        }
        void Build(int l,int r,int p){
            T[p].L=l,T[p].R=r;T[p].cov=-1;
            T[p].clr();
            if(l==r){
                int x=dfnID[l];
                T[p].sz=son[fa[x]]==x;
                T[p].cnt[0]=T[p].sz;
                return;
            }
            int mid=(l+r)>>1;
            Build(l,mid,p<<1);
            Build(mid+1,r,p<<1|1);
            T[p].sz=lson.sz+rson.sz;
            Up(p);
        }
        void Upd(int l,int r,int c,int p){
            if(l>r)return;
            if(T[p].L==l&&T[p].R==r){
                T[p].clr();
                T[p].cov=c;
                T[p].cnt[c]=T[p].sz;
                return;
            }
            int mid=(T[p].L+T[p].R)>>1;
            Down(p);
            if(mid>=r)Upd(l,r,c,p<<1);
            else if(mid<l)Upd(l,r,c,p<<1|1);
            else Upd(l,mid,c,p<<1),Upd(mid+1,r,c,p<<1|1);
            Up(p);
        }
        int Query(int l,int r,int c,int p){
            if(l>r)return 0;
            if(T[p].L==l&&T[p].R==r)return T[p].cnt[c];
            int mid=(T[p].L+T[p].R)>>1;
            Down(p);
            if(mid>=r)return Query(l,r,c,p<<1);
            else if(mid<l)return Query(l,r,c,p<<1|1);
            else return Query(l,mid,c,p<<1)+Query(mid+1,r,c,p<<1|1);
        }
    }Tr1;
    struct TAG{
        int c,t;
    };
    struct Seg2{
        struct Tree{
            int L,R;
            TAG cov,poi;
            void Add(TAG x){
                if(cov.t<x.t)cov=x;
            }
            void Addp(TAG x){
                if(poi.t<x.t)poi=x;
            }
        }T[M<<2];
        void Down(int p){
            TAG t=T[p].cov;
            lson.Add(t);
            rson.Add(t);
            t=T[p].poi;
            lson.Addp(t);
            rson.Addp(t);
        }
        int TID[M];
        void Build(int l,int r,int p){
            T[p].L=l,T[p].R=r;
            T[p].cov.t=T[p].cov.c=0;
            T[p].poi.t=T[p].poi.c=0;
            if(l==r){
                TID[l]=p;
                return;
            }
            int mid=(l+r)>>1;
            Build(l,mid,p<<1);
            Build(mid+1,r,p<<1|1);
        }
        void Upd(int l,int r,TAG c,int p){
            if(l>r)return;
            if(T[p].L==l&&T[p].R==r){
                T[p].Add(c);
                return;
            }
            int mid=(T[p].L+T[p].R)>>1;
            Down(p);
            if(mid>=r)Upd(l,r,c,p<<1);
            else if(mid<l)Upd(l,r,c,p<<1|1);
            else Upd(l,mid,c,p<<1),Upd(mid+1,r,c,p<<1|1);
        }
        void Updp(int l,int r,TAG c,int p){
            if(l>r)return;
            if(T[p].L==l&&T[p].R==r){
                T[p].Addp(c);
                return;
            }
            int mid=(T[p].L+T[p].R)>>1;
            Down(p);
            if(mid>=r)Updp(l,r,c,p<<1);
            else if(mid<l)Updp(l,r,c,p<<1|1);
            else Updp(l,mid,c,p<<1),Updp(mid+1,r,c,p<<1|1);
        }
        void changep(int x,TAG c){T[TID[x]].poi=c;}
        int stk[M],top;
        TAG Query(int x){
            for(int p=TID[x]>>1;p;p>>=1)stk[++top]=p;
            while(top)Down(stk[top--]);
            return T[TID[x]].cov;
        }
        TAG Queryp(int x){
            for(int p=TID[x]>>1;p;p>>=1)stk[++top]=p;
            while(top)Down(stk[top--]);
            return T[TID[x]].poi;
        }
    }Tr2;
    TAG MAX(TAG a,TAG b){return a.t>b.t?a:b;}
    int Query(int a,int b,int c){
        int ans=0;
        while(top[a]!=top[b]){
            if(dep[top[a]]<dep[top[b]])swap(a,b);
            int d=top[a],t=fa[d];
            ans+=Tr1.Query(L[d]+1,L[a],c,1);
            ans+=MAX(Tr2.Query(L[t]),Tr2.Queryp(L[d])).c==c;
            a=t;
        }
        if(dep[a]<dep[b])swap(a,b);
        ans+=Tr1.Query(L[b]+1,L[a],c,1);
        return ans;
    }
    void change(int a,int b,int c1,int c2,int t1,int t2){
        if(son[a])Tr1.Upd(L[son[a]],L[son[a]],c2,1);
        if(son[b])Tr1.Upd(L[son[b]],L[son[b]],c2,1);
        while(top[a]!=top[b]){
            if(dep[top[a]]<dep[top[b]])swap(a,b);
            int d=top[a],t=fa[d];
            Tr1.Upd(L[d]+1,L[a],c1,1);
            Tr1.Upd(L[son[t]],L[son[t]],c2,1);
            Tr2.Upd(L[d],L[a],(TAG){c2,t2},1);
            Tr2.changep(L[d],(TAG){c1,t1});
            a=t;
        }
        if(dep[a]<dep[b])swap(a,b);
        if(b>1)Tr1.Upd(L[b],L[b],c2,1),Tr2.changep(L[b],(TAG){c2,t2});
        Tr1.Upd(L[b]+1,L[a],c1,1);
        Tr2.Upd(L[b],L[a],(TAG){c2,t2},1);
    }
    void solve(){
        Tr1.Build(1,n,1);Tr2.Build(1,n,1);
        for(int i=1,op,x,y,z,c1,c2;i<=m;i++){
            Rd(op),Rd(x),Rd(y);
            z=LCA(x,y);
            if(op==1){
                Rd(c1);
                printf("%d\n",Query(x,y,c1));
            }else if(op==2){
                Rd(c1),Rd(c2);
                change(x,y,c1,c2,i*2,i*2-1);
            }else{
                Rd(c1);
                if(x==y)Tr1.Upd(1,n,c1,1),Tr2.Updp(1,n,(TAG){c1,i<<1},1);
                else if(z==y){
                    int t=Up(x,dep[z]+1);
                    Tr1.Upd(2,L[t]-1,c1,1);
                    Tr1.Upd(R[t]+1,n,c1,1);
                    Tr2.Updp(2,L[t]-1,(TAG){c1,i<<1},1);
                    Tr2.Updp(R[t]+1,n,(TAG){c1,i<<1},1);
                }else Tr1.Upd(L[y]+1,R[y],c1,1),Tr2.Updp(L[y]+1,R[y],(TAG){c1,i<<1},1);
            }
        }
    }
}
bool __2;
int main(){
    freopen("funeral.in","r",stdin);
    freopen("funeral.out","w",stdout);
    Rd(n);
    for(int i=1,a,b;i<n;i++){
        Rd(a),Rd(b);
        addedge(a,b);
        addedge(b,a);
    }
    init();
    Rd(m);
    Pbl::solve();
    return 0;
}