#include<bits/stdc++.h>
#define M 350005
#define LL long long
using namespace std;
bool mm1;
int n,aa;
vector<int>wk[M];
int A[M];
int dxy[6][3]={0,0,1,0,0,-1,0,1,0,0,-1,0,1,0,0,-1,0,0};
struct P30{
	int a[75][75][75];
	int mark[M];
	struct node{
		int x,y,z,id;
	}pos[M];
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
	int qq[M],ct;
	LL mi,mx;
	LL sum1[75][75][75],sum2[75][75][75],sum3[75][75][75];
	void Init(){
		for(int i=0;i<aa;i++){
			for(int j=0;j<aa;j++){
				sum1[i][j][0]=A[a[i][j][0]];
				sum2[i][0][j]=A[a[i][0][j]];
				sum3[0][i][j]=A[a[0][i][j]];
				for(int k=1;k<aa;k++){
					sum1[i][j][k]=sum1[i][j][k-1]+A[a[i][j][k]];
					sum2[i][k][j]=sum2[i][k-1][j]+A[a[i][k][j]];
					sum3[k][i][j]=sum3[k-1][i][j]+A[a[k][i][j]];
				}
			}
		}
	}
	LL query(int x1,int y1,int z1,int x2,int y2,int z2){
		if(x1==x2&&y1==y2){
			if(z1>z2)swap(z1,z2);
			return sum1[x1][y1][z2]-(z1>0?sum1[x1][y1][z1-1]:0);
		}
		if(x1==x2&&z1==z2){
			if(y1>y2)swap(y1,y2);
			return sum2[x1][y2][z1]-(y1>0?sum2[x1][y1-1][z1]:0);
		}
		if(y1==y2&&z1==z2){
			if(x1>x2)swap(x1,x2);
			return sum3[x2][y1][z1]-(x1>0?sum3[x1-1][y1][z1]:0);
		}
	}
	struct Node{
		int x1,y1,z1,x2,y2,z2;
		bool operator < (const Node& res) const{
			if(x1!=res.x1)return x1<res.x1;
			if(x2!=res.x2)return x2<res.x2;
			if(y1!=res.y1)return y1<res.y1;
			if(y2!=res.y2)return y2<res.y2;
			if(z1!=res.z1)return z1<res.z1;
			if(z2!=res.z2)return z2<res.z2;
		}
		bool operator == (const Node& res)const{
			return x1==res.x1&&x2==res.x2&&y1==res.y1&&y2==res.y2&&z1==res.z1&&z1==res.z2;
		}
	}tpp[M],cz[M];
	int tcnt,cnt;
	Node getlen(int x,int y,int z,int d){
		if(d==0)return (Node){x,y,z,x,y,aa};
		if(d==1)return (Node){x,y,0,x,y,z};
		if(d==2)return (Node){x,y,z,x,aa,z};
		if(d==3)return (Node){x,0,z,x,y,z};
		if(d==4)return (Node){x,y,z,aa,y,z};
		if(d==5)return (Node){0,y,z,x,y,z};
	}
	Node check_cho(Node u,Node v){
		int tmp[4];
		if(u.x2<v.x1)return (Node){-1};
		tmp[0]=u.x1,tmp[1]=u.x2,tmp[2]=v.x1,tmp[3]=v.x2;
		sort(tmp,tmp+4);
		int nx1=tmp[1],nx2=tmp[2];
		if(u.y2<v.y1)return (Node){-1};
		tmp[0]=u.y1,tmp[1]=u.y2,tmp[2]=v.y1,tmp[3]=v.y2;
		sort(tmp,tmp+4);
		int ny1=tmp[1],ny2=tmp[2];
		if(u.z2<v.z1)return (Node){-1};
		tmp[0]=u.z1,tmp[1]=u.z2,tmp[2]=v.z1,tmp[3]=v.z2;
		sort(tmp,tmp+4);
		int nz1=tmp[1],nz2=tmp[2];
		return (Node){nx1,ny1,nz1,nx2,ny2,nz2};
	}
	void dfs(int e,LL su){
		if(e==qq[0]+1){
			for(int i=1;i<=tcnt;i++){
				int c=0;
				for(int j=1;j<=cnt;j++){
					Node w=check_cho(tpp[i],cz[j]);
					if(w.x1!=-1)c++;
				}
				if(c>1)su-=1LL*(c-1)*query(tpp[i].x1,tpp[i].y1,tpp[i].z1,tpp[i].x2,tpp[i].y2,tpp[i].z2);
				mi=min(su,mi);
				mx=max(su,mx);
			}
			return;
		}
		int x=pos[qq[e]].x,y=pos[qq[e]].y,z=pos[qq[e]].z;
		for(int i=0;i<6;i++){
			Node w=getlen(x,y,z,i);
			cz[++cnt]=w;
			LL ad=query(w.x1,w.y1,w.z1,w.x2,w.y2,w.z2);
			dfs(e+1,su+ad);
			cnt--;
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
		Init();
		for(int i=1;i<=n;i++)if(A[i]==0)qq[++qq[0]]=i;
		for(int i=1;i<=qq[0];i++){
			for(int r=0;r<6;r++){
				int x=pos[qq[i]].x,y=pos[qq[i]].y,z=pos[qq[i]].z;
				Node t1=getlen(x,y,z,r);
				for(int j=1;j<=qq[0];j++){
					for(int o=0;o<6;o++){
						int xx=pos[qq[j]].x,yy=pos[qq[j]].y,zz=pos[qq[j]].z;
						Node t2=getlen(xx,yy,zz,o);
						Node w=check_cho(t1,t2);
						if(w.x1!=-1)tpp[++tcnt]=w;
					}
				}
			}
		}
		sort(tpp+1,tpp+tcnt+1);
		tcnt=unique(tpp+1,tpp+tcnt+1)-tpp-1;
		ct=0;
		dfs(1,0);
		printf("%lld %lld\n",mi,mx);
	}
}p30;
bool mm2;
int main(){
//	freopen("glitter.in","r",stdin);
//	freopen("glitter.out","w",stdout);
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
	p30.solve();
	return 0;
}
