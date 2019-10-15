#include<bits/stdc++.h>
#define M 500005
#define LL long long
using namespace std;
struct node{
	int x,l,r;
	bool operator < (const node& res)const{
		return x<res.x;
	}
}A[M];
struct Node{
	int x,y;LL v;
	bool operator < (const Node & res)const{
		return y<res.y;
	}
};
int n,X;
set<Node>S;
set<Node>::iterator it,tmp;
int main(){
	freopen("speike.in","r",stdin);
	freopen("speike.out","w",stdout);
	scanf("%d%d",&n,&X);
	for(int i=1,x1,x2,y1,y2;i<=n;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1>x2)swap(x1,x2);
		if(y1>y2)swap(y1,y2);
		A[i]=(node){x1,y1,y2};
	}
	sort(A+1,A+n+1);
	S.insert((Node){0,0,0});
	for(int i=1;i<=n;i++){
		LL tl=1e18,tr=1e18;
		for(it=S.lower_bound((Node){0,A[i].l,0});it!=S.end()&&it->y<=A[i].r;){
			tl=min(tl,it->v+A[i].x-it->x+it->y-A[i].l);
			tr=min(tr,it->v+A[i].x-it->x+A[i].r-it->y);
			tmp=it++;S.erase(tmp);
		}
		if(tl!=1e18)S.insert((Node){A[i].x,A[i].l,tl});
		if(tr!=1e18)S.insert((Node){A[i].x,A[i].r,tr});
	}
	LL ans=1e18;
	for(it=S.begin();it!=S.end();it++)
		ans=min(ans,it->v+X-it->x+abs(it->y));
	printf("%lld\n",ans);
	return 0;
}
