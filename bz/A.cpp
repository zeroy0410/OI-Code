#include<bits/stdc++.h>
#define M 205
using namespace std;
int n,T,s,e,G[M][M][21],Q[M],qc;
struct in{
	int l,a,b;
}In[M];
int H[M][M],tmp[M][M];
void Floyd(){
	memset(H,0x3f,sizeof(H));
	for(int i=1;i<=qc;i++)H[i][i]=0;
	for(int r=0;r<=20;r++){
		if(r!=0){
			for(int k=1;k<=qc;k++)
				for(int i=1;i<=qc;i++)
					for(int j=1;j<=qc;j++)
						G[i][j][r]=min(G[i][j][r],G[i][k][r-1]+G[k][j][r-1]);
		}
		if(n&1<<r){
			memset(tmp,0x3f,sizeof(tmp));
			for(int k=1;k<=qc;k++)
				for(int i=1;i<=qc;i++)
					for(int j=1;j<=qc;j++)
						tmp[i][j]=min(tmp[i][j],H[i][k]+G[k][j][r]);
			memcpy(H,tmp,sizeof(H));
		}
	}
}
int main(){
	scanf("%d%d%d%d",&n,&T,&s,&e);Q[++qc]=s;Q[++qc]=e;
	memset(G,0x3f,sizeof(G));
	for(int i=1;i<=T;i++){
		scanf("%d%d%d",&In[i].l,&In[i].a,&In[i].b);
		Q[++qc]=In[i].a;Q[++qc]=In[i].b;
	}
	sort(Q+1,Q+qc+1);
	qc=unique(Q+1,Q+qc+1)-Q-1;
	for(int i=1,a,b,l;i<=T;i++){
		In[i].a=lower_bound(Q+1,Q+qc+1,In[i].a)-Q;
		In[i].b=lower_bound(Q+1,Q+qc+1,In[i].b)-Q;
		a=In[i].a,b=In[i].b,l=In[i].l;
		G[a][b][0]=G[b][a][0]=min(G[a][b][0],l);
	}
	s=lower_bound(Q+1,Q+qc+1,s)-Q;
	e=lower_bound(Q+1,Q+qc+1,e)-Q;
	Floyd();
	printf("%d\n",H[s][e]);
	return 0;
}
