#include<bits/stdc++.h>
using namespace std;
const int sm = 1200;
const int sn = 3660;
const int Inf = 0x3f3f3f3f;
int M,N,tot=1,Ct,Ans,Sum,S,T;
int to[sn],nxt[sn],hd[sm];
int _c[sn],c[sn],f[sn];
int vis[sm],cst[sm],pre[sm];
int Min(int x,int y) { return x<y?x:y;}
void Add(int u,int v,int x,int y) {
	to[++tot]=v,nxt[tot]=hd[u],hd[u]=tot;
	f[tot]=x,_c[tot]=c[tot]=y;
	to[++tot]=u,nxt[tot]=hd[v],hd[v]=tot;
	f[tot]=-x,_c[tot]=c[tot]=0;
}
void SPFA() {
	Ans=0; int df;
	while(true) {
		for(int i=1;i<=T;++i) 
			cst[i]=-Inf,vis[i]=pre[i]=0;
		queue<int>q; int t;
		q.push(S),vis[S]=1,cst[S]=0;
		while(!q.empty()) {
			t=q.front(),q.pop();
			vis[t]=0;
			for(int i=hd[t];i;i=nxt[i]) 
				if(cst[to[i]]<cst[t]+f[i]&&c[i]>0) {
					cst[to[i]]=cst[t]+f[i];
					pre[to[i]]=i;
					if(!vis[to[i]]) {
						vis[to[i]]=1;
						q.push(to[i]);
					}
				}
		}
		if(cst[T]==-Inf) break;
		df=Inf;
		for(int i=T;i!=S;i=to[pre[i]^1])
			df=Min(df,c[pre[i]]);
		for(int i=T;i!=S;i=to[pre[i]^1])
			c[pre[i]]-=df,c[pre[i]^1]+=df;
		Ans+=df*cst[T];
	}
	printf("%d\n",Ans);
}

int main() {
	int v,A;
	scanf("%d%d",&M,&N);
	Sum=M*N+(((N-1)*N)>>1);
	S=Sum<<1|1,T=S+1;
	for(int i=1;i<=N;++i)
		for(int j=1;j<=M+i-1;++j) {
			scanf("%d",&v); ++Ct;
			Add(Ct,Ct+Sum,v,1);
			if(i==1) Add(S,Ct,0,1);
			if(i==N) Add(Ct+Sum,T,0,1);
			if(i!=N) {
				A=M*i+(i*(i-1)>>1)+j;
				Add(Ct+Sum,A,0,1);
				if(j+1<=M+i) Add(Ct+Sum,++A,0,1);
			}
		}
	for(int cas=1;cas<=3;++cas) {
		if(cas==1) SPFA();
		if(cas==2) {
			for(int i=1;i<=Sum;++i) {
				for(int j=hd[i];j;j=nxt[j])
					if(to[j]==i+Sum&&_c[j]==1) 
						_c[j]=Inf;
				for(int j=hd[i+Sum];j;j=nxt[j])
					if(to[j]==T&&_c[j]==1) 
						_c[j]=Inf;
			}
			memcpy(c,_c,sizeof(c));
			SPFA();
		}
		if(cas==3) {
			for(int i=1;i<=Sum;++i)
				for(int j=hd[i+Sum];j;j=nxt[j])
					if(to[j]!=S&&to[j]!=T&&to[j]!=i&&_c[j]==1)
						_c[j]=Inf;
			memcpy(c,_c,sizeof(c));
			SPFA();
		}
	}
	return 0;
}