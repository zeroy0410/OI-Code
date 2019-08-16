#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<stdio.h>
using namespace std;
#define LL long long
LL mod=1000000000;
const int N=100005;
int n,m,T;
int x[N],y[N],w[N],f[N<<1],bj[N<<1],d[N<<1];
LL ans;
int find(int x){
    if(f[x]==x)return x;
    int t=f[x];
    f[x]=find(f[x]),d[x]=(d[x]+d[t])%2;
    return f[x];
}
LL work(){
    int i,r1,r2,t;LL re=1;
    for(i=1;i<=n+m;++i)f[i]=i,d[i]=0,bj[i]=-1;
    f[n+1]=1,bj[1]=0;
    for(i=1;i<=T;++i){
        if(x[i]==1&&y[i]==1)continue;
        if(x[i]==1||y[i]==1){
            if(y[i]==1)r1=find(x[i]),t=x[i];
            else r1=find(y[i]+n),t=y[i]+n;
            if(bj[r1]==-1)bj[r1]=w[i]^d[t];
            else if(bj[r1]!=w[i]^d[t])return 0;
            continue;
        }
        r1=find(x[i]),r2=find(y[i]+n);
        if(r1!=r2){
            f[r1]=r2,d[r1]=(d[y[i]+n]-d[x[i]]+w[i]+4)%2;
            if(bj[r1]!=-1&&bj[r2]!=-1&&bj[r2]!=bj[r1]^d[r1])return 0;
            if(bj[r2]==-1&&bj[r1]!=-1)bj[r2]=bj[r1]^d[r1],bj[r1]=-1;
        }
        else if(d[x[i]]^d[y[i]+n]^w[i]==1)return 0;
    }
    for(i=1;i<=n+m;++i)if(find(i)==i&&bj[i]==-1){
        re=(re<<1)%mod;
        cout<<i<<endl;
    }
    return re;
}
int main(){
    int i,j,flag=-1;
    scanf("%d%d%d",&n,&m,&T);
    for(i=1;i<=T;++i){
        scanf("%d%d%d",&x[i],&y[i],&w[i]);
        if(x[i]==1&&y[i]==1)flag=w[i];
        if(!(x[i]&1)&&!(y[i]&1))w[i]^=1;
    }
    if(flag==-1||flag==0)ans+=work();
    if(flag==-1||flag==1){
        for(i=1;i<=T;++i)
            if(x[i]!=1&&y[i]!=1)w[i]^=1;
        ans+=work();
    }
    ans%=mod;
    printf("%lld\n",ans);
    return 0;
}