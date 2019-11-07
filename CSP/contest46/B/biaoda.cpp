#include<bits/stdc++.h>
using namespace std;

#define reg register
typedef long long ll;
#define rep(i,a,b) for(reg int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(reg int i=a,i##end=b;i>=i##end;--i)

char IO;
int rd(){
    int s=0,f=0;
    while(!isdigit(IO=getchar())) if(IO=='-') f=1;
    do s=(s<<1)+(s<<3)+(IO^'0');
    while(isdigit(IO=getchar()));
    return f?-s:s;
}

const int N=1e6+10;

bool be;

int lena,lenb,n;
int A[N],B[N];
struct Seg{
    int l,r;
    bool operator < (const Seg __) const {
        return r>__.r;
    }
}S[N];
bool cmp(const Seg x,const Seg y) {
    return x.l<y.l;
}
priority_queue <Seg> que;

int Check(int mid) {
    int p=1;
    while(!que.empty()) que.pop();  // 用优先队列维护贪心
    rep(i,1,lena+lenb) {
        while(p<=n && S[p].l<=i) que.push(S[p++]); // 将l<=i的区间塞进来
        for(reg int j=1;j<=mid && !que.empty();++j) { // 每次弹掉r最小的mid个
            if(que.top().r<i) return false;
            que.pop();
        }
    }
    return que.empty();
}


bool ed;


int main(){
//    printf("%.2lf\n",(&ed-&be)/1024.0/1024.0);
    lena=rd(),lenb=rd(),n=rd();
    rep(i,1,lena) A[i]=rd(); sort(A+1,A+lena+1);
    rep(i,1,lenb) B[i]=rd(); sort(B+1,B+lenb+1);
    rep(i,1,n) {
        int a=rd(),b=rd();
        a=upper_bound(A+1,A+lena+1,a)-A;
        b=upper_bound(B+1,B+lenb+1,b)-B;
        if(a>lena&&b>lenb) return puts("-1"),0;
        S[i].l=a,S[i].r=lena+lenb-b+1;
		S[i].l<<' '<<S[i].r<<endl;
    }
    sort(S+1,S+n+1,cmp);//将处理完的区间排好序
    int l=1,r=n,res=-1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(Check(mid)) r=mid-1,res=mid; //二分答案
        else l=mid+1;
    }
    printf("%d\n",res);
    return 0;
}
