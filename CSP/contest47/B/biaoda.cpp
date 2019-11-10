#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int kN=1e6+1;
int q,top;
ll n,h[kN],w[kN],s;
ll calc(const ll h,const ll w){
    return h*(h+1LL)/2LL+(n-w)*h;
}
int main(){
    cin>>n>>q;
    while(q--){
        ll a;
        scanf("%lld",&a);
        if(a>0LL){
            ll p=a;
            for(;top>0&&p+h[top]>=w[top];--top){
                s-=calc(h[top],w[top]);
                p+=h[top];
            }
            ++top;
            h[top]=w[top]=min(p,n);
            s+=calc(h[top],w[top]);
        }
        else{
            ll p=a;
            for(;top>0&&p+h[top]<=0LL;--top){
                s-=calc(h[top],w[top]);
                p+=h[top];
            }
            if(top>0){
                s-=calc(h[top],w[top]);
                h[top]+=p;
                s+=calc(h[top],w[top]);
            }
        }
        printf("%lld\n",s);
    }
}
