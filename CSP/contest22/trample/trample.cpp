#include<cstdio>
#include<algorithm>
#define M 200005
using namespace std;
int n,K;
struct BIT{
	int C[M];
	void Add(int x,int d){
		x++;
		while(x<M){
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
struct PK0{
	struct que{
		int op,l,r,x;
	}Q[M];
	int B[M<<1],bcnt;
	void solve(){
		bcnt=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&Q[i].op);
			if(Q[i].op==1||Q[i].op==2){
				scanf("%d%d",&Q[i].l,&Q[i].r);
				B[++bcnt]=Q[i].l;B[++bcnt]=Q[i].r;
			}
			else {
				scanf("%d",&Q[i].x);
				B[++bcnt]=Q[i].x;
			}
		}
		sort(B+1,B+bcnt+1);
		bcnt=unique(B+1,B+bcnt+1)-B-1;
		for(int i=1;i<=n;i++){
			if(Q[i].op==1||Q[i].op==2){
				int l=lower_bound(B+1,B+bcnt+1,Q[i].l)-B;
				int r=lower_bound(B+1,B+bcnt+1,Q[i].r)-B;
				if(Q[i].op==1)Tr.update(l,r,1);
				else Tr.update(l,r,-1);
			}
			else {
				int x=lower_bound(B+1,B+bcnt+1,Q[i].x)-B;
				printf("%d\n",Tr.sum(x));
			}
		}
	}
}pk0;
int main(){
	scanf("%d%d",&n,&K);
	if(n==0){puts("fafa");return 0;}
	else if(K==0)pk0.solve();
	else {
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
	}
	return 0;
}
