#include<bits/stdc++.h>
using namespace std;
#define N 5003
#define Mo(a) (a>=mo?a-=mo:a)
bool st;
const int mo=1e9+7;
int n,m,k,b,s,e,HEAD[N],Ne[N*4],E[N*4];
int ans,DP[N][32][4],Dep[N],F[N],Son[N];
int Tmp[32][4];
bool ed;
void ADD(int s,int e) {
	Ne[++b]=HEAD[s],HEAD[s]=b,E[b]=e;
}
void DFS(int i,int f) {
	Dep[i]=Dep[f]+1,F[i]=f;
	for(int z=HEAD[i]; z; z=Ne[z])
		if(E[z]!=f) {
			if(!Dep[E[z]])DFS(E[z],i);
			else if(Dep[i]>Dep[E[z]])for(int now=i; now!=E[z]; now=F[now])Son[F[now]]=now;
		}
}
void DO(int i) {
	DP[i][1][1]=1;
	for(int z=HEAD[i]; z; z=Ne[z]) {
		if(F[E[z]]!=i||E[z]==Son[i])continue;
		DO(E[z]),e=E[z];
		memcpy(Tmp,DP[i],sizeof(Tmp));
		for(int j=1; j!=k; ++j)
			for(int o=k-j; o; --o)
				DP[i][j+o][1]=(1ll*Tmp[j][1]*DP[e][o][1]+DP[i][j+o][1])%mo;
	}
	if(Son[i]) {
		DO(Son[i]),e=Son[i];
		memcpy(Tmp,DP[i],sizeof(Tmp));
		for(int j=1; j!=k; ++j)
			for(int o=k-j; o; --o)
				DP[i][j+o][1]=(1ll*Tmp[j][1]*DP[e][o][1]+DP[i][j+o][1])%mo;
		if(Son[F[i]]!=i) {
			for(int j=1; j!=k; ++j)
				for(int o=k-j; o; --o)
					DP[i][j+o][1]=(1ll*Tmp[j][1]*(DP[e][o][0]+DP[e][o][2])+DP[i][j+o][1])%mo;
		} else {
			for(int j=1; j!=k; ++j)
				for(int o=k-j; o; --o) {
					DP[i][j+o][0]=(1ll*Tmp[j][1]*(DP[e][o][0]+DP[e][o][2])+DP[i][j+o][0])%mo;
					DP[i][j+o][3]=(1ll*Tmp[j][1]*DP[e][o][3]+DP[i][j+o][3])%mo;
				}
			for(int j=1; j<=k; ++j)
				DP[i][j][2]=DP[e][j][2]+DP[e][j][3],Mo(DP[i][j][2]);
		}
	} else if(Son[F[i]]==i)
		for(int j=1; j<=k; ++j)
			DP[i][j][3]=DP[i][j][1];
	for(int j=1; j<=k; ++j)
		ans+=DP[i][j][1],Mo(ans);
}
int main() {
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	scanf("%d %d %d",&n,&m,&k),b=1;
	for(int i=1; i<=m; ++i) {
		scanf("%d %d",&s,&e);
		ADD(s,e),ADD(e,s);
	}
	DFS(1,0),DO(1);
	printf("%d\n",ans);
	return 0;
}

