#include<cstdio>
#include<algorithm>
#define MN 300001
#define ll long long
using namespace std;
char ibuf[20000004],*iptr=ibuf-1,C;
inline int _(){
    int x=0,c=*++iptr;
    while(c<48)c=*++iptr;
    while(c>47)x=x*10+c-48,c=*++iptr;
    return x;
}
char obuf[5000000],*optr=obuf;
inline void _(ll x){
    static int stk[32],stp=0;
    if (x<0) *(optr++)='-',x=-x;
    if(!x)stk[stp++]=0;
    while(x)stk[stp++]=x%10,x/=10;
    while(stp)*(optr++)=stk[--stp]+48;
    *(optr++)=10;
}
struct tree{int l,r,s[2],S;ll al;}t[MN*40];
int n,m,a[MN],num=0,l,r,k,s[2],S[MN][2],ro[MN],mi,ma;
ll mmh,c;
inline ll min(ll a,ll b){return a<b?a:b;}
inline ll max(ll a,ll b){return a>b?a:b;}
void in(int &P,int x,int v){
    int l=mi,r=ma,mid,*p;p=&P;
    for (;;){
        *p=++num;t[*p]=t[x];t[*p].s[v&1]++;t[*p].S++;t[*p].al+=v;
        if (l==r) break;
        int mid=l+r>>1;
        if (v<=mid) p=&t[*p].l,x=t[x].l,r=mid;else p=&t[*p].r,x=t[x].r,l=mid+1;
    }
}
void ask(int p,int x,int l,int r,int k){
    while (l<r){
        if (k>=t[t[p].r].S-t[t[x].r].S) s[0]+=t[t[p].r].s[0]-t[t[x].r].s[0],s[1]+=t[t[p].r].s[1]-t[t[x].r].s[1],
        mmh+=t[t[p].r].al-t[t[x].r].al,k-=t[t[p].r].S-t[t[x].r].S,p=t[p].l,x=t[x].l,r=l+r>>1;else p=t[p].r,x=t[x].r,l=(l+r>>1)+1;
        if (k==0) return;
    }
    if (k) mmh+=1LL*k*l,s[l&1]+=k;
}
ll askmax(int p,int x,int k,bool bo){
    if (t[p].s[bo]-t[x].s[bo]<=k) return -1e18;
    int l=mi,r=ma;
    while (l<r)
    if (t[t[p].r].s[bo]-t[t[x].r].s[bo]>k) p=t[p].r,x=t[x].r,l=(l+r>>1)+1;else k-=t[t[p].r].s[bo]-t[t[x].r].s[bo],p=t[p].l,x=t[x].l,r=l+r>>1;
    return l;
}
ll askmin(int p,int x,int k,bool bo){
    if (t[p].s[bo]-t[x].s[bo]<k) return 1e18;
    int l=mi,r=ma;
    while (l<r)
    if (t[t[p].r].s[bo]-t[t[x].r].s[bo]>=k) p=t[p].r,x=t[x].r,l=(l+r>>1)+1;else k-=t[t[p].r].s[bo]-t[t[x].r].s[bo],p=t[p].l,x=t[x].l,r=l+r>>1;
    return l;
}
int main(){
    ibuf[fread(ibuf,1,20000000,stdin)]=0;
    register int i;
    n=_();t[0].l=t[0].r=t[0].s[0]=t[0].s[1]=t[0].al=t[0].S=0;
    for (i=1;i<=n;i++) a[i]=_(),S[i][0]=S[i-1][0],S[i][1]=S[i-1][1],S[i][a[i]&1]++,mi=min(mi,a[i]),ma=max(ma,a[i]);
    for (i=1;i<=n;i++) in(ro[i],ro[i-1],a[i]);
    m=_();
    while (m--){
        l=_();r=_();k=_();
        if ((S[r][0]-S[l-1][0]>>1)+(S[r][1]-S[l-1][1]>>1)<(k>>1)){_(-1);continue;}
        mmh=s[0]=s[1]=0;ask(ro[r],ro[l-1],mi,ma,k);
        if (s[0]&1) mmh-=min(askmin(ro[r],ro[l-1],s[1],1)-askmax(ro[r],ro[l-1],s[0],0),askmin(ro[r],ro[l-1],s[0],0)-askmax(ro[r],ro[l-1],s[1],1));
        _(mmh);
    }
    fwrite(obuf,1,optr-obuf,stdout);
    return 0;
}