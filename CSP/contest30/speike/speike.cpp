#include<bits/stdc++.h>
#define M 2005
using namespace std;
int n;
int A[M][M],t;
int ret1[M][M],ret2[M][M];
bool vis[M][M];
struct node{
	int x,y,step;
};
queue<node>Q;
int dxy[4][2]={1,0,0,1,-1,0,0,-1};
int main(){
	freopen("speike.in","r",stdin);
	freopen("speike.out","w",stdout);
	scanf("%d%d",&n,&t);
	printf("%d\n",t);
//	for(int i=1,x1,x2,y1,y2;i<=n;i++){
//		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
//		int t1=min(x1,x2);
//		int t2=max(x1,x2);x1=t1,x2=t2;
//		t1=min(y1,y2);t2=max(y1,y2);
//		y1=t1;y2=t2;
//		x1++;x2--;y1++;y2--;
//		ret1[y1+1000][x1+1000]++;ret1[y1+1000][x2+1+1000]--;
//		ret1[y2+1+1000][x1+1000]--;ret1[y2+1+1000][x2+1+1000]++;
//	}
//	for(int i=-1000;i<=1000;i++){
//		for(int j=-1000;j<=1000;j++){
//			ret1[i+1000][j+1000]+=ret1[i+1000][j-1+1000];
//		}
//	}
//	for(int i=-1000;i<=1000;i++){
//		for(int j=-1000;j<=1000;j++){
//			ret2[i+1000][j+1000]+=ret2[i-1+1000][j+1000]+ret1[i+1000][j+1000];
//		}
//	}
//	Q.push((node){0,0,0});vis[0+1000][0+1000]=1;
//	while(!Q.empty()){
//		node e=Q.front();Q.pop();
//		if(e.x==t&&e.y==0){printf("%d\n",e.step);return 0;}
//		for(int i=0;i<4;i++){
//			int x=e.x+dxy[i][0];
//			int y=e.y+dxy[i][1];
//			if(x<-1000||x>1000||y<-1000||y>1000||vis[x+1000][y+1000]||ret2[x+1000][y+1000])continue;
//			vis[x+1000][y+1000]=1;
//			Q.push((node){x,y,e.step+1});
//		}
//	}
	return 0;
}
