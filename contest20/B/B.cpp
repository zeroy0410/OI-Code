#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n,A[M],h[M],tt;
int L,U;
struct edge{
    int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
    G[++tt]=(edge){h[a],b,c};
    h[a]=tt;
}
struct P20{
    LL dis[M];
    int fa[M][14],dep[M];
    int LCA(int a,int b){
        if(dep[a]>dep[b])swap(a,b);
        int step=dep[b]-dep[a];
        for(int i=13;i>=0;i--)
            if(step&1<<i)b=fa[b][i];
        if(a==b)return a;
        for(int i=13;i>=0;i--)
            if(fa[a][i]!=fa[b][i])
                a=fa[a][i],b=fa[b][i];
        return fa[a][0];
    }
    void dfs(int x,int f,LL ds,int d){
        fa[x][0]=f;dis[x]=ds;dep[x]=d;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(u==f)continue;
            dfs(u,x,ds+c,d+1);
        }
    }
    void solve(){
        dfs(1,0,0,0);
        for(int j=1;j<=13;j++)
            for(int i=1;i<=n;i++)
                fa[i][j]=fa[fa[i][j-1]][j-1];
        double ans=-1e9;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int lca=LCA(i,j);
                int ct=dep[i]-dep[lca]+dep[j]-dep[lca];
                if(ct<L||ct>U)continue;
                LL ds=dis[i]-dis[lca]+dis[j]-dis[lca];
                ans=max(ans,1.0*ds/ct);
            }
        }
        printf("%.3lf\n",ans);
    }
}p20;
struct P50{
    int qc;
    LL sum[M];
    void dfs(int x,int f,LL ds){
        sum[++qc]=ds;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to;
            if(u==f)continue;
            dfs(u,x,ds+G[i].co);
        }
    }
    struct node{
        LL x,y;
    }stk[M];
    int l,r;
    bool cmp(node a,node b,node c){
        return 1.0*(c.y-a.y)/(c.x-a.x)<=1.0*(a.y-b.y)/(a.x-b.x);
    }
    double calc(int i,int k){
        if(k<l||k>r)return -1;
        return 1.0*(sum[i]-stk[k].y)/(i-stk[k].x);
    }
    void solve(){
        qc=0;
        dfs(1,0,0);
        double ans=-1e9;
		l=1;r=0;
        int cur=1;
        for(int i=1;i<=n;i++){
            while(i-cur>=L){
                while(l<=r-1&&cmp(stk[r],stk[r-1],(node){cur,sum[cur]}))r--;
                stk[++r]=(node){cur,sum[cur]};cur++;
            }
            while(l<=r&&i-stk[l].x>U)l++;
            if(l<=r){
                int tl=l,tr=r,tmp=l;
                while(tl<=tr){
                    int mid=(tl+tr)>>1;
                    if(calc(i,mid)>=calc(i,mid-1)&&calc(i,mid)>=calc(i,mid+1)){
                        tmp=mid;
                        break;
                    }
                    else if(calc(i,mid)<=calc(i,mid-1)&&calc(i,mid)>=calc(i,mid+1))tr=mid-1;
                    else tl=mid+1;
                }
				ans=max(ans,calc(i,tmp));
			}
        }
        printf("%.3lf\n",ans);
    }
}p50;
LL mx;
struct P100{
    struct YD{
        struct node{
            int l,r;LL mi;
        }tree[M<<2];
        int tid[M];
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
        void up(int p){
            fa.mi=min(lson.mi,rson.mi);
        }
        void build(int l,int r,int p){
            fa.l=l;fa.r=r;fa.mi=1e18;
            if(l==r){
                if(l==0)fa.mi=0;
                tid[l]=p;
                return;
            }
            int mid=(l+r)>>1;
            build(l,mid,p<<1);
            build(mid+1,r,p<<1|1);
            up(p);
        }
        void update(int x,LL y){
            bool f=0;int p=tid[x];
            if(y==1e18)tree[p].mi=1e18,f=1;
            else if(y<tree[p].mi)f=1,tree[p].mi=y;
            if(!f)return;
            for(p>>=1;p;p>>=1)up(p);
        }
        LL query(int l,int r,int p){
            if(fa.l==l&&fa.r==r)return fa.mi;
            int mid=(fa.l+fa.r)>>1;
            if(r<=mid)return query(l,r,p<<1);
            else if(l>mid)return query(l,r,p<<1|1);
            return min(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
        }
#undef fa
#undef lson
#undef rson 
    }Tr;
    double mid;
    int sz[M],rt,mi,mxd,tot,srt;
    bool solved[M];
    vector<int>wk[M];
    void dfs_rt(int x,int f){
        sz[x]=1;int mm=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to;
            if(u==f||solved[u])continue;
            dfs_rt(u,x);
            sz[x]+=sz[u];
            mm=max(mm,sz[u]);
        }
        mm=max(mm,tot-sz[x]);
        if(mm<mi)mi=mm,rt=x;
    }
    bool dfs(int x,int fa,LL ds,int dep,bool f){
        // cout<<x<<endl;
        if(dep>U)return 0;
        if(!f){
            if(Tr.query(max(0,L-dep),U-dep,1)<=ds-mid*dep)return 1;
        }else {
            Tr.update(dep,mid*dep-ds);
        }
        mxd=max(mxd,dep);
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to,c=G[i].co;
            if(u==fa||solved[u])continue;
            if(dfs(u,x,ds+1LL*c*5000,dep+1,f))return 1;
        }return 0;
    }
    bool ask_ans(int x){
        mxd=0;bool f=0;
        for(int i=h[x];i;i=G[i].nxt){
            int u=G[i].to;
            if(solved[u])continue;
            if(dfs(u,x,1LL*5000*G[i].co,1,0)){f=1;break;}
            dfs(u,x,1LL*5000*G[i].co,1,1);
        }
        f|=Tr.query(L,U,1)<=0;
        for(int i=1;i<=mxd;i++)Tr.update(i,1e18);
        return f;
    }
    bool dfssolve(int x){
		bool f=ask_ans(x);solved[x]=1;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(solved[u])continue;
			tot=sz[u],mi=2e9,dfs_rt(u,x);
			wk[x].push_back(rt);
			f|=dfssolve(rt);
		}
        return f;
	}
    bool dfsSv(int x){
        if(ask_ans(x))return 1;solved[x]=1;
        for(int i=0,ss=wk[x].size();i<ss;i++)
            if(dfsSv(wk[x][i]))return 1;
        return 0;
    }
    bool check(){
        memset(solved,0,sizeof(solved));
        if(!srt){
            tot=n;mi=2e9,dfs_rt(1,0);
            srt=rt;return dfssolve(rt);
        }else return dfsSv(srt);
    }
    void solve(){
        Tr.build(0,U,1);
        LL l=0,r=mx*5000;
        LL ans=0;
        while(l<=r){
            mid=(l+r)>>1;
            // cout<<1.0*mid/5000<<endl;
            if(check())l=mid+1,ans=mid;
            else r=mid-1;
        }
        printf("%.3lf\n",1.0*ans/5000);
    }
}p100;
int in[M];
int main(){
    freopen("rebuild.in","r",stdin);
    freopen("rebuild.out","w",stdout);
    scanf("%d",&n);
    scanf("%d%d",&L,&U);
    bool flag=1;
    for(int i=1,a,b;i<n;i++){
        LL c;
        scanf("%d%d%lld",&a,&b,&c);
        Add(a,b,c);mx=max(mx,c);
        Add(b,a,c);
        in[a]++;in[b]++;
    }
    int cc=0;
    for(int i=1;i<=n;i++){
        if(in[i]!=2&&in[i]!=1)flag=0;
        if(in[i]==1)cc++;
    }
    if(cc!=2)flag=0;
    if(n<=5000)p20.solve();
    else if(flag)p50.solve();
    else p100.solve();
    return 0;
}
