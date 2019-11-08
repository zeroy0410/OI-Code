#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
#define M 100005
using namespace std;
int n,c[M];
long long ans;
struct hzl {
    int h,k;
} A[M];
bool cmp(hzl a,hzl b) {
    return a.h<b.h;
}
void Add(int x,int d) {
    while(x<=100000) {
        c[x]+=d;
        x+=lowbit(x);
    }
    return ;
}
int sum(int x) {
    int s=0;
    while(x) {
        s+=c[x];
        x-=lowbit(x);
    }
    return s;
}
int main() {
//  freopen("2.in","r",stdin);
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d%d",&A[i].h,&A[i].k);
    sort(A+1,A+n+1,cmp);
    for(int i=1; i<=n; i++) {
        int now=sum(A[i].h-A[i].k+1);
        int l=1,r=A[i].h,s1=1,s2=A[i].h;
        while(l<=r) {
            int mid=l+r>>1;
            if(sum(mid)<=now) {
                s1=mid;
                r=mid-1;
            } else l=mid+1;
        }
        l=1,r=A[i].h;
        while(l<=r) {
            int mid=l+r>>1;
            if(sum(mid)>=now) {
                s2=mid;
                l=mid+1;
            } else r=mid-1;
        }
        Add(s2+1,1);
        Add(A[i].h+1,-1);
        A[i].k-=A[i].h-s2;
        Add(s1,1);
        Add(s1+A[i].k,-1);
    }
    for(int i=1; i<=A[n].h; i++) {
        int now=sum(i);
        ans+=1LL*now*(now-1)/2;
    }
    printf("%lld\n",ans);
    return 0;
}
