#include<bits/stdc++.h>
#define FOR(i,x,y) for(int i=(x),i##END=(y);i<=i##END;++i)
#define DOR(i,x,y) for(int i=(x),i##END=(y);i>=i##END;--i)
template<typename T,typename _T>inline bool chk_min(T &x,const _T y){return y<x?x=y,1:0;}
template<typename T,typename _T>inline bool chk_max(T &x,const _T y){return x<y?x=y,1:0;}
typedef long long ll;
struct node
{
    int t,g,m;
    bool operator <(const node &_)const{return t<_.t;}
};
node A[18],B[18];
int n;ll ans;
ll calc(ll a,ll b,ll c){
    ll delta=b*b-4*a*c;
    if(delta<0)return -1;
    ll x=floor((-b+sqrt(delta))/(2*a));
    if(x<0||a*x*x+b*x+c>0)return -1;
    return x;
}
void solve(int K){
    int tot=0;
    FOR(i,0,n-1)if(K>>i&1)B[++tot]=A[i];
    int p=1;ll s=0;
    B[0].t=0;
    FOR(i,1,tot){
        int x=B[i].t-B[i-1].t;ll C=0;
        FOR(j,i,tot){
            int T=B[j].t-B[i-1].t;
            C+=B[j].g;
            int res=calc(1,p-T,C-s-1ll*T*p);
            if(res==-1)return;
            chk_min(x,res);
        }
        p+=x;
        s+=1ll*((B[i].t-B[i-1].t)-x)*p-B[i].g;
    }
    ll sum=0;
    FOR(i,1,tot)sum+=B[i].m;
    chk_max(ans,sum);
}
int main(){
    scanf("%d",&n);
    FOR(i,0,n-1)scanf("%d%d%d",&A[i].t,&A[i].g,&A[i].m);
    std::sort(A,A+n);
    FOR(i,1,(1<<n)-1)solve(i);
    printf("%lld\n",ans);
    return 0;
}
