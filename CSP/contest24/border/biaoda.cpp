#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
const int mod=1e9+7;
const LL MAX=2e9;
int n,q;
int A[M];
struct QAQ{int l,id;};
vector<QAQ>vec[M];
int ans[M];
LL Pw[M],sum[M];
LL val[M],qs[M];
int pre[M];
int fa[M];
int getfa(int x){
    return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void merge(int x,int y){
    int len=x-pre[x];
    if(len>30&&val[y])val[y]=MAX;
    else val[y]=min(MAX,val[x]+(val[y]<<len));
    fa[x]=y;pre[y]=pre[x];
}
LL S(int l,int r){
    LL res=(sum[l]-sum[r+1]*Pw[r-l+1])%mod;
    if(res<0)res+=mod;
    return res;
}
void solve(){
    Pw[0]=1;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        Pw[i]=Pw[i-1]*2%mod;
    }
    for(int i=n;i;i--)sum[i]=(sum[i+1]*2+A[i])%mod;
    for(int i=1;i<=n;i++){
        pre[i]=i-1;val[i]=A[i];
        while(pre[i]&&val[i]>=0)merge(pre[i],i);
        qs[i]=(qs[pre[i]]+S(pre[i]+1,i)*2)%mod;
        for(int j=0,sz=vec[i].size();j<sz;j++){
            int l=vec[i][j].l;
            ans[vec[i][j].id]=((qs[i]-qs[getfa(l)]+S(l,getfa(l)))%mod+mod)%mod;
        }
    }
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}   
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    for(int i=1,l,r;i<=q;i++){
        scanf("%d%d",&l,&r);
        vec[r].push_back((QAQ){l,i});
    }
    solve();
    return 0;
}
