#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
typedef long double db;
int n,L,P;
char s[35];
int Len[M];
struct node{int l,r,s;}q[M];
db dp[M];
db calc(int i,int j){
	int y=abs(Len[i]-Len[j]+i-j-1-L);
	db res=1;
	for(int i=1;i<=P;i++)res*=y;
	return dp[j]+res;
}
int main(){
//	freopen("poet.in","r",stdin);
//	freopen("poet.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&L,&P);
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			Len[i]=Len[i-1]+strlen(s);
		}
		int l=1,r=0;
		q[++r]=(node){1,n,0};
		for(int i=1;i<=n;i++){
			dp[i]=calc(i,q[l].s);
			if(q[l].l==q[l].r)l++;
			else q[l].l++;
			while(l<=r&&calc(q[r].l,q[r].s)>calc(q[r].l,i))r--;
			if(l>r)q[++r]=(node){i+1,n,i};
			else {
				int L=q[r].l+1,R=q[r].r+1;
				while(L<R){
					int mid=(L+R)>>1;
					if(calc(mid,q[r].s)>calc(mid,i))R=mid;
					else L=mid+1;
				}
				q[r].r=L-1;
				if(L<=n)q[++r]=(node){L,n,i};
			}
		}
		cout<<dp[n]<<endl;
		if(dp[n]>1e18)puts("Too hard to arrange");
		else printf("%.0Lf\n",dp[n]);
		puts("--------------------");
	}
	return 0;
}
