#include<bits/stdc++.h>
#define M 200005
using namespace std;
struct node{
	int x,y,z;
	bool operator < (const node & res)const{
		if(x!=res.x)return x>res.x;
		return y<res.y;	
	}
}wk[M<<1];
int C[M];void add(int x,int d){while(x<M){C[x]=max(C[x],d);x+=(x&-x);}}
int query(int x){int res=0;while(x){res=max(res,C[x]);x-=(x&-x);}return res;}
int n,m,B[M],bn,ans[M];
int main(){
	freopen("matryoshka.in","r",stdin);
	freopen("matryoshka.out","w",stdout); 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&wk[i].x,&wk[i].y),B[i]=wk[i].y;
	for(int i=1;i<=m;i++)scanf("%d%d",&wk[i+n].x,&wk[i+n].y),wk[i+n].z=i;
	sort(B+1,B+n+1);bn=unique(B+1,B+n+1)-B-1;
	stable_sort(wk+1,wk+n+m+1);
	for(int i=1;i<=n+m;i++){
		wk[i].y=upper_bound(B+1,B+bn+1,wk[i].y)-B-1;
		if(wk[i].z)ans[wk[i].z]=query(wk[i].y);
		else add(wk[i].y,query(wk[i].y)+1); 
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
