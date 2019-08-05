#include<bits/stdc++.h>
#define M 500005 
using namespace std;
int n,m;
struct node{int x,y,s,t;}A[M];
struct Node{
	int x,y; 
	bool operator < (const Node& res) const{
		return x>res.x;
	}
}p[M];
priority_queue<Node>Q;
bool cmp1(node &a,node &b){return a.s<b.s;};
bool cmp2(Node &a,Node &b){return a.x<b.x;};
struct que{
	int x,id;
	bool operator < (const que& res) const{
		return x<res.x;
	}
}q[M]; 
int f[M],g[M],pcnt,qq,ans[M];
//f[i] 到达i点的最晚出发时间
//g[i] 为了赶上第i辆车的最晚出发时间
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d%d%d",&A[i].x,&A[i].y,&A[i].s,&A[i].t);
	sort(A+1,A+m+1,cmp1);memset(f,-1,sizeof(f));f[1]=1e9;
	for(int i=1;i<=m;i++){
		while(!Q.empty()){
			Node e=Q.top();
			if(e.x<=A[i].s){
				Q.pop();
				f[A[e.y].y]=max(f[A[e.y].y],g[e.y]); 
			}else break; 
		}
		g[i]=min(A[i].s,f[A[i].x]);
		Q.push((Node){A[i].t,i});
		if(A[i].y==n){p[++pcnt].x=A[i].t;p[pcnt].y=g[i];}
	}
	sort(p+1,p+pcnt+1,cmp2);
	scanf("%d",&qq);
	for(int i=1;i<=qq;i++)scanf("%d",&q[i].x),q[i].id=i;
	sort(q+1,q+qq+1);int now=-1,j=1;
	for(int i=1;i<=qq;i++){
		for(;j<=pcnt&&p[j].x<=q[i].x;j++)now=max(now,p[j].y);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=qq;i++)
		printf("%d\n",ans[i]); 
	return 0;
}
