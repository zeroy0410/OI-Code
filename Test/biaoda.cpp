#include <bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
LL dp[M];
int n,A[M],cnt[M],s[M];
vector<int>q[M];
LL cal(int x,int y){return dp[x-1]+1LL*A[x]*y*y;}
int sol(int x,int y){
    int l=1,r=n,ret=n+1;
    while(l<=r){
        int mid=l+r>>1;
        if(cal(x,mid-s[x]+1)>=cal(y,mid-s[y]+1)){
            ret=mid;
            r=mid-1;
        }
        else l=mid+1; 
    }
    return ret;
}
int main(){
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);A[i]=x;s[i]=++cnt[x];
        while(q[x].size()>=2&&sol(q[x][q[x].size()-2],q[x][q[x].size()-1])<=sol(q[x][q[x].size()-1],i))q[x].pop_back();
        q[x].push_back(i);
        while(q[x].size()>=2&&sol(q[x][q[x].size()-2],q[x][q[x].size()-1])<=s[i])q[x].pop_back();
        dp[i]=cal(q[x][q[x].size()-1],s[i]-s[q[x][q[x].size()-1]]+1);
    }
    printf("%lld\n",dp[n]);
    return 0;
}
