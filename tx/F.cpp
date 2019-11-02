#include<bits/stdc++.h>
using namespace std;
const int N=200010;
unsigned long long ans;
bool del[N];
struct data{
    int id,key,l,r;
    bool operator <(const data&rhs)const{
       return key>rhs.key;
    }
}w[N];
priority_queue<data> Q;
int a[N],n,k;
int main(){
    while(~scanf("%d%d",&n,&k)){
        ans=0;
        memset(del,0,sizeof(del));
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=1;i<n;i++){
            w[i].id=i;
            w[i].key=a[i+1]-a[i];
            w[i].l=i-1;
            w[i].r=i+1;
            Q.push(w[i]);
        }n--;
        w[n].r=w[0].l=w[0].r=0;
        w[0].key=0x3f3f3f3f;
        while(k--){
            for(;;){
                data t=Q.top();
                Q.pop();
                int id=t.id,l=w[id].l,r=w[id].r;
                if(del[id])continue;
                del[id]=del[l]=del[r]=1;
                ans+=w[id].key;
                w[++n].id=n;
                w[n].key=w[l].key+w[r].key-w[id].key;
                w[n].l=w[l].l; w[n].r=w[r].r;
                w[w[l].l].r=n; w[w[r].r].l=n;
                Q.push(w[n]);
                break;
            }
        }printf("%lld\n",ans);
    }return 0;
}
