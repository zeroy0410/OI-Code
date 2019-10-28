#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
#define maxn 50010
#define inf 0x3fffffff
using namespace std;
set<int>s;
int n,ch[maxn*35][2],rt[maxn],bin[35],tot,size[maxn*35];
struct node{
	int x,id;
	bool operator<(const node& y)const{return x>y.x;}
}a[maxn];
 
int insert(int x,int val){
	int root=++tot;int y=root;
	for(int c,i=30;i>=0;i--){
		c=(val>>i)&1;
		ch[y][!c]=ch[x][!c];
		y=ch[y][c]=++tot;
		x=ch[x][c];
		size[y]=size[x]+1;
	}
	return root;
}
int query(int l,int r,int val){
	int ans=0;
	for(int c,i=30;i>=0;i--){
		c=(val>>i)&1;
		if(size[ch[r][!c]]-size[ch[l][!c]])
			r=ch[r][!c],l=ch[l][!c],ans=ans<<1|1;
		else l=ch[l][c],r=ch[r][c],ans=ans<<1;
	}
	return ans;
}
 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].x);a[i].id=i;
		rt[i]=insert(rt[i-1],a[i].x);
	}sort(a+1,a+1+n);
	s.insert(-1),s.insert(inf);s.insert(a[1].id); 
	s.insert(inf+1),s.insert(-2);
	set <int>::iterator l,r;
	int ans=0,x,y;
	for(int i=2;i<=n;i++){
		l=r=s.lower_bound(a[i].id);
		l--;l--;r++;
		x=*l+1,y=*r-1;
		x=max(1,x),y=min(y,n);
		ans=max(ans,query(rt[x-1],rt[y],a[i].x));
		s.insert(a[i].id); 
	}
	printf("%d",ans);
	return 0;
}
