#include<bits/stdc++.h>
#define M 300005
using namespace std;
int T,n,A[M];
int stk[M],top;
int L[M],R[M],mi[M],mx[M];
long long ans,dp[M];
int main(){
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        memset(L,0x3f,sizeof(L));
        memset(R,0,sizeof(R));
        memset(mi,0x3f,sizeof(mi));
        memset(mx,0,sizeof(mx));
        ans=0;
        scanf("%d",&n);top=0;
        for(int i=1;i<=n;i++)scanf("%d",&A[i]);
        for(int i=1;i<=n;i++){
            L[A[i]]=min(L[A[i]],i);
            R[A[i]]=max(R[A[i]],i);
        }
        for(int i=1;i<=n;i++){
            if(L[A[i]]==i)stk[++top]=i,mi[top]=i,mx[top]=R[A[i]];
            mi[top]=min(mi[top],L[A[i]]);
            mx[top]=max(mx[top],R[A[i]]);
            if(R[A[i]]==i){
                while(top&&mx[top]==i){
                    if(mi[top]==stk[top]){
                        dp[i]=dp[stk[top]-1]+1;
                        break;
                    }
                    else {
                        mi[top-1]=min(mi[top],mi[top-1]);
                        mx[top-1]=max(mx[top],mx[top-1]);
                        top--;
                    }
                }
            }
        }
        for(int i=1;i<=n;i++) ans+=dp[i];
        printf("%lld\n",ans);
    }
    return 0;
}