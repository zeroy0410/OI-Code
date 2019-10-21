#include<bits/stdc++.h>
using namespace std;
int n,m,K;
struct P10{
	int mark;
	void solve(){
		for(int i=1,x;i<=m;i++){
			scanf("%d",&x);
			mark|=1<<x;
		}
		for(int i=1;i<1<<n;i++){
			if(mark&1<<i){
				for(int j=1;j<i;j++)
					if(mark&1<<j)
						mark|=(1<<(i|j));
			}
		}
		for(int i=1;i<1<<(1<<n);i++){
			int ct=0;
			for(int j=1;j<1<<n;j++)
				if(i&1<<j)ct++;
			if(ct==K){
				bool fl=0;
				for(int j=1;j<1<<n;j++){
					if(!(i&1<<j))continue;
					for(int k=1;k<1<<n;k++){
						if(!(i&1<<k))continue;
						if(!(i&1<<(j|k))){fl=1;break;}
					}
					if(fl)break;
				}
				if(fl)continue;
				if((i&mark)==mark){
					for(int j=1;j<1<<n;j++){
						if(i&1<<j)printf("1");
						else printf("0");
					}
					return;
				}
			}
		}
		puts("-1");
	}
}p10;
struct Pm0{
	bool mark[1<<18];
	int tmp;
	void solve(){
		if(m==1)scanf("%d",&tmp);
		for(int i=0;i<n;i++){
			if(K&1<<i)
				mark[1<<(n-i-1)]=1;
		}
		if(m==1&&!mark[tmp&-tmp]){
			puts("-1");
			return;
		}
		for(int i=1;i<1<<n;i++){
			if(mark[(i&-i)])
				printf("1");
			else printf("0");
		}
		puts("");
	}
}pm0;
struct P100{

}p100;
int main(){
//	freopen("set.in","r",stdin);
//	freopen("set.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	if(n<=4)p10.solve();
	else if(m==0||m==1)pm0.solve();
	else puts("-1");
	return 0;
}
