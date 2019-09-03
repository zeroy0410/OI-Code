#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>P;
const int N=100010,M=262150,inf=1000000010;
int n,m,i,x,y,ans;
P xmi[M],xma[M],ymi[M],yma[M];
void build(int x,int a,int b){
    if(a==b){
        scanf("%d%d",&xmi[x].first,&ymi[x].first);
        xmi[x].second=ymi[x].second=a;
        xma[x]=xmi[x];
        yma[x]=ymi[x];
        return;
    }
    int mid=(a+b)>>1;
    build(x<<1,a,mid),build(x<<1|1,mid+1,b);
    xmi[x]=min(xmi[x<<1],xmi[x<<1|1]);
    xma[x]=max(xma[x<<1],xma[x<<1|1]);
    ymi[x]=min(ymi[x<<1],ymi[x<<1|1]);
    yma[x]=max(yma[x<<1],yma[x<<1|1]);
}
P askxmi(int x,int a,int b,int c,int d){
    if(c>d)return P(inf,0);
    if(c<=a&&b<=d)return xmi[x];
    int mid=(a+b)>>1;
    P t(inf,0);
    if(c<=mid)t=askxmi(x<<1,a,mid,c,d);
    if(d>mid)t=min(t,askxmi(x<<1|1,mid+1,b,c,d));
    return t;
}
P askymi(int x,int a,int b,int c,int d){
    if(c>d)return P(inf,0);
    if(c<=a&&b<=d)return ymi[x];
    int mid=(a+b)>>1;
    P t(inf,0);
    if(c<=mid)t=askymi(x<<1,a,mid,c,d);
    if(d>mid)t=min(t,askymi(x<<1|1,mid+1,b,c,d));
    return t;
}
P askxma(int x,int a,int b,int c,int d){
    if(c>d)return P(-inf,0);
    if(c<=a&&b<=d)return xma[x];
    int mid=(a+b)>>1;
    P t(-inf,0);
    if(c<=mid)t=askxma(x<<1,a,mid,c,d);
    if(d>mid)t=max(t,askxma(x<<1|1,mid+1,b,c,d));
    return t;
}
P askyma(int x,int a,int b,int c,int d){
    if(c>d)return P(-inf,0);
    if(c<=a&&b<=d)return yma[x];
    int mid=(a+b)>>1;
    P t(-inf,0);
    if(c<=mid)t=askyma(x<<1,a,mid,c,d);
    if(d>mid)t=max(t,askyma(x<<1|1,mid+1,b,c,d));
    return t;
}
inline int cal(int x,int y,int z){
    return max(
    max(askxma(1,1,n,x,z-1).first,askxma(1,1,n,z+1,y).first)-min(askxmi(1,1,n,x,z-1).first,askxmi(1,1,n,z+1,y).first)
    ,
    max(askyma(1,1,n,x,z-1).first,askyma(1,1,n,z+1,y).first)-min(askymi(1,1,n,x,z-1).first,askymi(1,1,n,z+1,y).first)
    );
}
int main(){
    scanf("%d%d",&n,&m);
    build(1,1,n);
    while(m--){
        scanf("%d%d",&x,&y);
        ans=cal(x,y,askxmi(1,1,n,x,y).second);
        ans=min(ans,cal(x,y,askxma(1,1,n,x,y).second));
        ans=min(ans,cal(x,y,askymi(1,1,n,x,y).second));
        ans=min(ans,cal(x,y,askyma(1,1,n,x,y).second));
        printf("%d\n",ans);
    }
}
