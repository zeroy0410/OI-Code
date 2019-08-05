#include<cstdio>
#include<iostream>
#include<string.h> 
#define LL long long
#define M 1000005 
using namespace std;
const int mod=19940417;
void exgcd(LL a,LL b,LL &x,LL &y){if(!b){x=1,y=0;return;}exgcd(b,a%b,y,x);y-=a/b*x;}
LL inv(LL a){
	LL x,y;
	exgcd(a,mod,x,y);
	return x;
}
LL fac[3][mod+5];
void Init(LL P,int f){
	fac[f][0]=1;
	for(int i=1;i<=P;i++)
		fac[f][i]=[f]fac[i-1]*i%P;
}
LL C(LL a,LL b,LL P){
	return fac[a]*inv(fac[b])%P*inv(fac[a-b])%P;
}
LL lucas(LL a,LL b,LL P){
	if(a<P&&b<P)return C(a,b,P);
	return C(a%P,b%P,P)*lucas(a/P,b/P,P);
}
void CRT_merge(int 
struct node{
	int x,y;
	bool operator < (const node& res)const{
		return x<res.x;
	}
	bool operator == (const node& res)const{
		return x==res.x&&y==res.y;
	}
}A[M];
int n,K;
int main(){
	Init(mod);
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++){
		
	return 0;
}
