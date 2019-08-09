#include<cstdio>
#include<cmath>
#define FOR(i,l,r) for(int i=(l),i##R=(r);i<=i##R;i++)
const int N=55;
int n;
int stk[N][N],top[N],num,ct;
bool check(int x,int y){
	int sum=x+y,p=sqrt(sum);
	return p*p==sum;
}
int main(){
	scanf("%d",&n);
	while(1){
		ct++;
		int ok=0;
		FOR(i,1,num)
			if(check(stk[i][top[i]],ct)){stk[i][++top[i]]=ct;ok=1;break;}
		if(!ok){
			if(num<n)num++,stk[num][top[num]=1]=ct;
			else break;
		}
	}
	printf("%d\n",ct-1);
	FOR(i,1,num)FOR(j,1,top[i])printf("%d%c",stk[i][j],j==top[i]?'\n':' ');
	return 0;
}