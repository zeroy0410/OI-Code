#include<bits/stdc++.h>
#define M 50005
using namespace std;
const int inf=1e9+7;
struct node{
	int id,x;
	bool operator < (const node& res)const{
		return x>res.x;
	}
};
int n;
node A[M];
int ch[M*40][2],val[M*40],rt[M],tot;
int Insert(int x,int d){
	int tmp=++tot,y=tot;
	for(int i=30,c;i>=0;i--){
		c=(d>>i)&1;
		ch[y][!c]=ch[x][!c];
		y=ch[y][c]=++tot;
		x=ch[x][c];
		val[y]=val[x]+1;
	}
	return tmp;
}
set<int>S;
int query(int l,int r,int x){
	int ans=0;
	for(int i=30,c;i>=0;i--){
		c=(x>>i)&1;
		if(val[ch[r][!c]]-val[ch[l][!c]])
			r=ch[r][!c],l=ch[l][!c],ans=ans<<1|1;
		else r=ch[r][c],l=ch[l][c],ans=ans<<1;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i].x);A[i].id=i;
		rt[i]=Insert(rt[i-1],A[i].x);
	}
	sort(A+1,A+n+1);
	S.insert(-1);S.insert(inf);S.insert(A[1].id);
	S.insert(inf+1),S.insert(-2);
	set<int>::iterator l,r;
	int ans=0,x,y;
	for(int i=2;i<=n;i++){
		l=r=S.lower_bound(A[i].id);
		l--;l--;r++;
		x=*l+1,y=*r-1;
		x=max(1,x),y=min(y,n);
		ans=max(ans,query(rt[x-1],rt[y],A[i].x));
		S.insert(A[i].id); 
	}
	printf("%d\n",ans);
	return 0;
}
