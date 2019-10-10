#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n,m;
struct node{
	int a,b,c;
}A[M];
struct P20{
	int wk[M],wcnt;
	int cnt[45];
	void Print(int x){
		for(int i=0;i<m;i++)
			if(x&1<<i)putchar('1');
			else putchar('0');
		puts("");
	}
	void solve(){
		wcnt=0;
		for(int i=0;i<m;i++)
			wk[++wcnt]=A[i].a,wk[++wcnt]=A[i].b;
		sort(wk+1,wk+wcnt+1);
		wcnt=unique(wk+1,wk+wcnt+1)-wk-1;
		for(int i=0;i<m;i++){
			A[i].a=lower_bound(wk+1,wk+wcnt+1,A[i].a)-wk;
			A[i].b=lower_bound(wk+1,wk+wcnt+1,A[i].b)-wk;
		}
		for(int i=0;i<1<<m;i++){
			memset(cnt,0,sizeof(cnt));
			for(int j=0;j<m;j++){
				if(i&1<<j){
					cnt[A[j].b]+=A[j].c;
					cnt[A[j].a]-=A[j].c;
				}
				else {
					cnt[A[j].a]+=A[j].c;
					cnt[A[j].b]-=A[j].c;
				}
			}
			bool fl=1;
			for(int j=1;j<=wcnt;j++){
				if(abs(cnt[j])>1){
					fl=0;
					break;
				}
			}
			if(fl){Print(i);return;}
		}
		puts("-1");
	}
}p20;
struct P50{
	int cnt[M],ans[M];
	void solve(){
		for(int i=0;i<m;i++){
			int a=A[i].a,b=A[i].b,c=A[i].c;
			int t1=abs(cnt[a]+c)+abs(cnt[b]-c);
			int t2=abs(cnt[a]-c)+abs(cnt[b]+c);
			if(t1>t2){
				cnt[a]-=c;
				cnt[b]+=c;
				ans[i]=1;
			}
			else if(t1<t2){
				cnt[a]+=c;
				cnt[b]-=c;
				ans[i]=0;
			}
			else {
				if(rand()%2){
					cnt[a]-=c;
					cnt[b]+=c;
					ans[i]=1;
				}
				else {
					cnt[a]+=c;
					cnt[b]-=c;
					ans[i]=0;
				}
			}
		}
		bool fl=1;
		for(int i=1;i<=n;i++)
			if(abs(cnt[i])>1)fl=0;
		if(!fl)puts("-1");
		else {
			for(int i=0;i<m;i++)
				printf("%d",ans[i]);
			puts("");
		}
	}
}p50;
int main(){
	freopen("eugene.in","r",stdin);
	freopen("eugene.out","w",stdout);
	srand(19260817);
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&A[i].a,&A[i].b,&A[i].c);
		A[i].a++;A[i].b++;
	}
	if(m<=20)p20.solve();
	else p50.solve();
	return 0;
}
