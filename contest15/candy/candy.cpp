#include<bits/stdc++.h>
#define N 2005
#define M 1000005
using namespace std;
int n,len,len2,len4;
int C[2][N][N<<1],x[M],y[M];
void Add(int x,int y,int d,int f){
	x++;y++;
	for(;x<=len2;x+=(x&-x))	
		for(int j=y;j<=len4;j+=(j&-j))
			C[f][x][j]+=d;
}
int Sum(int x,int y,int f){
	x++;y++;int res=0;if(x<=0||y<=0)return 0;
	if(x>len2)x=len2;if(y>len4)y=len4;
	for(;x;x-=(x&-x))
		for(int j=y;j;j-=(j&-j))
			res+=C[f][x][j];
	return res;
}
int calc(int x1,int y1,int x2,int y2,int f){return Sum(x2,y2,f)-Sum(x2,y1-1,f)-Sum(x1-1,y2,f)+Sum(x1-1,y1-1,f);}
int main(){
	freopen("candy.in","r",stdin); 
	freopen("candy.out","w",stdout);
	scanf("%d%d",&n,&len);
	len2=len*2;len4=len2*2;
	while(n--){
		int op,t,c,l,r,d;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d%d%d",&t,&c,&l,&r,&d);
			x[c]=((t-l*d)%len2+len2)%len2;
			y[c]=r-l;
			Add(x[c],x[c]+y[c],1,0);
			Add(x[c],-x[c]+y[c]+len2,1,1);
		} else if(op==3){
			scanf("%d%d",&t,&c);
			Add(x[c],x[c]+y[c],-1,0);
			Add(x[c],-x[c]+y[c]+len2,-1,1);
		} else {
			scanf("%d%d%d",&t,&l,&r);t%=len2;int res=0,flag=(r==len);
            res+=calc(t,l+t,t+r,len4,0);
            res+=calc(0,l+t-len2,t+r-len2-flag,len4,0);
            res+=calc(t-r+len2+flag,l-t,len2,len4,1);
            res+=calc(t-r,l-t+len2,t-1,len4,1);
			printf("%d\n",res);
		}
	}
	return 0;
}
