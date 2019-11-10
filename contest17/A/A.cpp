#include<bits/stdc++.h>
#define M 100005
#define LL long double
using namespace std;
const LL inf=1e18;
int n,L,P,T,A[M];
char S[35];
LL sum[M],dp[M];
LL calc(int i,int j){
	int y=abs(sum[i]-sum[j]+i-j-1-L);
	LL res=1;
	for(int i=1;i<=P;i++)res*=y;
	return dp[j]+res;
}
struct node{int l,r,s;}Q[M];
int main(){
	freopen("poet.in","r",stdin);
	freopen("poet.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&L,&P);
		for(int i=1;i<=n;i++){
			scanf("%s",S);
			sum[i]=sum[i-1]+strlen(S);
		}
		int l=1,r=0;
		Q[++r]=(node){1,n,0};
		for(int i=1;i<=n;i++){
			dp[i]=calc(i,Q[l].s);
			if(Q[l].l==Q[l].r)l++;
			else Q[l].l++;
			while(l<=r&&calc(Q[r].l,Q[r].s)>calc(Q[r].l,i))r--;
			if(l>r)Q[++r]=(node){i+1,n,i};
			else {
				int L=Q[r].l+1,R=Q[r].r+1;
				while(L<R){
					int mid=(L+R)>>1;
					if(calc(mid,Q[r].s)>calc(mid,i))R=mid;
					else L=mid+1;
				}
				Q[r].r=L-1;
				if(L<=n)Q[++r]=(node){L,n,i};
			}
		}
		if(dp[n]>1e18)puts("Too hard to arrange");
		else printf("%.0Lf\n",dp[n]);
		puts("--------------------");		
	}
	return 0;
}
