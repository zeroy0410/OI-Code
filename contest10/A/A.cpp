#include<bits/stdc++.h>
#define M 350005
#define LL long long
using namespace std;
int n,aa;
vector<int>wk[M];
int A[M];
int dxy[6][3]={0,0,1,0,0,-1,0,1,0,0,-1,0,1,0,0,-1,0,0};
struct P100{
	int a[75][75][75];
	int mark[M];
	struct node{int x,y,z,id;}pos[M];
	bool ca(int x,int y,int z){return x>=0&&x<aa&&y>=0&&y<aa&&z>=0&&z<aa;}
	bool check(int x1,int y1,int z1,int x2,int y2,int z2){
		return (x1==x2&&y1==y2&abs(z1-z2)==1)||
				(x1==x2&&z1==z2&abs(y1-y2)==1)||
				(z1==z2&&y1==y2&abs(x1-x2)==1);
	}
	bool can(int u,int x,int y,int z){
		bool flag=1;
		int c=0;
		for(int j=0;j<wk[u].size()&&flag;j++){
			int tp=wk[u][j];
			if(pos[tp].id!=0)c++;
			if(pos[tp].id!=0&&
			!check(x,y,z,pos[tp].x,pos[tp].y,pos[tp].z))flag=0;
		}
		for(int j=0;j<6&&flag;j++){
			int nx=x+dxy[j][0];
			int ny=y+dxy[j][1];
			int nz=z+dxy[j][2];
			if(!ca(nx,ny,nz))continue;
			if(a[nx][ny][nz]==0)continue;
			c--;
		}
		if(c!=0)flag=0;
		return flag;
	}
	queue<node>q;
	int qq[M];
	LL mi,mx;
	void dfs(int e,LL su){
		if(e==qq[0]+1){
			LL res=0;
			mi=min(su,mi);
			mx=max(su,mx);
			return;
		}
		int x=pos[qq[e]].x,y=pos[qq[e]].y,z=pos[qq[e]].z;
		for(int i=0;i<6;i++){
			int nx=x+dxy[i][0];
			int ny=y+dxy[i][1];
			int nz=z+dxy[i][2];
			LL Ad=0;
			for(int j=0;j<n;j++){
				if(ca(nx,ny,nz)){
					mark[a[nx][ny][nz]]++;
					if(mark[a[nx][ny][nz]]==1)Ad+=A[a[nx][ny][nz]];
					nx=nx+dxy[i][0];
					ny=ny+dxy[i][1];
					nz=nz+dxy[i][2];
				}
				else break;
			}
			dfs(e+1,su+Ad);
			nx=x+dxy[i][0];
			ny=y+dxy[i][1];
			nz=z+dxy[i][2];
			for(int j=0;j<n;j++){
				if(ca(nx,ny,nz)){
					mark[a[nx][ny][nz]]--;
					nx=nx+dxy[i][0];
					ny=ny+dxy[i][1];
					nz=nz+dxy[i][2];
				}
				else break;
			}
		}
	}
	void solve(){
		mx=-1e18;mi=1e18;
		memset(a,0,sizeof(a));
		int st;
		for(int i=1;i<=n;i++)
			if(wk[i].size()==3){st=i;a[0][0][0]=i;pos[i]=(node){0,0,0,i};break;}
		q.push((node){0,0,0,st});
		while(!q.empty()){
			node e=q.front();q.pop();
			for(int i=0;i<6;i++){
				int nx=e.x+dxy[i][0];
				int ny=e.y+dxy[i][1];
				int nz=e.z+dxy[i][2];
				if(!ca(nx,ny,nz))continue;
				if(a[nx][ny][nz])continue;
				for(int j=0;j<wk[e.id].size();j++){
					int u=wk[e.id][j];
					if(pos[u].id!=0)continue;
					if(can(u,nx,ny,nz)){
						a[nx][ny][nz]=u;
						pos[u]=(node){nx,ny,nz,u};
						q.push((node){nx,ny,nz,u});
						break;
					}
				}
			}
		}
		for(int i=1;i<=n;i++)if(A[i]==0)qq[++qq[0]]=i;
		dfs(1,0);
		printf("%lld %lld\n",mi,mx);
	}
}p100;
int main(){
	freopen("glitter.in","r",stdin);
	freopen("glitter.out","w",stdout);
	scanf("%d",&n);aa=n;n=n*n*n;
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		char c;int res=0;
		while(1){
			c=getchar();
			if(c>='0'&&c<='9')break;
		}
		res=c-'0';bool f=1;
		while(1){
			if(!f)res=0;f=0;
			while(1){
				c=getchar();
				if(c<'0'||c>'9')break;
				res=res*10+c-'0';
			}
			wk[i].push_back(res);
			if(c=='\n'||c=='\r'||c==EOF)break;
		}
	}
	p100.solve();
	return 0;
}
