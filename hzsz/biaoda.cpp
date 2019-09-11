#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <iomanip>
#define INF 99999999;
typedef long long LL;
using namespace std;
 
const int MAX=200000+10;
int *rank,r[MAX],sa[MAX],height[MAX],size;
int wa[MAX],wb[MAX],wm[MAX],len[110],pos[MAX];
bool mark[110];
char s[MAX];
 
bool cmp(int *r,int a,int b,int l){
	return r[a] == r[b] && r[a+l] == r[b+l];
}
 
void makesa(int *r,int *sa,int n,int m){
	int *x=wa,*y=wb,*t;
	for(int i=0;i<m;++i)wm[i]=0;
	for(int i=0;i<n;++i)wm[x[i]=r[i]]++;
	for(int i=1;i<m;++i)wm[i]+=wm[i-1];
	for(int i=n-1;i>=0;--i)sa[--wm[x[i]]]=i;
	for(int i=0,j=1,p=0;p<n;j=j*2,m=p){
		for(p=0,i=n-j;i<n;++i)y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<m;++i)wm[i]=0;
		for(i=0;i<n;++i)wm[x[y[i]]]++;
		for(i=1;i<m;++i)wm[i]+=wm[i-1];
		for(i=n-1;i>=0;--i)sa[--wm[x[y[i]]]]=y[i];
		for(t=x,x=y,y=t,i=p=1,x[sa[0]]=0;i<n;++i){
			x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
		}
	}
	rank=x;
}
 
void calheight(int *r,int *sa,int n){
	for(int i=0,j=0,k=0;i<n;height[rank[i++]]=k){
		for(k?--k:0,j=sa[rank[i]-1];r[i+k] == r[j+k];++k);
	}
}
 
bool check(int mid,int n,int k){
	memset(mark,false,sizeof mark);	
	int num=0,ans=0;
	for(int i=1;i<=n;++i){
		if(height[i]>=mid){
			for(int j=1;j<=size;++j){//判断sa[i]和sa[i-1]所属的字符串是否已被计算过 
				if(sa[i]>len[j-1] && sa[i]<len[j])ans+=(mark[j]?0:1),mark[j]=true;
				if(sa[i-1]>len[j-1] && sa[i-1]<len[j])ans+=(mark[j]?0:1),mark[j]=true;
			}
		}else{
			if(ans>k/2)pos[++num]=sa[i-1];//pos记录满足条件的子串首位置 
			ans=0;
			memset(mark,false,sizeof mark);
		}
	}
	if(ans>k/2)pos[++num]=sa[n];
	if(num){pos[0]=num;return true;} 
	return false;
}
 
int main(){
	int k,n,num=0;
	len[0]=-1;//注意len[0]初始化<0 
	while(cin>>k,k){
		pos[0]=size=n=0;//注意初始化 
		for(int i=0;i<k;++i){
			scanf("%s",s+n);
			for(;s[n] != '\0';++n)r[n]=s[n];
			r[len[++size]=n++]=300+i;//300+i保证每个分隔的字符不同 
		}
		r[n-1]=0;
		makesa(r,sa,n,400);
		calheight(r,sa,n-1);
		int L=1,R=n,mid;
		while(L<=R){
			mid=L+R>>1;
			if(check(mid,n,k))L=mid+1;
			else R=mid-1;
		}
		if(num++)printf("\n");
		if(L-1 == 0)printf("?\n");
		else{
			for(int i=1;i<=pos[0];++i){
				for(int j=pos[i];j<pos[i]+L-1;++j)printf("%c",s[j]);
				printf("\n");
			}
		}
	}
	return 0;
}
