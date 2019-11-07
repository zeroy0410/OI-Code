#include<bits/stdc++.h>
#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;x++)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;x--)
#define FOO(x,y) for(int x=0,x##_=y;x<x##_;x++)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)
#define szf(x) sizeof(x)
#define clr(x,y) memset(x,y,szf(x))
#define sot(A,x) sort(A+1,A+x+1)
#define uni(A,x) {sort(A+1,A+x+1);x=unique(A+1,A+x+1)-A-1;}
#define pf printf
#define sf scanf
#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read2(x,y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define reads(A) scanf("%s",A)
#define readf(x) scanf("%lf",&x)
#define ll long long
#define db double
#define ct clock_t
#define ck clock
using namespace std;
bool mem1;
template<class T>bool tomin(T &x,T y){return y<x?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
template<class T>void read(T &x){
    x=0;
    int f=1;
    char c;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
const int maxn=1e5+5;
const int P=1e9+7;
int n,m;
int A[maxn];
ll pw[maxn];
namespace P10{
    int Calc(int s){
        int lst=0;
        int res=0;
        FOO(i,n)if(s>>i&1){
            if(A[i+1]>lst){
                res++;
                lst=A[i+1];
            }
        }return res;
    }
    void solve(){
        int ans=0;
        FOO(i,1<<n)ans=(ans+pw[Calc(i)])%P;
        pf("%d",ans);
    }
}
namespace P40{
    ll dp[maxn][25];
    int com[25][25];
    int c[maxn];
    void Add(int x,int d){
        while(x<=n){
            c[x]+=d;
            x+=x&-x;
        }
    }
    int query(int x){
        int res=0;
        while(x){
            res+=c[x];
            x&=x-1;
        }return res;
    }
    int pos[maxn];
    int R[maxn];
    ll pw[maxn];
    void solve(){
        FOR(i,1,n)pos[A[i]]=i;
        FOR(i,pw[0]=1,n)pw[i]=pw[i-1]*2%P;
        FOR(i,0,m)FOR(j,com[i][0]=1,i)com[i][j]=(com[i-1][j]+com[i-1][j-1])%P;
        dp[0][0]=1;
        ll ans=0;
        FOR(i,1,n){
            int res=query(A[i]);
            Add(A[i],-res);
            Add(A[i]+1,res);
            FOR(j,0,m){
                ll &v=dp[i][j];
                FOR(lst,0,i-1)if(A[lst]<A[i]){
                    int res=pw[query(A[lst])];
                    FOR(k,0,j)v=(v+dp[lst][k]*com[j][k]%P*res%P)%P;
                }
            }
            Add(A[i]+1,1);
        }
        FOR(i,1,n)ans=(ans+dp[i][m]*pw[query(A[i])])%P;
        pf("%lld",ans);
    }
}
namespace P100{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,L,mid
    #define rson rs,mid+1,R
    const int maxm=maxn<<2;
    void Mod(int &x,int y){
        if((x+=y)>=P)x-=P;
    }
    int Plus(int x,int y){
        Mod(x,y);
        return x;
    }
    struct YD{
        int val[maxm];
        int ad[maxm];
        void build(int p,int L,int R){
            ad[p]=1;
            val[p]=0;
            if(L==R)return;
            int mid=L+R>>1;
            build(lson);
            build(rson);
        }
        void Up(int p){
            val[p]=Plus(val[ls],val[rs]);
        }
        void Modi(int p,int a){
            ad[p]=(ll)ad[p]*a%P;
            val[p]=(ll)val[p]*a%P;
        }
        void Down(int p){
            if(ad[p]>1){
                Modi(ls,ad[p]);
                Modi(rs,ad[p]);
                ad[p]=1;
            }
        }
        void update(int p,int L,int R,int l,int r,int v){
            if(L==l&&R==r)return Modi(p,v);
            Down(p);
            int mid=L+R>>1;
            if(r<=mid)update(lson,l,r,v);
            else if(l>mid)update(rson,l,r,v);
            else update(lson,l,mid,v),update(rson,mid+1,r,v);
            Up(p);
        }
        void Change(int p,int L,int R,int x,int v){
            if(L==R)return Mod(val[p],v);
            Down(p);
            int mid=L+R>>1;
            if(x<=mid)Change(lson,x,v);
            else Change(rson,x,v);
            Up(p);
        }
        int query(int p,int L,int R,int l,int r){
            if(L==l&&r==R)return val[p];
            Down(p);
            int mid=L+R>>1;
            if(r<=mid)return query(lson,l,r);
            if(l>mid)return query(rson,l,r);
            return Plus(query(lson,l,mid),query(rson,mid+1,r));
        }
        void update(int l,int r,int v){
            if(l>r)return;
            update(1,0,n,l,r,v);
        }
        void Change(int x,int v){
            Change(1,0,n,x,v);
        }
        int query(int l,int r){
            if(l>r)return 0;
            return query(1,0,n,l,r);
        }
    }T[25];
    int dp[maxn][25];
    int com[25][25];
    void solve(){
        FOR(i,0,m)FOR(j,com[i][0]=1,i)com[i][j]=Plus(com[i-1][j],com[i-1][j-1]);
        FOR(i,0,m+1)T[i].build(1,0,n);
        FOR(i,0,m)T[i].Change(0,1);
        int ans=0;
        FOR(i,1,n){
            FOR(j,0,m)dp[i][j]=T[j].query(0,A[i]-1);
            FOR(k,0,m){
                int sum=0;
                FOR(j,0,k)Mod(sum,(ll)dp[i][j]*com[k][j]%P);
                T[k].Change(A[i],sum);
            }
            FOR(j,0,m+1)T[j].update(A[i]+1,n,2);
            T[m+1].Change(A[i],dp[i][m]);
        }
        ans=T[m+1].query(1,n);
        pf("%d",ans);
    }
}
bool mem2;
int main(){
    read2(n,m);
    FOR(i,1,n){
        pw[i]=1;
        FOO(j,m)pw[i]=pw[i]*i%P;
    }
    FOR(i,1,n)read(A[i]);
    if(n<=20)P10::solve();
    else if(n<=1000)P40::solve();
    else P100::solve();
    return 0;
}
