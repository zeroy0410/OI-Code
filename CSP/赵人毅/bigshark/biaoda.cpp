#include<bits/stdc++.h>
using namespace std;
#define M 20005
#define ll long long
const int mx=1e9;
struct hh{
    ll a[505];
    int cnt;
    hh(){
        cnt=1;
        memset(a,0,sizeof(a));
    }
    hh operator*(hh x){
        hh w;
        for(int i=1;i<=cnt;++i)
            for(int j=1;j<=x.cnt;++j){
                w.a[i+j-1]+=a[i]*x.a[j];
                if(w.a[i+j-1]>=mx){
                    w.a[i+j]+=w.a[i+j-1]/mx;
                    w.a[i+j-1]%=mx;
                }
            }
        if(w.a[cnt+x.cnt])w.cnt=cnt+x.cnt;
        else w.cnt=cnt+x.cnt-1;
        return w;
    }
    hh operator+(hh x){
        hh w;w.cnt=max(cnt,x.cnt);
        for(int i=1;i<=w.cnt;++i){
            w.a[i]+=a[i]+x.a[i];
            if(w.a[i]>=mx)w.a[i+1]++,w.a[i]-=mx;
        }
        if(w.a[w.cnt+1])w.cnt++;
        return w;
    }
    bool operator<(hh x){
        if(cnt<x.cnt)return 1;
        if(cnt>x.cnt)return 0;
        for(int i=cnt;i>=1;--i)
            if(a[i]<x.a[i])return 1;
            else if(a[i]>x.a[i])return 0;
        return 0;
    }
    hh operator-(hh x){
        hh w;w.cnt=cnt;
        for(int i=1;i<=cnt;++i)w.a[i]=a[i];
        for(int i=1;i<=x.cnt;++i){
            if(w.a[i]<x.a[i])w.a[i]+=mx,w.a[i+1]--;
            w.a[i]-=x.a[i];
        }
        while(w.cnt>1&&w.a[w.cnt]==0)w.cnt--;
        return w;
    }
    void out(){
        printf("%lld",a[cnt]);
        for(int i=cnt-1;i>=1;--i)printf("%lld",a[i]);
        cout<<endl;
    }
}dp[M],ans,K,sz[M],p;
vector<int>d[M];
int n,k,id;
void dfs(int x,int f){
    sz[x].a[1]=1;
    for(int i=0;i<(int)d[x].size();++i){
        int v=d[x][i];
        if(v==f)continue;
        dfs(v,x);
        dp[x]=dp[x]+(dp[v]+sz[v])*K;
        sz[x].a[1]+=sz[v].a[1];
    }
}
void Dfs(int x,int f){
    if(f){
        p.a[1]=n-sz[x].a[1];
        dp[x]=dp[x]+(dp[f]+p-(dp[x]+sz[x])*K)*K;
        sz[x].a[1]=n;
    }
    for(int i=0;i<(int)d[x].size();++i){
        int v=d[x][i];
        if(v==f)continue;
        Dfs(v,x);
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        d[x].push_back(y);
        d[y].push_back(x);
    }K.a[1]=k;
    dfs(1,0);Dfs(1,0);ans=dp[1];id=1;
    for(int i=2;i<=n;++i)if(dp[i]<ans)ans=dp[i],id=i;
    printf("%d",id);
}
