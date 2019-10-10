#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m,A[M];
int ans=0;
struct BIT{
	int C[M<<1];
	void Add(int x,int d){
		x++;
		while(x<(M<<1)){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	int sum(int x){
		int res=0; x++;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
	void update(int l,int r,int d){
		Add(l,d);Add(r+1,-d);
	}
}Tr;
char op[15];
int main(){
	freopen("patrick.in","r",stdin);
	freopen("patrick.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	A[n+1]=0;
	for(int i=1;i<=n;i++)
		if(A[i]>A[i+1])Tr.update(A[i+1]+1,A[i],1);
	for(int i=1,x,y;i<=m;i++){
		scanf("%s",op+1);
		if(op[1]=='C'){
			scanf("%d%d",&x,&y);
			x^=ans;y^=ans;
			if(A[x]>A[x+1])Tr.update(A[x+1]+1,A[x],-1);
			if(x>1&&A[x-1]>A[x])Tr.update(A[x]+1,A[x-1],-1);
			A[x]=y;
			if(A[x]>A[x+1])Tr.update(A[x+1]+1,A[x],1);
			if(x>1&&A[x-1]>A[x])Tr.update(A[x]+1,A[x-1],1);
		}
		else {
			scanf("%d",&x);
			x^=ans;ans=Tr.sum(x);
			printf("%d\n",ans);
		}
	}
	return 0;
}
