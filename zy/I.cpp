#include<bits/stdc++.h>
#define M 100005
using namespace std;
int T,n,q,u,K;
int cnt[M][11];
int main(){
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof(cnt));
		scanf("%d",&n);
		for(int i=1,x;i<=n;i++){
			scanf("%d",&x);
			for(int j=1;j<=10;j++)
				cnt[i][j]=cnt[i-1][j]+(x==j);
		}
		scanf("%d",&q);
		while(q--){
			scanf("%d%d",&u,&K);
			int ans=0,L=u,R=u,st=0,ct=0;
			while(1){
				for(int i=1;i<=10;i++)
					if(!(st&(1<<i))&&cnt[R][i]-cnt[L-1][i]>0)
						st|=1<<i,ct++;
				if(ct>=K){printf("%d\n",ans);break;}
				if(R==n){puts("-1");break;}
				ans++;
				L<<=1,R=min(n,R<<1|1);
				if(L>n){puts("-1");break;}	
			}	
		}
	}
	return 0;
}
