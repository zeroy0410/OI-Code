#include<bits/stdc++.h>
#define M 300005
#define LL long long 
double esp=1e-10;
using namespace std;
int n,tot=0;
struct node{
	double a,b;
}A[M];
double ans=0,Ans=0;
struct Node{
	double x,k,b;
	bool operator < (const Node& res)const{
		return x<res.x;
	}
}Q[M];
double K=0,res=0;
int main(){
	freopen("spongebob.in","r",stdin);
	freopen("spongebob.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&A[i].a,&A[i].b);
		if(A[i].a==0)
			ans+=abs(A[i].b);
		else {
			if(A[i].a<0){A[i].a=-A[i].a;A[i].b=-A[i].b;}
			double tmp=1.0*(-A[i].b)/A[i].a;
			Q[++tot].x=tmp;Q[tot].k=A[i].a;Q[tot].b=A[i].b;
		}
	}
	sort(Q+1,Q+tot+1);
	for(int i=1;i<=n;i++){
		if(A[i].a==0)continue;
		res=res+abs(Q[tot].x*A[i].a+A[i].b);
	}
	Ans=res;
	for(int i=1;i<=tot;i++)K+=Q[i].k;
	int las=tot;K-=2*Q[tot].k;
	for(int i=tot-1;i>=1;i--){
		double l=Q[las].x-Q[i].x;
		res-=K*l;
		Ans=min(Ans,res);
		K-=2*Q[i].k;
		las=i;
	}
	printf("%.8lf\n",Ans+ans);
	return 0;
}
