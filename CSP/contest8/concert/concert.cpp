#include<bits/stdc++.h>
#define M 100005
using namespace std;
bool mm1;
int T,n,K,A[M],S,P;
char op[16];
bool mm2;
int l,r,Q[M];
void solve1(){
	int tmp=(n-K-(K+1))/2;
	int ans=-1e9;
	l=1;r=0;
	for(int i=tmp+1,ed=tmp+K+K+1;i<=ed;i++){
		while(l<=r&&Q[l]+K<i)l++;
		while(l<=r&&A[Q[r]]>=A[i])r--;
		Q[++r]=i;
		if(tmp+1+K<=i)ans=max(ans,A[Q[l]]);
	}
	printf("%d\n",ans);
}
void solve2(){
	int s=(n-(K+1))/2+1;
	int ans=-1e9;
	for(int i=s;i<=s+K;i++)
		ans=max(ans,A[i]);
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",op);
		if(op[2]=='w'){
			scanf("%d%d",&n,&K);
			for(int i=1;i<=n;i++)
				scanf("%d",&A[i]);
		}
		else {
			scanf("%d%d%d%d",&n,&K,&S,&P);
			A[1]=S;
			for(int i=2;i<=n;i++)
				A[i]=(1LL*A[i-1]*2333+6666)%P;
		}
		if(n==1)printf("%d\n",A[1]);
		else if((n-1)/K%2)solve2();
		else solve1();
	}
	return 0;
}
