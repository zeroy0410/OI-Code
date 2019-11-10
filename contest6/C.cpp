#include<bits/stdc++.h>
#define M 1005
using namespace std;
int n,m,K,lmi,lmx,c1,c2,F;
int A[1005][1005];
int dxy[4][2]={1,0,-1,0,0,1,0,-1};
bool can(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;	
}
void fall(int x,int y){
	if(can(x-1,y))A[x][y]=A[x-1][y],fall(x-1,y);	
}
struct node{
	int x,y,step;	
};
queue<node>q;
bool vis[M][M];
void bfs(){
//	while(!q.empty())q.pop();
//	q.push((node){1,1,0});vis[1][1]=1;
//	while(!q.empty()){
//		node e=q.front();q.pop();
//		for
//	}
//	vis[1][1]=1;
//	int x=1,y=1;
//	for(int i=1;i<=lmi;i++){
//		if(	
//	}
}
int main(){
	freopen("game1.in","r",stdin);
	freopen("game1.out","w",stdout);
	srand(time(NULL));
	scanf("%d%d%d%d%d%d%d%d",&n,&m,&K,&lmi,&lmx,&c1,&c2,&F);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&A[i][j]);
	cout<<1<<endl;
	for(int i=1;i<=m;i++){
		printf("%d %d ",n,i);	
	}
	return 0;
}
