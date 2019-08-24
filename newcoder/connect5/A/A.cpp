#include<bits/stdc++.h>
#define M 10000005
#define LL long long
using namespace std;
int n,d;
void read(int &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}
int main(){
	read(n);read(d);
	LL ans=0;
	for(register int i=1,x,las;i<=n;i++){
		read(x);
		if(i==1){las=x;continue;}
		LL t1=abs(x%d-las);
		LL t2=abs(x%d+d-las);
		ans+=min(t1,t2);
		x%=d;
		las=x;
	}
	printf("%lld\n",ans);
	return 0;
}
