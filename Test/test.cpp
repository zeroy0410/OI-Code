#include<bits/stdc++.h>
#define M 200005
using namespace std;
int T,n,K,d,A[M],B[M];
struct BIT{
	int C[M];
	void add(int x,int d){
		x++;
		while(x<=n+1){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	int sum(int x){
		x++;int res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
int mx[M];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&K,&d);
		for(int i=1;i<=n;i++)scanf("%d",&A[i]),B[i]=A[i],mx[i]=-1;
		for(int i=1;i<=n+1;i++)Tr.C[i]=0;
		sort(B+1,B+n+1);
		int bc=unique(B+1,B+n+1)-B-1;
		for(int i=1;i<=n;i++)
			A[i]=lower_bound(B+1,B+bc+1,A[i])-B;
		int ans=1e9;
		for(int i=1;i<=n;i++){
			if(mx[A[i]]==-1){mx[A[i]]=i,Tr.add(i,1);}
			else {
				Tr.add(mx[A[i]],-1);
				mx[A[i]]=i;
				Tr.add(i,1);
			}
			if(i>=d)
				ans=min(ans,Tr.sum(i)-Tr.sum(i-d));
		}
		printf("%d\n",ans);
	}
	return 0;
}
