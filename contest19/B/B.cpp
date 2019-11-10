#include<bits/stdc++.h>
#define M 505
using namespace std;
int n;
struct Node{
	int x,y;
	bool operator < (const Node& res)const{
		return y>res.y;
	}
};
priority_queue<Node>Q;
struct P100{
	struct node{int to,co;};
	vector<node>G[250005];
	int dis[250005];
	int ID[505][505];
	bool vis[250005];
	void solve(){
		int s=n*n+2,t=s-1;
		for(int i=0;i<=n;i++)ID[0][i]=t,ID[i][0]=s;
		for(int i=0;i<=n+1;i++)ID[n+1][i]=s,ID[i][n+1]=t;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ID[i][j]=(i-1)*n+j;
		for(int i=1;i<=n+1;i++){
			for(int j=1,x;j<=n;j++){
				scanf("%d",&x);
				G[ID[i][j]].push_back((node){ID[i-1][j],x});
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=0,x;j<=n;j++){
				scanf("%d",&x);
				G[ID[i][j]].push_back((node){ID[i][j+1],x});
			}
		}
		for(int i=0;i<=n;i++){
			for(int j=1,x;j<=n;j++){
				scanf("%d",&x);
				G[ID[i][j]].push_back((node){ID[i+1][j],x});
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1,x;j<=n+1;j++){
				scanf("%d",&x);
				G[ID[i][j]].push_back((node){ID[i][j-1],x});
			}
		}
		n++;
		memset(dis,60,sizeof(dis));
		dis[s]=0;Q.push((Node){s,0});
		while(!Q.empty()){
			Node e=Q.top();Q.pop();
			if(vis[e.x])continue;
			vis[e.x]=1;
			for(int i=0;i<G[e.x].size();i++){
				int u=G[e.x][i].to,c=G[e.x][i].co;
				if(dis[u]>e.y+c){
					dis[u]=e.y+c;
					Q.push((Node){u,dis[u]});
				}
			}
		}
		printf("%d\n",dis[t]);
	}
}p100;
int main(){
	freopen("altitude.in","r",stdin);
	freopen("altitude.out","w",stdout);	
	scanf("%d",&n);
	p100.solve();
	return 0;
}
