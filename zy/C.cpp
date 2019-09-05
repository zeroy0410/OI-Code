#include<bits/stdc++.h>
using namespace std;
double dis[40][1<<12|5];
int n,k,base,st[40];
struct node{
	int x,y;
}A[40];
double len2(node &a,node &b){
	return sqrt( (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) );
}
bool vis[40][1<<12|5];
struct Heap{
	double d;int x,s;
	bool operator <(const Heap &_)const{
		return d>_.d;
	}
};
priority_queue<Heap>Q;
void Work(){
	for(int i=0;i<=n;i++)
		for(int j=0;j<=base;j++)
			vis[i][j]=0,dis[i][j]=1e50;
	Q.push((Heap){0.0,0,0});
	while(!Q.empty()){
		Heap v=Q.top();Q.pop();
		if(vis[v.x][v.s])continue;
		vis[v.x][v.s]=1;
		for(int j=0;j<=n;j++)if(j!=v.x){
			Heap u=v;
			u.x=j,u.s|=st[j];
			u.d+=len2(A[v.x],A[j]);
			if(dis[u.x][u.s]>u.d){
				dis[u.x][u.s]=u.d;
				Q.push(u);
			}
		}
	}
}
int main(){
	for(int _=(scanf("%d",&_),_);_;_--){
		scanf("%d%d",&n,&k);
		base=(1<<k)-1;
		for(int i=1;i<=n;i++)scanf("%d%d",&A[i].x,&A[i].y);
		int all=0;
		char s[20];
		for(int i=1;i<=n;i++){
			scanf("%s",s);st[i]=0;
			for(int j=0;j<k;j++)st[i]|=(s[j]=='1')<<j;
			all|=st[i];
		}
		if(all!=base){puts("-1");continue;}
		Work();
		printf("%.8lf\n",dis[0][base]);
	}
	return 0;
}
