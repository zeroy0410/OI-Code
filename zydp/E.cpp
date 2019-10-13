#include<bits/stdc++.h>
using namespace std;
const int M=1e9;
int m,n,f[13][4096],F[13],field[13][13];
bool state[4096];
int main(){
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>field[i][j];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			F[i]=(F[i]<<1)+field[i][j];
	int base=1<<n;
	for(int i=0;i<base;i++)
		state[i]=((i&(i<<1))==0)&&((i&(i>>1))==0);
	f[0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<base;j++)
			if(state[j]&&((j&F[i])==j))
				for(int k=0;k<base;k++)
					if((k&j)==0)
						f[i][j]=(f[i][j]+f[i-1][k])%M;
	int ans=0;
	for(int i=0;i<base;i++)
		ans+=f[m][i],ans%=M;
	cout<<ans<<endl;
	return 0;
}
