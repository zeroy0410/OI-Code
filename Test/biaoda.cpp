#include<bits/stdc++.h>

#define FOG(x,y,z) for(register int x=y,x##_=z;x<=x##_;++x)
#define DOG(x,y,z) for(register int x=y,x##_=z;x>=x##_;--x)
#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;++x)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;--x)
#define FOR_(x,y,z,s) for(int x=y,x##_=z;x<=x##_;x+=s)
#define FOR__(x,y,z) for(int x=y,x##_=z;x<=x##_;x<<=1)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)
#define EOD(x,y) for(int &x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define While(x) for(;x;)
#define clr(x,y) memset(x,y,sizeof(x))
#define lbd(A,s,e,x) (lower_bound(A+s,A+e+1,x)-A)
#define ubd(A,s,e,x) (upper_bound(A+s,A+e+1,x)-A)
#define uni(A,x) {sort(A+1,A+x+1);x=unique(A+1,A+x+1)-A-1;}
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
#define uint unsigned int
#define db double
#define ct clock_t
#define ck() clock()
#define rd rand()
#define rmx RAND_MAX
#define RD T*(rd*2-rmx)


using namespace std;

template<class T>bool tomin(T &x,T y){return y<x?x=y,1:0;}
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
bool mem1;
const db Pi=acos(-1);
const int maxn=1e5+5;
int n,m;
int A[maxn],B[maxn];
int cnt[maxn],rcnt[maxn];
bool mem2;
int main(){
    // cerr<<(&mem2-&mem1)/1024.0/1024<<endl;
    srand(time(NULL));
    read(n);
    FOR(i,1,n)read(A[i]),B[++m]=A[i];
    uni(B,m);
    FOR(i,1,n)cnt[A[i]=lbd(B,1,m,A[i])]++;
    sort(cnt+1,cnt+m+1);
    if(cnt[m]==1)return pf("%d",n),0;
    FOR(i,1,m)rcnt[cnt[i]]++;
    int ans=0;
    if(rcnt[3])ans=rcnt[3]+rcnt[2]+rcnt[1]/2-1;
    else ans=rcnt[2]+rcnt[1]-1;
    pf("%d",ans);
    return 0;
}

