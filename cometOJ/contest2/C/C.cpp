#include<bits/stdc++.h>
#define M 400005
#define LL long long
using namespace std;
int T,n,m;
int h[M],tt,D[M],in[M],fr[M];
bool vis[M],mark[M];
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
struct P60{
	int stk[M],top;
	int Q[M],qcnt;
	bool dfs_lop(int x){
		if(vis[x]==1){
			while(stk[top]!=x){
				Q[++qcnt]=stk[top--];
				vis[Q[qcnt]]=0;
			}
			Q[++qcnt]=x;
			vis[x]=0;
			return 1;
		}
		stk[++top]=x;
		vis[x]=1;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(dfs_lop(u))return 1;
		}
		top--;
		vis[x]=0;
		return 0;
	}
	int rt,de,ct;
	LL dp[M];
	void dfs(int x,LL ds){
		mark[x]=1;
		dp[x]=0;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to,c=G[i].co;
			if(u==rt&&x==de)continue;
			dfs(u,c);
			dp[x]=max(dp[x],dp[u]+c);
		}
		if(dp[x]+ds>m){ct++,dp[x]=-ds;}
	}
	void solve(){
		int ans=0;
		for(int i=1;i<=n;i++){
			if(!mark[i]){
				top=qcnt=0;
				if(!dfs_lop(i))continue;
				Q[qcnt+1]=Q[1];
				int res=1e9;
				for(int j=1;j<=qcnt;j++){
					de=Q[j+1];rt=Q[j];
					ct=0;
					dfs(rt,0);
					res=min(res,ct);
				}
				ans+=res+1;
			}
		}
		printf("%d\n",ans);
	}
}p60;
struct P100{
	int Q[M<<1],fa[M<<1][19],qcnt;
	queue<int>q;
	bool nlop[M];
	void find_lop(){
		while(!q.empty())q.pop();
		for(int i=1;i<=n;i++)
			if(!in[i])q.push(i);
		while(!q.empty()){
			int x=q.front();q.pop();
			nlop[x]=1;
			int u=fr[x];
			in[u]--;
			if(in[u]==0)q.push(u);
		}
	}
	int ct;
	LL dp[M],sum[M<<1],Ans;
	void dfs(int x){
		dp[x]=0;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to,c=G[i].co;
			if(!nlop[u])continue;
			dfs(u);
			if(dp[u]+c>m)ct++;
			else dp[x]=max(dp[x],dp[u]+c);
		}
	}
	LL f[M][19],lg2[M];
	void Init_RMQ(){
		for(int i=1;i<=qcnt;i++)f[i][0]=sum[i]+dp[Q[i]];
		lg2[1]=0;
		for(int i=2;i<=qcnt;i++)lg2[i]=lg2[i>>1]+1;
		for(int j=1;(1<<j)<=qcnt;j++)
			for(int i=1;i+(1<<j)-1<=qcnt;i++)
				f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	} 
	LL query(int l,int r){
		int k=lg2[r-l+1];
		return max(f[l][k],f[r-(1<<k)+1][k]);
	}
	void solve(){
		memset(nlop,0,sizeof(nlop));
		Ans=0;find_lop();
		for(int i=1;i<=n;i++){
			if(!nlop[i]&&!mark[i]){
				qcnt=ct=0;
				for(int j=i;!mark[j];){
					mark[j]=1;Q[++qcnt]=j;
					for(int k=h[j];k;k=G[k].nxt){
						int u=G[k].to;
						if(!nlop[u]){j=u;break;}
					}
				}
				for(int j=1;j<=qcnt;j++)dfs(Q[j]);
				for(int j=1,ed=qcnt;j<=ed;j++)Q[++qcnt]=Q[j];
				for(int j=2;j<=qcnt;j++)
					sum[j]=sum[j-1]+D[Q[j]];
				Init_RMQ();
				int res=1;
				for(int j=2;j<=qcnt;j++){
		            while(-sum[res]+query(res,j)>m)res++;
		            fa[j][0]=res-1;
		            for(int k=1;k<19;k++)
		                fa[j][k]=fa[fa[j][k-1]][k-1];
		        }
		        int ans=1e9;
		        for(int j=1;j<=qcnt>>1;j++){
		            int r=j+(qcnt>>1)-1,res=0;
		            for(int k=18;k>=0;k--)
		                if(fa[r][k]>=j)
		                    r=fa[r][k],res|=1<<k;
		            ans=min(ans,res);
		        }
		        Ans+=ans+ct+1;
			}
		}
		printf("%lld\n",Ans);
	}
}p100;
int main(){
	scanf("%d",&T);
	while(T--){
		tt=0;
		memset(h,0,sizeof(h));
		memset(vis,0,sizeof(vis));
		memset(mark,0,sizeof(mark));
		memset(in,0,sizeof(in));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&fr[i],&D[i]);
			Add(fr[i],i,D[i]);
			in[fr[i]]++;
		}
		p100.solve();
	}
	return 0;
}
