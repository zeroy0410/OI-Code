#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,A[M];
int main(){
    // freopen("stone.in","r",stdin);
    // freopen("stone.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    sort(A+1,A+n+1);
    LL ans1=0,ans2=0;
    for(int i=1;i<=n/2;i++)ans1+=A[i];
    for(int i=n/2+1;i<=n;i++)ans2+=A[i];
    printf("%lld %lld\n",ans2,ans1);
    return 0;
}