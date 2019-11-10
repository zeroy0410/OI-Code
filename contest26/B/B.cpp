#include<bits/stdc++.h>
#define M 45
using namespace std;
int n,m,K;
char S[M][M];
int bx,by;
struct P100{
	int ID[M][M],tot;
	int h[M*M],tt,Ca[M*M*2];
	struct edge{
		int nxt,to;
	}G[M*M*M];
	void Add(int a,int b){
		G[++tt]=(edge){h[a],b};
		h[a]=tt;
	}
	bool de[M*M];
	int mk[M*M],tim=0,vis[M*M];
	bool sp(int x){
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(de[u])continue;
			if(vis[u]==tim)continue;
			vis[u]=tim;
			if(mk[u]==-1||sp(mk[u])){
				mk[x]=u;
				mk[u]=x;
				return true;
			}
		}
		return false;
	}
	void solve(){
		tt=0;
		for(int i=1;i<=n;i++){
			scanf("%s",S[i]+1);
			for(int j=1;j<=m;j++)
				if(S[i][j]=='.')
					{bx=i;by=j;}
		}
		S[bx][by]='X';
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((S[i][j]=='O'&&(abs(i-bx)+abs(j-by))%2==1||
					S[i][j]=='X'&&(abs(i-bx)+abs(j-by))%2==0))
					ID[i][j]=++tot;
			}
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(ID[i][j]){
					if(ID[i+1][j])Add(ID[i][j],ID[i+1][j]);
					if(ID[i-1][j])Add(ID[i][j],ID[i-1][j]);
					if(ID[i][j+1])Add(ID[i][j],ID[i][j+1]);
					if(ID[i][j-1])Add(ID[i][j],ID[i][j-1]);
				}
			}
		memset(mk,-1,sizeof(mk));
		for(int i=1;i<=tot;i++){
			if(mk[i]==-1){
				++tim;
				sp(i);
			}
		}
		scanf("%d",&K);K*=2;
		for(int i=1;i<=K;i++){
			if(mk[ID[bx][by]]!=-1){
				int tmp=mk[ID[bx][by]];
				mk[ID[bx][by]]=mk[tmp]=-1;
				de[ID[bx][by]]=1;
				++tim;Ca[i]=sp(tmp);
			}
			else {
				de[ID[bx][by]]=1;
				Ca[i]=1;
			}
			scanf("%d%d",&bx,&by);
		}
		int res=0;
		for(int i=1;i<=K;i+=2)
			if(!Ca[i]&&!Ca[i+1])
				res++;
		printf("%d\n",res);
		for(int i=1;i<=K;i+=2)
			if(!Ca[i]&&!Ca[i+1])
				printf("%d\n",(i+1)/2);
	}
}p100;
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	p100.solve();
	return 0;
}
