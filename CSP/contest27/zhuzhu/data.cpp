#include<bits/stdc++.h>

#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;++x)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;--x)
#define FOR_(x,y,z,s) for(int x=y,x##_=z;x<=x##_;x+=s)
#define FOR__(x,y,z) for(int x=y,x##_=z;x<=x##_;x<<=1)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)

#define clr(x,y) memset(x,y,sizeof(x))
#define szf(x) sizeof(x)
#define min3(x,y,z) min(min(x,y),z)
#define max3(x,y,z) max(max(x,y),z)

#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read(x),read(y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define reads(str) sf("%s",str)
#define ts (*this)
#define sf scanf
#define pf printf

#define ll long long
#define ull unsigned long long
#define db double
#define ct clock_t
#define ck() clock()



template<class T>bool tomin(T &x,T y){return x>y?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
template<class T>void read(T &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}

#define pf printf
#define rd rand()
#define ph(x,y,z) edge[x].push_back((Edge){y,z});
#define p1(x) printf("%d\n",x)
#define p2(x,y) printf("%d %d\n",x,y)
#define p3(x,y,z) printf("%d %d %d\n",x,y,z)
#define p4(x,y,z,w) printf("%d %d %d %d\n",x,y,z,w)
#define p5(x,y,z,w,u) printf("%d %d %d %d %d\n",x,y,z,w,u)
#define s1(x) scanf("%d",&x)
#define s2(x,y) scanf("%d%d",&x,&y)
#define s3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define rf random_shuffle
#define ll long long
using namespace std;
bool mem1;
namespace tree{
    const int maxn=2e5+5;
    struct Edge{
        int e,to;
    }edge[maxn<<1];
    int head[maxn],tot;
    void Add(int x,int y){
        edge[++tot]=(Edge){y,head[x]};
        head[x]=tot;
    }
    int L[maxn],R[maxn];
    int dep[maxn],fa[maxn][20];
    void dfs(int u,int f){
        dep[u]=dep[f]+1;
        fa[u][0]=f;
        L[u]=++tot;
        EOR(u,v)if(v!=f)dfs(v,u);
        R[u]=tot;
    }
    bool Check(int x,int y){
        return L[x]<=L[y]&&R[x]>=L[y];
    }
    void solve(){
        int n=10;
        p1(n);
        FOR(i,2,n){
            int x=rd%(i-1)+1;
            Add(x,i);
            Add(i,x);
            p2(x,i);
        }
        dfs(1,0);
        FOR(j,1,18)FOR(i,1,n)fa[i][j]=fa[fa[i][j-1]][j-1];
        // FOR(i,2,n)p2(i-1,i);
        int m=100;
        p1(m);
        // FOR(i,1,m-1)p3(0,1,2147483647);
        // p4(1,1,n,1);
        FOR(i,1,m){
            if(rd%3==0){
                p3(0,rd%n+1,rd%100+1);
                // p3(0,1,2147483647);
            }
            else{
                // p4(1,1,n,1);
                int k=rd%6+1;
                pf("1 %d",k);
                FOR(j,1,k){
                    int u=rd%n+1;
                    int d=rd%dep[u];
                    int p=u;
                    DOR(k,18,0)if(d>>k&1)p=fa[p][k];
                    pf(" %d %d",u,p);
                }puts("");
            }
        }
    }
}
namespace XOR{
    void solve(){
        int n=1000000000,m=200000;
        p2(n,m);
        while(m--){
            int x1,y1,x2,y2;
            do{
                x1=rd%n+1;
                y1=rd%n+1;
                x2=rd%n+1;
                y2=rd%n+1;
            }while(x1>x2||y1>y2);
            p4(x1,y1,x2,y2);
        }
    }
}
namespace piano{
    void solve(){
        int n=1000000,m=1e8;
        p1(n);
        FOR(i,1,n)p3(m-rd%m,m-rd%m,m-rd%m);
    }
}
namespace Toy_Blocks{
    void solve(){
        int n=100;
        p1(n);
        int l=0;
        FOR(i,1,n){
            p2(l+=rd%10+1,rd%20+1);
        }
    }
}
namespace nue{
    void solve(){
        int n=3,S=rd%n+1;
        p2(n,S);
        FOR(i,1,n)pf("%d ",rd%2);puts("");
        FOR(i,1,n-1)p2(rd%n+1,rd%n+1);
    }
}
namespace hina{
    void solve(){
        int n=1e5;
        int cnt=0;
        FOR(i,1,n){
            if(cnt&&rd%2){
                cnt--;
                putchar(')');
            }else{
                cnt++;
                putchar('(');
            }
        }
        FOR(i,1,cnt)putchar(')');
    }
}
namespace kanako{
    void Print(int n){
        pf("%d",rd%9+1);
        DOR(i,n,1)pf("%d",rd%10);
        puts("");
    }
    void solve(){
        int l,r,P,V=1e6;
        do{
            l=rd%100000+1;
            r=V-rd%1;
        }while(l>=r);
        Print(l);
        Print(r);
        P=rd%100+2;
        p1(P);
    }
}
namespace magic{
    void solve(){
        int n=rd%5+2;
        p2(n,1);
        FOR(i,2,n)p2(rd%(i-1)+1,i);
    }
}
namespace gift{
    void solve(){
        int n=10000,q=min(n,(int)1e5),V=1e9;
        p1(n);
        FOR(i,1,n)p2(rd%V+1,rd%V+1);
        p1(q);
        FOR(i,1,q){
            int l,r;
            do{
                l=rd%n+1;
                r=rd%n+1;
            }while(l>r);
            p2(l,r);
        }
    }
}
namespace dream{
    void solve(){
        int n=2,q=5,k=rd%(1<<q);
        p3(n,k,q);
        q=1<<q;
        FOR(i,1,n)pf("%d ",rd%q);
    }
}
namespace Prime_Query{
    void solve(){
        int T=2;
        p1(T);
        while(T--){
            int n=8,Q=10,V=1e4;
            p2(n,Q);
            FOR(i,1,n)pf("%d ",rd%V+1);
            puts("");
            int l,r;
            while(Q--){
                switch(rd%3){
                    case 0:
                        pf("A %d %d\n",rd%100+1,rd%n+1);
                        break;
                    case 1:
                        do l=rd%n+1,r=rd%n+1;
                        while(l>r);
                        pf("R %d %d %d\n",rd%V+1,l,r);
                        break;
                    case 2:
                        do l=rd%n+1,r=rd%n+1;
                        while(l>r);
                        pf("Q %d %d\n",l,r);
                        break;
                }
            }
        }
    }
}
namespace delivery{
    void solve(){
        while(rd%3){
            int n=5,m=5,Q=5,V=1e4+1;
            p2(n,m);
            FOR(i,2,n)pf("%d ",rd%V+1);puts("");
            FOR(i,1,m)p3(rd%n+1,rd%n+1,rd%V+1);
            p1(Q);
            while(Q--)p2(rd%n+1,rd%n+1); 
        }
    }
}
namespace path{
    void solve(){
        int T=1;
        p1(T);
        while(T--){
            int n=5e4,m=5e4,Q=5e4;
            p3(n,m,Q);
            FOR(i,1,m)p3(rd%n+1,rd%n+1,rd%10000000+1);
            FOR(i,1,Q)pf("%d\n",i);
        }
    }
}
namespace collect{
    void solve(){
        int n=5,m=7,k=10,q=5;
        p4(n,m,k,q);
        FOR(i,1,n){
            FOR(j,1,k)pf("%d",rd%2);
            puts("");
        }
        FOR(i,1,m)p2(rd%n+1,rd%n+1);
        FOR(i,1,k)pf("%d ",rd%100+1);
        puts("");
        FOR(i,1,q){
            // pf("%d %d %d %lf %d %d\n",rd%10+1,rd%n+1,rd%n+1,(db)(rd%101)/100,rd%100+1,rd%10+1);
            pf("%d %d %d %lf %d %d\n",rd%100+1,rd%n+1,rd%n+1,(db)(rd%3)/2,rd%100+1,rd%100+1);
        }
    }
}
namespace shrew{
    void solve(){
        int n=100-rd%10,m=100-rd%10;
        p2(n,m);
        FOR(i,1,n){
            FOR(j,1,m)pf("%d ",rd%100);
            puts("");
        }
    }
}
namespace Stack{
    const int maxn=3e5+5;
    int sz[maxn];
    void solve(){
        int n=300000;
        p1(n);
        int v,w;
        FOR(i,1,n){
            loop:;
            switch(rd%3){
                case 0:
                    pf("a %d\n",v=rd%i);
                    sz[i]=sz[v]+1;
                    break;
                case 1:
                    v=-1;
                    FOR(j,0,i-1)if(sz[j]){
                        v=j;
                        break;
                    }
                    if(v==-1)goto loop;
                    do v=rd%i;
                    while(sz[v]==0);
                    pf("b %d\n",v);
                    sz[i]=sz[v]-1;
                    break;
                case 2:
                    // goto loop;
                    pf("c %d %d\n",v=rd%i,rd%i);
                    sz[i]=sz[v];
                    break;
                // case 3:
                //     pf("c %d %d\n",v=rd%i,rd%i);
                //     sz[i]=sz[v];
                //     break;
                // case 4:
                //     pf("c %d %d\n",v=rd%i,rd%i);
                //     sz[i]=sz[v];
                //     break;
                // case 5:
                //     pf("c %d %d\n",v=rd%i,rd%i);
                //     sz[i]=sz[v];
                //     break;
                // case 6:
                //     pf("c %d %d\n",v=rd%i,rd%i);
                //     sz[i]=sz[v];
                //     break;
            }
        }
    }
}
namespace maze{
    void solve(){
        int n=30,m=30,k=5,H=1;
        p4(n,m,k,H);
        bool flag=0;
        int sx=rd%n+1,sy=rd%m+1;
        FOR(i,1,n){
            FOR(j,1,m){
                if(i==sx&&j==sy)putchar('$');
                else{
                    int x=rd%20;
                    if(x<=3)putchar('.');
                    else if(x<=12)putchar('#');
                    else if(x<=13)putchar('@');
                    else putchar(rd%k+'A');
                }
            }
            puts("");
        }
        FOR(i,0,(1<<k)-1)pf("%d ",rd%1000+1);
    }
}
namespace C{
    void solve(){
        int n=6;
        p1(n);
        FOR(i,1,n)putchar(rd%2?'(':')');
    }
}
namespace manager{
    void solve(){
        int n=1e5;
        p1(n);
        FOR(i,1,n-1)pf("%d ",rd%i);puts("");
        int q=1e5;
        p1(q);
        while(q--){
            pf("%s %d\n",rd%2?"install":"uninstall",rd%n);
        }
    }
}
namespace Bridge_crossing{
    void solve(){
        int T=10;
        p1(T);
        while(T--){
            int n=2;
            p1(n);
            FOR(i,1,n)pf("%d ",rd%100000+1);
            puts("");
        }
    }
}
namespace Chef_and_the_Number_Sequence{
    void solve(){
        int T=1;
        p1(T);
        while(T--){
            int n=1,m=rd%16+1,L=rd%n+1;
            p3(n,m,L);
            FOR(i,1,n)pf("%d ",rd%m+1);
            puts("");
        }
    }
}
namespace Tree{
    void solve(){
        int n=12,L=rd%n+1,R=rd%n+L;
        p3(n,L,R);
        FOR(i,2,n)pf("%d ",rd%(i-1)+1);
    }
}
namespace bet{
    void solve(){
        int n=100000000-rd%100;
        int R=20;
        int Q=5;
        int T=10000;
        p4(n,R,Q,T);
    }
}
namespace tree20190908{
    void solve(){
        freopen("in.txt","w",stdout);
        int n=2e6,m=1e9;
        p1(n);
        FOR(i,1,n)pf("%d ",rd%1+1);
    }
}
namespace jishu{
    void solve(){
        int T=5e5,v=1e6;
        p1(T);
        while(T--){
            p2(rd%v+1,rd%v+1);
        }
    }
}
namespace INSQ16C{
    void solve(){
        int T=2;
        p1(T);
        while(T--){
            int n=4;
            p1(n);
            FOR(i,1,n)pf("%d ",rd%10+1);puts("");
            int Q=5;
            p1(Q);
            while(Q--)p2(rd%n+1,rd%10+1);
        }
    }
}
namespace brick{
    void solve(){
        int n=1000,C=1000000-rd%100000;
        p2(n,C);
        FOR(i,1,n)pf("%d ",rd%1000+1);
    }
}
namespace letter{
    void solve(){
        int n=200000,Q=200000,B=rd%100000000+27;
        p3(n,Q,B);
        FOR(i,1,n)putchar(rd%26+'a');puts("");
        while(Q--){
            // if(rd%2){
                int l,r;
                do l=rd%n+1,r=rd%n+1;
                while(l>r);
                p3(0,l,r);
            // }else{
            //     pf("1 %d %c\n",rd%n+1,rd%26+'a');
            // }
        }
    }
}
namespace mine{
    void solve(){
        int n=1e6,V=1e9;
        p1(n);
        FOR(i,1,n){
            int a,b;
            do{
                a=rd%V+1;
                b=rd%V+1;
            }while(a>b);
            p2(a,b);
        }
    }
}
namespace CHEFSHOP{
    bool vis[1<<15|5];
    int sz[1<<15|5];
    void solve(){
        int T=5;
        p1(T);
        while(T--){
            clr(vis,0);
            int n=15;
            p1(n);
            FOR(i,1,n)pf("%d ",rd%1000000+1);puts("");
            int m=rd%((1<<n)-1-n*(n+1)/2);
            FOR(i,1,(1<<n)-1)sz[i]=sz[i&i-1]+1;
            p1(m);
            while(m--){
                int x;
                do x=rd%(1<<n);
                while(vis[x]||sz[x]<=2);
                vis[x]=1;
                pf("%d",sz[x]);
                FOR(i,0,n-1)if(x>>i&1)pf(" %d",i+1);puts("");
            }
        }
    }
}
namespace treap{
    void solve(){
        int n=1e6-rd%1000000,p=rd%998244353;
        p2(n,p);
        int r=rd%n+1;
        FOR(i,1,n)if(i!=r)p2(r,i);
        // FOR(i,2,n)p2(1,i);
    }
}
namespace test{
    const int maxn=5e5+5;
    int A[maxn];
    void solve(){
        int n=0,m=10,Q=500000;
        p3(n,m,Q);
        FOR(i,1,n)pf("%d ",rd%1000+1);puts("");
        FOR(i,1,m)pf("%d ",rd%100000+1);puts("");
        FOR(i,1,Q-1)A[i]=rd%101;
        sort(A+1,A+Q);
        FOR(i,1,Q-1)pf("%d ",A[i]);puts("");
        FOR(i,1,Q)p3(rd%100000+1,rd%m+1,rd%100000+1);
    }
}
namespace ball{
    void solve(){
        int T=1e5,V=1e7;
        p1(T);
        while(T--){
            int n,m;
            do n=rd%V+1,m=rd%V+1;
            while(n<m);
            p2(n,m);
        }
    }
}
namespace FAVGAME{
    bool eg[1000][1000];
    void solve(){
        int T=1;
        p1(T);
        while(T--){
            int n=100,m=3;
            p2(n,m);
            FOR(i,1,m){
                int x,y;
                do x=rd%n+1,y=rd%n+1;
                while(x==y||eg[x][y]);
                eg[x][y]=eg[y][x]=1;
                p2(x,y);
            }
            puts("");
        }
    }
}
namespace Let_Them_Slide{
    void solve(){
        int n=20,m=30;
        p2(n,m);
        int sum=150;
        FOR(i,1,n){
            int s=rd%min(sum+i-n,m)+1;
            sum-=s;
            pf("%d",s);
            FOR(j,1,s)pf(" %d",rd%10001-5000);
            puts("");
        }
    }
}
namespace cactus{
    void solve(){
        int n=500,W=rd%1000+32,K=rd%10000+10000;
        // int n=10000,W=5000,K=1000000;
        p3(n,W,K);
        // FOR(i,1,n)p2(rd%6+1,rd%1000+1);
        FOR(i,1,n)p2(rd%(W>>5)+1,rd%1000+1);
    }
}
namespace Graph{
    void Print(int x,int y){
        ll v=0;
        FOR(i,0,62)v=v<<1|rd%2;
        pf("%d %d %lld\n",x,y,v);
    }
    void solve(){
        int n=100000,m=500000;
        p2(n,m);
        FOR(i,1,n-1)Print(i,i+1);
        FOR(i,1,m-n+1)Print(rd%n+1,rd%n+1);
    }
}
namespace tree_20190914{
    void solve(){
        int n=300000,m=100;
        p2(n,m);
        FOR(i,1,n)pf("%d ",rd%1000000+1);puts("");
        FOR(i,2,n)p3(rd%(i-1)+1,i,rd%1000000+1);
        p1(m);
        while(m--)p2(rd%n+1,rd%1000000+1);
    }
}
namespace walk_20190916{
    const int maxn=2e5+5;
    int A[maxn];
    void solve(){
        // freopen("walk.in","w",stdout);
        int n=5,m=5,V=(1<<3)-2;
        p2(n,m);
        // FOR(i,1,n>>1)A[i]=1;
        // FOR(i,(n>>1)+1,n)A[i]=2;
        // FOR(i,1,V+1)A[i]=i;
        // FOR(i,V+2,n)A[i]=rd%V+1;
        // A[1]=V+1;
        // FOR(i,2,n)A[i]=rd%V+1;
        FOR(i,1,n)A[i]=rd%V+1;
        // FOR(i,V+1,n)A[i]=rd%V+1;
        rf(A+1,A+n+1);
        FOR(i,1,n)pf("%d ",A[i]);puts("");
        FOR(i,1,m)p2(rd%n+1,rd%n+1);
    }
}
namespace master_20190916{
    void solve(){
        // freopen("master.in","w",stdout);
        int n=300,m=rd%(n+1);
        p2(n,m);
        FOR(i,1,n)putchar(rd%26+'a');puts("");
        FOR(i,1,n)putchar(rd%26+'a');puts("");
    }
}
namespace tour_20190916{
    const int maxn=1505;
    bool eg[maxn][maxn];
    void solve(){
        // freopen("tour.in","w",stdout);
        int n=50;
        p1(n);
        FOR(i,1,n)FOR(j,i+1,n)eg[i][j]=eg[j][i]=rd%10;
        FOR(i,1,n){
            FOR(j,1,n)pf("%d",eg[i][j]);
            puts("");
        }
    }
}
namespace pair_20190917{
    void Print(int n){
        pf("%d",rd%9+1);
        FOR(i,1,n-1)pf("%d",rd%10);
    }
    void solve(){
        int T=5;
        p2(T,0);
        while(T--){
            Print(499999);
            putchar(' ');
            Print(500000);
            puts("");
            // pf("1 %d",rd%9+1);
            // int n=499999;
            // FOR(i,1,n)pf("%d",rd%10);
            // puts("");
            // int l,r;
            // do l=rd%1000000+1,r=rd%1000000+1;
            // while(l>r);
            // p2(l,r);
            // p2(1,rd%1000000);
        }
    }
}
namespace star_20190917{
    void solve(){
        int n=5,m=2,q=1;
        p3(n,m,q);
        FOR(i,1,n)pf("%d ",1);puts("");
        FOR(i,2,n)p2(i-1,i);
        puts("");
        FOR(i,1,m)p2(rd%n+1,rd%n+1);
        puts("");
        FOR(i,1,q){
            int l,r;
            // FOR(j,1,10)l=rd%m+1;
            // r=min(m,l+rd%50);
            do{
                l=rd%m+1;
                r=rd%m+1;
            }while(l>r);
            p2(l,r);
        }
    }
}
namespace rhombus_20190917{
    void solve(){
        freopen("rhombus.in","w",stdout);
        int n=3000-rd%100,m=3000-rd%100,H=rd%min((n+1)/2,(m+1)/2)+1;
        // p4(n,m,H,0);
        // FOR(i,1,n){
        //     FOR(j,1,m)pf("%d ",rd%2000001-1000000);
        //     puts("");
        // }
        p4(n,m,H,1);
        p5(rd%1000000+1,rd%1000+1,rd%1000+1,rd%1000+1,rd%1000000+1);
    }
}
namespace fake_20190919{
    void solve(){
        int T=2;
        p1(T);
        while(T--){
            int n=10000,m=5000,K=rd%1000+1;
            p3(n,m,K);
            FOR(i,1,n)pf("%d ",rd%1000);puts("");
        }
    }
}
namespace horse_20190919{
    void solve(){
        // freopen("horse.in","w",stdout);
        int n=4;
        p1(n);
        FOR(i,1,n)pf("%d ",rd%10+1);puts("");
        FOR(i,2,n)p3(rd%(i-1)+1,i,rd%10+1);
    }
}
namespace treasure_20190919{
    void solve(){
        int n=1e5;
        p1(n);
        FOR(i,1,n)pf("%d ",rd%5?rd%n+1:-1);
    }
}
namespace mayoi_20190920{
    void solve(){
        int n=5,m=3;
        p2(n,m);
        FOR(i,1,n)pf("%d ",rd%2);puts("");
        FOR(i,0,(1<<m)-1)p2(rd%2,rd%10+1);
    }
}
namespace hitagi_20190920{
    void solve(){
        freopen("hitagi.in","w",stdout);
        int V=5e8;
        int n=1e5,m=2e8;
        p2(n,m);
        pf("0 ");
        FOR(i,2,n)pf("%d ",(int)5e3);
    }
}
namespace nadeko_20190920{
    void solve(){
        int n=15;
        p1(n);
        FOR(i,1,n)p3(rd%100000+1,rd%10+1,rd%10+1);
    }
}
namespace tree_20190921{
    void solve(){
        int n=1,m=2,Q=100;
        p3(n,m,Q);
        FOR(i,1,n)pf("%d ",rd%2?998244353:rd%100+1);puts("");
        FOR(i,2,n)p2(rd%(i-1)+1,i);
        FOR(i,n,m)p2(rd%n+1,rd%n+1);
        FOR(i,1,Q){
                p3(1,rd%n+1,rd%2?998244353:rd%100+1);
        }
    }
}
namespace string_20190923{
    void solve(){
        int a,b,c,d;
        do{
            a=rd%7;
            b=rd%7;
            c=rd%3;
            d=rd%3;
        }while(a<c||b<d||a+b==0||c+d==0);
        p4(a,b,c,d);
    }
}
namespace tour_20190923{
    void solve(){
        int n=5e5,m=n-1;
        p2(n,m);
        FOR(i,2,n)p2(rd%(i-1)+1,i);
    }
}
namespace city_20190924{
    void solve(){
        int n=4;
        p1(n);
        FOR(i,2,n)p3(rd%(i-1)+1,i,rd%5+1);
    }
}
namespace factory_20190924{
    void solve(){
        int n=5,m=rd%n+1;
        p2(n,m);
        FOR(i,1,n){
            int s,e;
            do{
                s=rd%10;
                e=100-rd%10;
            }while(s>e);
            p2(s,e);
        }
    }
}
namespace voltage_20190925{
    void solve(){
        
    }
}
namespace war_20190925{
    void solve(){
        int n=10,m=1<<n-1;
        p2(n,m);
        FOR(i,1,1<<n-1){
            FOR(j,2,n)pf("%d ",rd%1000+1);
            puts("");
        }
        puts("");
        FOR(i,1,1<<n-1){
            FOR(j,2,n)pf("%d ",rd%1000+1);
            puts("");
        }
        puts("");
    }
}
namespace highway_20190927{
    void solve(){
        int n=2e5;
        p1(n);
        FOR(i,2,n)p3(rd%(i-1)+1,i,rd%20001-10000);
    }
}
namespace computer_20190927{
    void solve(){
        ll n=1e18-rd;
        pf("%lld",n);
    }
}
namespace advence_20190927{
    void solve(){
        int T=10;
        p1(T);
        while(T--){
            int n=4e5;
            FOR(i,1,n){
                int x=rd%10000;
                if(x<6000)putchar('.');
                else if(x<8000)putchar('#');
                else putchar('*');
            }
            puts("");
        }
    }
}
namespace fake_20190927{
    const int maxn=3e5+5;
    int fa[maxn];
    struct Edge{
        int e,to;
    }edge[maxn<<1];
    int head[maxn],tot;
    void Add(int x,int y){
        edge[++tot]=(Edge){y,head[x]};
        head[x]=tot;
    }
    int stk[maxn],top;
    struct node{
        int x,y;
    }par[maxn*10];
    void dfs(int u,int f){
        stk[++top]=u;
        FOR(i,1,10)par[++tot]=(node){stk[rd%top+1],u};
        EOR(u,v)if(v!=f)dfs(v,u);
        top--;
    }
    void solve(){
        int n=3e5,m=3e5;
        p2(n,m);
        FOR(i,1,n)pf("%d ",rd%300000+1);
        FOR(i,2,n){
            p2(fa[i]=rd%(i-1)+1,i);
            Add(fa[i],i);
        }
        puts("");
        tot=0;
        dfs(1,0);
        rf(par+1,par+tot+1);
        FOR(i,1,m)p2(par[i].x,par[i].y);
        // int n=1e4,m=1e4;
        // p2(n,m);
        // FOR(i,1,n)pf("%d ",rd%300000+1);puts("");
        // FOR(i,2,n)p2(i-1,i);
        // FOR(i,1,m)p2(rd%n+1,rd%n+1);
    }
}
namespace convolution_20190927{
    void solve(){
        int n=14,m=14;
        p2(n,m);
        FOR(i,0,(1<<n)-1)pf("%d ",rd%m);puts("");
        FOR(i,0,(1<<n)-1)pf("%d ",rd%m);puts("");
        FOR(i,0,m-1){
            FOR(j,0,m-1)pf("%d ",rd%m);
            puts("");
        }
    }
}
namespace tree_20190928{
    void solve(){
        int n=8;
        p1(n);
        FOR(i,2,n)p2(rd%(i-1)+1,i);
    }
}
namespace buildroad_20190930{
    const int maxn=15;
    bool eg[maxn][maxn];
    void solve(){
        int n=13,m=n*(n-1)/2,S=0;
        FOR(i,1,n)eg[i][i]=1;
        p3(n,m,S);
        while(m--){
            int x,y;
            do{
                x=rd%n+1;
                y=rd%n+1;
            }while(eg[x][y]);
            eg[x][y]=eg[y][x]=1;
            p3(x,y,1);
        }
    }
}
namespace magic_20190930{
    void solve(){
        int T=30;
        p1(T);
        while(T--){
            int V=1e9;
            int n=100,v=rd%100+2;
            p2(n,v);
            FOR(i,1,n)pf("%d ",rd%100000+1);
            puts("");
        }
    }
}
namespace trample_20190930{
    struct node{
        int l,r;
        bool operator <(const node &A)const
        {
            return l==A.l?r<A.r:l<A.l;
        }
    };
    multiset<node>s;
    multiset<node>::iterator it;
    void solve(){
        int n=40,x=0,V=1e9+1;
        p2(n,x);
        int l,r;
        int m=0;
        FOR(i,1,n){
            switch(rd%4){
                case 0:
                    do{
                        l=rd%V;
                        r=rd%V;
                    }while(l>r);
                    p3(1,l,r);
                    s.insert((node){l,r});
                    m++;
                    break;
                case 1:
                    if(!m){
                        i--;
                        continue;
                    }
                    it=s.begin();
                    for(int x=rd%m;x;x--)++it;
                    p3(2,(*it).l,(*it).r);
                    s.erase(it);
                    m--;
                    break;
                case 2:
                    p2(3,rd%V);
                    break;
                case 3:
                    p2(3,rd%V);
                    break;
            }
        }
    }
}
namespace rain_20191003{
    void solve(){
        int n=1000,m=1000;
        p2(n,m);
        FOR(i,1,n){
            FOR(j,1,m)pf("%2d ",rd%1000000000+1);
            puts("");
        }
    }
}
namespace bigshark_20191003{
    const int maxn=2e4+5;
    int fa[maxn];
    int getfa(int x){
        return x==fa[x]?x:fa[x]=getfa(fa[x]);
    }
    void solve(){
        int n=20000,m=rd%9+2;
        p2(n,m);
        int x,y;
        FOR(i,1,n)fa[i]=i;
        FOR(i,2,n){
            do{
                x=rd%n+1;
                y=rd%n+1;
            }while(getfa(x)==getfa(y));
            // pf("(%d,%d):",getfa(x),getfa(y));
            p2(x,y);
            fa[getfa(x)]=getfa(y);
        }
    }
}
namespace starcraft_20191003{
    void solve(){
        int n=0,m=20,T=1000000000,W=1;
        p4(n,m,T,W);
    }
}
namespace ran_20191004{
    void solve(){
        int n=5,Q=1;
        p3(n,Q,0);
        while(Q--){
            p2(rd%n,rd%n);
        }
    }
}
namespace sakura_20191005{
    const int maxn=3e5+5;
    struct Edge{
        int e,to;
    }edge[maxn];
    int head[maxn];
    void Add(int x,int y){
        edge[y]=(Edge){y,head[x]};
        head[x]=y;
    }
    void dfs(int u,int f){
        
    }
    void solve(){
        int n=3,m=n+1,p=1;
        p3(n,m,p);
        FOR(i,2,n)Add(rd%(i-1)+1,i);
        dfs(1,0);
    }
}
namespace buried_20191005{
    void solve(){
        int n=3,m=3;
        p2(n,m);
        FOR(i,1,n)pf("%d ",i==1?rd%(m-1)+1:rd%m);puts("");
        FOR(i,2,n)p2(rd%(i-1)+1,i);
    }
}
namespace BZOJ1068_20191007{
    void solve(){
        int n=10;
        FOR(i,1,n)putchar(rd%2+'a');
    }
}
namespace _20191007{
    void solve(){
        int T=1;
    }
}
namespace speed_20191007{
    void solve(){
        // freopen("speed.in","w",stdout);
        int n=5,Q=n;
        p2(n,Q);
        FOR(i,2,n){
            int l,r;
            do{
                l=rd%n+1;
                r=rd%n+1;
            }while(l>r);
            p4(rd%(i-1)+1,i,l,r);
        }
        FOR(i,1,Q)pf("%d\n",i);
    }
}
namespace market_20191007{
    void solve(){
        freopen("market.in","w",stdout);
        int n=300,Q=100000,V=1e9;
        p2(n,Q);
        FOR(i,1,n)p3(rd%10000+1,300-rd%10,rd%300+1);
        FOR(i,1,Q)pf("%d %d\n",rd%V+1,rd%300+1);
    }
}
namespace div_20191007{
    void solve(){
        freopen("div.in","w",stdout);
        int n=10000,m=200,V=1e9;
        p2(n,m);
        pf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",223092870
                                                            ,281291010
                                                            ,300690390
                                                            ,358888530
                                                            ,397687290
                                                            ,417086670
                                                            ,455885430
                                                            ,514083570
                                                            ,572281710
                                                            ,591681090
                                                            ,649879230
                                                            ,688677990
                                                            ,708077370
                                                            ,766275510
                                                            ,805074270
                                                            ,863272410);
        FOR(i,1,m-15)pf("%d ",rd%V+1);
    }
}
namespace zhuzhu_201901008{
    const int maxn=2e5+5;
    int eg[1005][1005];
    int E[maxn][3];
    int fa[maxn];
    int getfa(int x){
        return x==fa[x]?x:fa[x]=getfa(fa[x]);
    }
    void solve(){
        int T=3;
        p1(T);
        while(T--){
            int n=13,m=14;
            ll X=0;
            p2(n,m);
            FOR(i,1,n){
                eg[i][i]=1;
                fa[i]=i;
            }
            FOR(i,2,n){
                int x=rd%(i-1)+1;
                eg[x][i]=eg[i][x]=1;
                E[i-1][0]=x;
                E[i-1][1]=i;
                E[i-1][2]=rd%10+1;
            }
            FOR(i,n,m){
                int x,y;
                do{
                    x=rd%n+1;
                    y=rd%n+1;
                }while(eg[x][y]||eg[y][x]);
                eg[x][y]=eg[y][x]=1;
                E[i][0]=x,E[i][1]=y;
                E[i][2]=rd%10+1;
            }
            FOR(i,2,n){
                int x;
                do x=rd%m+1;
                while(getfa(E[x][0])==getfa(E[x][1]));
                fa[getfa(E[x][0])]=getfa(E[x][1]);
                X+=E[x][2];
            }
            pf("%lld\n",X);
            FOR(i,1,m)p3(E[i][0],E[i][1],E[i][2]);
            puts("");
        }
    }
}
namespace panwang_20191008{
    void solve(){
        int a=5,b=5,c=5;
        p3(a,b,c);
        FOR(i,1,a+b+c)p2(rd%201-100,rd%2+1);
    }
}
bool mem2;
int main()
{
    // cerr<<(&mem2-&mem1)/1024.0/1024<<endl;
    srand((unsigned)time(NULL));

    // tree::solve();
    // XOR::solve();
    // piano::solve();
    // Toy_Blocks::solve();
    // nue::solve();
    // hina::solve();
    // kanako::solve();
    // magic::solve();
    // gift::solve();
    // dream::solve();
    // Prime_Query::solve();
    // delivery::solve();
    // path::solve();
    // collect::solve();
    // shrew::solve();
    // Stack::solve();
    // maze::solve();
    // C::solve();
    // manager::solve();
    // Bridge_crossing::solve();
    // Chef_and_the_Number_Sequence::solve();
    // Tree::solve();
    // bet::solve();
    // tree20190908::solve();
    // jishu::solve();
    // INSQ16C::solve();
    // brick::solve();
    // letter::solve();
    // mine::solve();
    // CHEFSHOP::solve();
    // treap::solve();
    // test::solve();
    // ball::solve();
    // FAVGAME::solve();
    // Let_Them_Slide::solve();
    // cactus::solve();
    // Graph::solve();
    // tree_20190914::solve();
    // tour_20190916::solve();
    // walk_20190916::solve();
    // master_20190916::solve();
    // tour_20190916::solve();
    // pair_20190917::solve();
    // star_20190917::solve();
    // rhombus_20190917::solve();
    // fake_20190919::solve();
    // horse_20190919::solve();
    // treasure_20190919::solve();
    // mayoi_20190920::solve();
    // hitagi_20190920::solve();
    // nadeko_20190920::solve();
    // tree_20190921::solve();
    // string_20190923::solve();
    // tour_20190923::solve();
    // city_20190924::solve();
    // factory_20190924::solve();
    // voltage_20190925::solve();
    // war_20190925::solve();
    // highway_20190927::solve();
    // computer_20190927::solve();
    // advence_20190927::solve();
    // fake_20190927::solve();
    // convolution_20190927::solve();
    // tree_20190928::solve();
    // buildroad_20190930::solve();
    // magic_20190930::solve();
    // trample_20190930::solve();
    // rain_20191003::solve();
    // bigshark_20191003::solve();
    // starcraft_20191003::solve();
    // ran_20191004::solve();
    // sakura_20191005::solve();
    // buried_20191005::solve();
    // BZOJ1068_20191007::solve();
    // _20191007::solve();
    // speed_20191007::solve();
    // market_20191007::solve();
    // div_20191007::solve();
    zhuzhu_201901008::solve();
    // panwang_20191008::solve();
}

