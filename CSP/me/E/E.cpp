#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
bool mm1;
int n,op;
LL A[M];
LL dp[M],mx[M],sum[M];
LL pf(LL a){ return a*a; }
int stk[M],top;
void solve(){
    for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i];
    dp[1]=A[1]*A[1];mx[1]=A[1];stk[++top]=0;stk[++top]=1;
    int cur=1;
    for(int i=2;i<=n;i++){
        while(cur+1<=top&&sum[i]>=sum[stk[cur+1]]+mx[stk[cur+1]])cur++;
        dp[i]=dp[stk[cur]]+pf(sum[i]-sum[stk[cur]]);
        mx[i]=sum[i]-sum[stk[cur]];
        while(top&&sum[i]+mx[i]<=sum[stk[top]]+mx[stk[top]])top--;
        stk[++top]=i;
    }
    printf("%lld\n",dp[n]);
}
bool mm2;
int main(){
	scanf("%d%d",&n,&op);

	return 0;
}