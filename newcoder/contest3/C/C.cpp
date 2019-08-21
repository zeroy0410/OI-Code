#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n;
int l[M],r[M];
struct P60{
	int f[2][M*3][20],lg2[M*3];
	void Init_RMQ(bool fl){
		for(int i=1;i<=3*n;i++)
			if(!fl)f[fl][i][0]=i-l[i];
			else f[fl][i][0]=i+r[i];
		lg2[1]=0;
		for(int i=2;i<=3*n;i++)lg2[i]=lg2[i>>1]+1;
		for(int j=1;(1<<j)<=3*n;j++)
			for(int i=1;i+(1<<j)-1<=3*n;i++)
				if(!fl)f[fl][i][j]=min(f[fl][i][j-1],f[fl][i+(1<<(j-1))][j-1]);
				else f[fl][i][j]=max(f[fl][i][j-1],f[fl][i+(1<<(j-1))][j-1]);
	}
	int query(bool fl,int l,int r){
		int k=lg2[r-l+1];
		if(!fl)return min(f[fl][l][k],f[fl][r-(1<<k)+1][k]);
		return max(f[fl][l][k],f[fl][r-(1<<k)+1][k]);
	}
	void solve(){
		for(int i=n+1;i<=3*n;i++)
			l[i]=l[i-n],r[i]=r[i-n];
		Init_RMQ(0);Init_RMQ(1);
		for(int i=n+1;i<=2*n;i++){
			int L=i,R=i;
			if(n==1){printf("0 ");continue;}
			int now=0;
			while(1){
				now++;
				int tl=L,tr=R;
				L=query(0,tl,tr);
				R=query(1,tl,tr);
				if(R-L+1>=n)break;
			}
			printf("%d ",now);
		}
		puts("");
	}
}p60;
struct P100{
	void solve(){
		
	}
}p100;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&l[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&r[i]);
	p60.solve();
	return 0;
}