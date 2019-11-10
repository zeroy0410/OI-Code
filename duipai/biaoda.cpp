#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=2e5+5,P=998244353;
int n,K,m;
int a[M],b[M];
ll f[M],g[M];
ll solve(int n,int *a){
    for(int i=2;i<=n;i++){
        if(a[i]&&a[i-1]&&a[i]==a[i-1])return 0;
    }
    bool fl=0;
    for(int i=1;i<=n;i++)
        if(a[i])fl=1;
    if(!fl){
        ll res=K;
        for(int i=1;i<n;i++)res=res*(K-1)%P;
        return res;
    }
    ll ans=1;
    int st,ed;
    for(st=1;!a[st];st++)ans=ans*(K-1)%P;
    for(ed=n;!a[ed];ed--)ans=ans*(K-1)%P;
    for(int i=st;i<=ed;i++){
        if(!a[i]){
            int ct=0,j;
            for(j=i;!a[j];j++)ct++;
            if(a[i-1]==a[j])ans=ans*f[ct]%P;
            else ans=ans*g[ct]%P;
            i=j;
        }
    }
    return ans;
}
int main(){
    scanf("%d%d%d",&n,&K,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    f[1]=K-1,g[1]=K-2;
    for(int i=2;i<=n;i++){
        f[i]=g[i-1]*(K-1)%P;
        g[i]=(f[i-1]+g[i-1]*(K-2))%P;
    }
    if(m==0)printf("%lld\n",solve(n,a));
    else {
        int ct=0;
        for(int i=1;i<=n;i+=2)b[++ct]=a[i];
        ll ans=solve(ct,b);
        ct=0;
        for(int i=2;i<=n;i+=2)b[++ct]=a[i];
        printf("%lld\n",solve(ct,b)*ans%P);
    }
    return 0;
}
