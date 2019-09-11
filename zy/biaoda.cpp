#include<bits/stdc++.h>
using namespace std;
const int M=3005;
int pr[M],ct;
bool mark[M],No[M];
void init(){
	for(int i=2;i<=M-5;i++){
		if(mark[i])continue;
		pr[++ct]=i;
		for(int j=i+i;j<=M-5;j+=i)
			mark[j]=1;
	}
	for(int i=2;i*i<=M-5;i++)
		for(int j=i*i;j<=M-5;j+=i*i)
			No[j]=1;
}
bool num[M],Mark[M];
struct node{
	int mp,sp;
	bool operator <(const node &_)const{
		return mp<_.mp;
	}
}a[M];
int p[20];
int dp[1<<16],res[1<<16];
int main(){
	init();
	int T;
	scanf("%d",&T);
	while(T--){
		int n,P;
		scanf("%d%d",&n,&P);
		memset(num,false,sizeof(num));
		for(int i=2;i<=n;i++){
			int x=i;
			for(int j=1;j<=ct&&pr[j]<=n;j++)
				while(x%pr[j]==0)num[j]^=1,x/=pr[j];
		}
		memset(Mark,0,sizeof(Mark));
		for(int i=1;i<=ct&&pr[i]<=n;i++){
			if(num[i])continue;
			for(int j=pr[i];j<=n;j+=pr[i])Mark[j]=1;
		}
		//No表示永远也用不到的数（含有两个及以上相同的质因子）
		//Mark表示该次用不到的数（含有总和为偶数的质因子） 
		//重新将有用的小质数标号
		int sl=0;
		for(int i=1;pr[i]*pr[i]<=n;i++)
			if(num[i])p[sl++]=pr[i];
		//for(int i=0;i<sl;i++)printf("%d ",p[i]);puts("");
		//将所有剩下的数按照大质数分类，并记下所有小质数的状态（寿司晚宴） 
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(No[i]||Mark[i])continue;
			cnt++;
			//printf("%d ",i);
			int x=i;
			a[cnt].sp=0;
			for(int j=0;j<sl;j++)
				if(x%p[j]==0)x/=p[j],a[cnt].sp|=1<<j;
			//printf("%d\n",x);
			a[cnt].mp=x;
		}//puts("!");
		sort(a+1,a+1+cnt);
		for(int i=1;i<=cnt;i++)
			printf("%d %d\n",a[i].sp,a[i].mp);
		//printf("%d\n",cnt);
		//for(int i=1;i<=cnt;i++)printf("%d %d\n",a[i].mp,a[i].sp);
		memset(dp,0,sizeof(dp));
		dp[0]=1;
		for(int i=1;i<=cnt;i++){
			for(int j=(1<<sl)-1;j>=0;j--){
				if((j&a[i].sp)==0){
					if(a[i].mp==1)(dp[j|a[i].sp]+=dp[j])%=P;
					else (dp[j|a[i].sp]+=res[j])%=P;
				}
				printf("%d\n",dp[j]);
			}
			//	for(int j=0;j<(1<<sl);j++)printf("%d ",dp[j]);puts("");
			if(i!=cnt&&a[i].mp!=a[i+1].mp){
				for(int j=0;j<(1<<sl);j++)
					res[j]=dp[j],dp[j]=0;
			}
		}
		printf("%d\n",dp[(1<<sl)-1]);
	}
	return 0;
}
