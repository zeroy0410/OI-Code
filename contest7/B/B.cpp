#include<bits/stdc++.h>
#define M 5005
#define LL long long
#define A(x,y) T[(x-1)*m+y]
using namespace std;
bool mm1;
int n,m,q;
int xn,x0,a,b,c,d;
int T[M*M];
void Init(){
	scanf("%d%d%d%d%d",&x0,&a,&b,&c,&d);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n*m;i++)T[i]=i;
	for(int i=1;i<=n*m;i++){
		xn=((1LL*a*x0*x0+1LL*b*x0)%d+c)%d;
		swap(T[i],T[xn%i+1]);
		x0=xn;
	}
	for(int i=1,u,v;i<=q;i++){
		scanf("%d%d",&u,&v);
		swap(T[u],T[v]); 
	}
}
struct node{
	short x,y;
	bool operator < (const node& res)const{
		if(x!=res.x)return x<res.x;
		return y<res.y;
	}
}mp[M*M];
set<node>wk;
set<node>::iterator it;
int ans[M+M],acnt=0;
bool mm2;
int main(){
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	Init();
	wk.clear();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			mp[A(i,j)]=(node){i,j};
	wk.insert((node){1,1});
	wk.insert((node){n,m});
	ans[++acnt]=A(1,1);
	ans[++acnt]=A(n,m);
	for(int i=1;i<=n*m;i++){
		if(mp[i].x==1&&mp[i].y==1)continue;
		if(mp[i].x==n&&mp[i].y==m)continue;
		short x=mp[i].x,y=mp[i].y;
		it=wk.lower_bound((node){mp[i].x,mp[i].y});
		short x2=it->x,y2=it->y;
		it--;
		short x1=it->x,y1=it->y;
		if(x1<=x&&x2>=x&&y1<=y&&y2>=y){
			ans[++acnt]=i;
			wk.insert(mp[i]);
		}
	}
	sort(ans+1,ans+acnt+1);
	for(int i=1;i<=acnt;i++)
		printf("%d%c",ans[i]," \n"[i==acnt]);
	return 0;
}
