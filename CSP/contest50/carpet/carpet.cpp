#include<bits/stdc++.h>
#define M 300005
#define LL long long
using namespace std;
int x[4],y[4],n,P,Q,T;
struct Matrix{
	int x1,y1,x2,y2;
	Matrix operator + (const Matrix& res){
		if(x2<=res.x1||y2<=res.y1||res.x2<=x1||res.y2<=y1)return (Matrix){0,0,0,0};
		x[0]=x1;x[1]=x2;x[2]=res.x1;x[3]=res.x2;
		y[0]=y1;y[1]=y2;y[2]=res.y1;y[3]=res.y2;
		sort(x,x+4);sort(y,y+4);
		return (Matrix){x[1],y[1],x[2],y[2]};
	}
}A[M],pre[M],las[M];
LL ans;
int main(){
	freopen("carpet.in","r",stdin);
	freopen("carpet.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d%d%d",&P,&Q,&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
		pre[0]=(Matrix){0,0,P,Q};
		for(int i=1;i<=n;i++)
			pre[i]=pre[i-1]+A[i];
		las[n+1]=(Matrix){0,0,P,Q};
		for(int i=n;i>=1;i--)
			las[i]=las[i+1]+A[i];
		for(int i=1;i<=n;i++){
			Matrix tmp=pre[i-1]+las[i+1];
			ans=ans+1LL*(tmp.x2-tmp.x1)*(tmp.y2-tmp.y1);
			ans-=1LL*(pre[n].x2-pre[n].x1)*(pre[n].y2-pre[n].y1);
		}
		ans+=1LL*(pre[n].x2-pre[n].x1)*(pre[n].y2-pre[n].y1);
		printf("%lld\n",ans);
	}
	return 0;
}
