#include<cstdio>
#include<algorithm>
#define M 100005
using namespace std;
int n,K;
struct BIT{
	int C[M];
	void Add(int x,int d){
		x++;
		while(x<=K+1){
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
	void update(int l,int r,int d){
		Add(l,d);Add(r+1,-d);
	}
}Tr;
int main(){
	freopen("trample.in","r",stdin);
	freopen("trample.out","w",stdout);
	scanf("%d%d",&n,&K);
	if(n==0){puts("fafa");return 0;}
	for(int i=1,op,l,r,x;i<=n;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&l,&r);
			if(r-l+1>=K){Tr.update(0,K-1,1);}
			else {
				l=l%K;
				r=r%K;
				if(l<=r)Tr.update(l,r,1);
				else Tr.update(0,r,1),Tr.update(l,K-1,1);
			}
		}
		else if(op==2){
			scanf("%d%d",&l,&r);
			if(r-l+1>=K){Tr.update(0,K-1,-1);}
			else {
				l=l%K;
				r=r%K;
				if(l<=r)Tr.update(l,r,-1);
				else Tr.update(0,r,-1),Tr.update(l,K-1,-1);
			}
		}
		else {
			scanf("%d",&x);
			printf("%d\n",Tr.sum(x%K));
		}
	}	
	return 0;
}
