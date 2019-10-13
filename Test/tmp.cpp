#include<bits/stdc++.h>
#define LL long long
using namespace std;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(!b){d=a;x=1;y=0;return;}
    exgcd(b,a%b,d,y,x);y-=a/b*x;
}
LL n,p,a,b;
int main(){
	cin>>n>>p>>a>>b;
	LL x,y,g;
	exgcd(a,b,g,x,y);
	if(p%g!=0)puts("-1");
	else {
		LL t1=b/g,t2=a/g;
		LL t=(p/g)%t2;y*=t;
		if(y>0){
			LL k=y/t2;
			while(y-t2*k<0)k--;
			while(y-t2*(k+1)>=0)k++;
			y-=k*t2;
			x=(p-y*b)/a;
			if(x<0)puts("-1");
			else {
				if(x+y<=n)printf("%lld %lld %lld\n",x,y,n-x-y);
				else puts("-1");
			}
		}
		else {
			LL k=(-y)/t2;
			while(y+t2*k<0)k++;
			while(y+t2*(k-1)>=0)k--;
			y+=k*t2;
			x=(p-y*b)/a;
			if(x<0)puts("-1");
			else {
				if(x+y<=n)printf("%lld %lld %lld\n",x,y,n-x-y);
				else puts("-1");
			}
		}
	}
	return 0;
}
