#include<bits/stdc++.h>
using namespace std;
bool mm1;
int n,R,Q,T;
const double eps=1e-10;
struct P60{
	double dp[10005][25][6];
	double p;
	double dfs(int i,int j,int k){
		if(i==n+1||k==0)return 0;
		if(dp[i][j][k]!=-1)return dp[i][j][k];
		double res=0;
		res+=(dfs(i+1,min(j+1,R),min(Q,k+1))+min(j+1,R))*p;
		res+=dfs(i+1,0,k-1)*(1-p);
		return dp[i][j][k]=res;
	}
	double calc(double mid){
		p=mid;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=R;j++)
				for(int k=0;k<=Q;k++)
					dp[i][j][k]=-1;
		return dfs(1,0,Q);
	}
	void solve(){
		double l=0,r=1,ans=-1;
		for(int _=1;_<=50;_++){
			double mid=(l+r)/2;
			double res=calc(mid);
			if(res>T+eps){ans=r=mid;}
			else l=mid;
		}
		if(ans==-1)puts("Impossible.");
		else printf("%.6lf\n",ans);
	}
}p60;
int pos[30][10],len;
struct P100{
	struct Matrix{
		double a[55][55];
		void clear(){
			for(int i=1;i<=len;i++)
				for(int j=1;j<=len;j++)
					a[i][j]=0;
		}
		Matrix operator *(const Matrix res){
			Matrix ans;ans.clear();
			for(int i=1;i<=len;i++)
				for(int j=1;j<=len;j++)
					for(int k=1;k<=len;k++){
						if(a[i][k]<eps)continue;
						ans.a[i][j]+=a[i][k]*res.a[k][j];
					}
			return ans;
		}
	};
	Matrix qkpow(Matrix a,int b){
		Matrix res;res.clear();
		for(int i=1;i<=len;i++)
			res.a[i][i]=1;
		while(b){
			if(b&1)res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	double calc(double p){
		Matrix s,tmp,res;
		s.clear();tmp.clear();res.clear();
		s.a[len][1]=1;
		for(int k=1;k<=Q;k++){
			int ed=min(R,k-1);
			if(k==Q)ed=R;
			for(int j=0;j<=ed;j++){
				tmp.a[pos[j][k]][pos[min(R,j+1)][min(Q,k+1)]]+=p;
				tmp.a[pos[j][k]][len]+=p*min(R,j+1);
				if(k!=1)tmp.a[pos[j][k]][pos[0][k-1]]+=1-p;
			}
		}
		tmp.a[len][len]=1;
		res=qkpow(tmp,n)*s;
		return res.a[pos[0][Q]][1];
	}
	void solve(){
		len=0;
		for(int i=1;i<=Q;i++){
			int ed=min(R,i-1);
			if(i==Q)ed=R;
			for(int j=0;j<=ed;j++)
				pos[j][i]=++len;
		}
		len++;
		double l=0,r=1,ans=-1;
		for(int _=1;_<=50;_++){
			double mid=(l+r)/2;
			double res=calc(mid);
			if(res>T+eps){ans=r=mid;}
			else l=mid;
		}
		if(ans==-1)puts("Impossible.");
		else printf("%.6lf\n",ans);
	}
}p100;
bool mm2;
int main(){
	scanf("%d%d%d%d",&n,&R,&Q,&T);
	p100.solve();
	return 0;
}
