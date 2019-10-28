#include<bits/stdc++.h>
#define M 50005
#define LL long long
using namespace std;
int n,K,P[M],C[M];
LL m;
priority_queue<int>Q;
struct node{
	int p,c;
}A[M];
bool cmpp(node a,node b){return a.p<b.p;}
bool cmpc(node a,node b){return a.c<b.c;}
int main(){
	scanf("%d%d%lld",&n,&K,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&A[i].p,&A[i].c);
	sort(A+1,A+n+1,cmpc);
	int ans=0;
	for(int i=1;i<=K;i++){
		if(m>=A[i].c)m-=A[i].c,ans++;
		else {
			printf("%d\n",ans);
			return 0;
		}
	}
	sort(A+K+1,A+n+1,cmpp);
	for(int i=K+1;i<=n;i++){
		if(m>=A[i].p)m-=A[i].p,ans++;
		else {
			printf("%d\n",ans);
			return 0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
