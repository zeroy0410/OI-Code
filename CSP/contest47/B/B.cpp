#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,q,top;
struct node{ 
	LL l,r; 
}stk[M];
LL getsum(LL l,LL r){ 
	return (n-l+1+n-r+1)*(r-l+1)/2;
}
LL ans=0;
void Add(LL x){
	LL ad=0;
	while(top&&1+ad+x>=stk[top].l){
		ad+=stk[top].r-stk[top].l+1;
		ans-=getsum(stk[top].l,stk[top].r);
		top--;
	}
	stk[++top]=(node){1,min(x+ad,1LL*n)};
	ans+=getsum(1,min(x+ad,1LL*n));
}
void Del(LL x){
	while(top&&x){
		if(stk[top].r-stk[top].l+1<=x){
			x-=stk[top].r-stk[top].l+1;
			ans-=getsum(stk[top].l,stk[top].r);
			top--;
		}	
		else {
			ans-=getsum(stk[top].l,stk[top].r);
			stk[top].l+=x;x=0;
			ans+=getsum(stk[top].l,stk[top].r);
		}
	}
//	cout<<stk[top].l<<' '<<stk[top].r<<endl;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1,x;i<=q;i++){
		scanf("%d",&x);
		if(x>=0)Add(x);
		else Del(-x);
		printf("%lld\n",ans);
	}
	return 0;
}
