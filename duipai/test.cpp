#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int T;
LL X;
struct Pbl{
    LL Q[M];
    int qcnt;
    LL Get(int s,int l){
        LL res=0;
        for(int i=0;i<l;i++){
            if(s&1<<i)res=res*10+4;
            else res=res*10+7;
        }
        return res;
    }
    void build(){
        for(int l=2;l<=10;l+=2){
            for(int i=0;i<1<<l;i++){
                int c=0;
                for(int j=0;j<l;j++){
                    if(i&1<<j)c++;
                }
                if(c!=l/2)continue;
                Q[++qcnt]=Get(i,l);
            }
        }
    }
    void solve(){
        qcnt=0;build();
        sort(Q+1,Q+qcnt+1);
    }
    LL calc(LL x){
        int cur=lower_bound(Q+1,Q+qcnt+1,x)-Q;
        return Q[cur];
    }
}pbl;
struct P100{
    int Q[35],qcnt,len,ans[35],tmp[35];
    bool less(int c7,int c4,int w){
        if(w>qcnt)return 0;
        for(int i=1;i<=c7;i++)tmp[i]=7;
        for(int i=c7+1;i<=c7+c4;i++)tmp[i]=4;
        for(int i=1;i<=c7+c4;i++){
            if(tmp[i]>Q[w+i-1])return 0;
            if(tmp[i]<Q[w+i-1])return 1;
        }
        return 0;
    }
    void solve(LL x){
        qcnt=0;
        while(x){
            Q[++qcnt]=x%10;
            x/=10;
        }
        if(qcnt&1)Q[++qcnt]=0;
        for(int i=1;i<=qcnt/2;i++)
            swap(Q[i],Q[qcnt-i+1]);
        if(less(qcnt/2,qcnt/2,1)){
            len=qcnt+2;
            for(int i=1;i<=len/2;i++)printf("4");
            for(int i=1;i<=len/2;i++)printf("7");
            puts("");
            return;
        }
        int len=qcnt;
        int l4=len/2,l7=len/2;
        bool fl=0;
        for(int i=1;i<=qcnt;i++){
            if(fl){
                if(l4){ans[i]=4;l4--;}
                else ans[i]=7;
                continue;
            }
            if(Q[i]<4){
                if(l4){l4--;ans[i]=4;}
                else {l7--;ans[i]=7;}
                fl=1;
            }
            else if(Q[i]==4){
                if(less(l7,l4-1,i+1)){l7--;ans[i]=7;fl=1;}
                else {l4--;ans[i]=4;}
            }
            else if(Q[i]<7){l7--;ans[i]=7;fl=1;}
            else {l7--;ans[i]=7;}
        }
        for(int i=1;i<=len;i++)
            printf("%d",ans[i]);
        puts("");
    }
}p100;
int main(){
    pbl.solve();
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&X);
        // if(X<=(int)1e8){
        p100.solve(X);
        // }
    }
    return 0;
}