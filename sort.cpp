#include<bits/stdc++.h>
using namespace std;
const int M=1005;
int a[M],n;
namespace Counting{
	int cnt[M],b[M];
	void sort(){
		for(int i=1;i<=n;i++)cnt[a[i]]++;
		for(int i=1;i<=M-5;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)b[cnt[a[i]]--]=a[i];
		for(int i=1;i<=n;i++)printf("%d ",b[i]);
	}
}
namespace Radix{
	static const int P=65535;
	int cnt[P+1],b[M];
	void sort(){
		for(int i=1;i<=n;i++)cnt[a[i]&P]++;
		for(int i=1;i<=P;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)b[cnt[a[i]&P]--]=a[i];
		for(int i=0;i<=P;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[b[i]>>16]++;
		for(int i=1;i<=P;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)a[cnt[b[i]>>16]--]=b[i];
		for(int i=1;i<=n;i++)printf("%d ",a[i]);
	}
}
namespace Selection{
	void sort(){
		for(int i=1;i<=n;i++){
			int id=i;
			for(int j=i+1;j<=n;j++)
				if(a[id]>a[j])id=j;
			if(id!=i)swap(a[id],a[i]);
		}
		for(int i=1;i<=n;i++)printf("%d ",a[i]);
	}
}
namespace Insert{
	int b[M];
	void sort(){
		for(int j,i=1;i<=n;i++){
			for(j=1;j<i;j++)if(a[i]<b[j])break;
			for(int k=i;k>=j+1;k--)b[k]=b[k-1];
			b[j]=a[i];
		}	
		for(int i=1;i<=n;i++)printf("%d ",b[i]);
	}
}
namespace Merge{
	int b[M],c[M];
	void solve(int l,int r){
		if(l==r){b[l]=a[l];return;}
		int mid=(l+r)>>1;
		solve(l,mid),solve(mid+1,r);
		int i1=l,i2=mid+1,i3=0;
		while(i1<=mid&&i2<=r){
			if(b[i1]<b[i2])c[++i3]=b[i1++];
			else c[++i3]=b[i2++];
		}
		while(i1<=mid)c[++i3]=b[i1++];
		while(i2<=r)c[++i3]=b[i2++];
		for(int i=l;i<=r;i++)b[i]=c[i-l+1];
	}
	void sort(){
		solve(1,n);
		for(int i=1;i<=n;i++)printf("%d ",b[i]);
	}
}
namespace Heap{
	int sz;
	void down(int p){
		for(int j;(j=p<<1)<=sz;p=j){
			if(j<sz&&a[j|1]<a[j])j|=1;
			if(a[j]<a[p])swap(a[j],a[p]);
			else break;
		}
		puts("");
	}
	void sort(){
		sz=n;
		for(int i=1;i<=n/2;i++)down(i);
		for(int i=1;i<=n;i++){
			printf("%d ",a[1]);
			a[1]=a[sz--];
			down(1);
		}
	}
}
namespace Fast{
	void solve(int l,int r){
		int x=a[l],i=l,j=r;
		while(i<j){
			while(i<j&&a[i]<=x)i++;
			while(i<j&&a[j]>=x)j--;
			if(i<j)swap(a[i],a[j]);
		}
		if(l<=i-1)solve(l,i-1);
		if(i+1<=r)solve(i+1,r);
	}
	void sort(){
		solve(1,n);
		for(int i=1;i<=n;i++)printf("%d ",a[i]);
	}

}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	Heap::sort();
	return 0;
}
