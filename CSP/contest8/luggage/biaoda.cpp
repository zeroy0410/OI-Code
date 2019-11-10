#include<bits/stdc++.h>
using namespace std;
#define M 100005
struct hh{
    int a,b,c,d,p;
    bool operator<(hh x)const{
        return a<x.a;
    }
}sk[M];
int mx[M<<3],yc[M<<3],a[M<<1],ans[M];
void down(int p){
    if(yc[p]){
        yc[p<<1]=max(yc[p<<1],yc[p]),mx[p<<1]=max(mx[p<<1],yc[p]);
        yc[p<<1|1]=max(yc[p<<1|1],yc[p]),mx[p<<1|1]=max(mx[p<<1|1],yc[p]);
        yc[p]=0;
    }
}
void update(int p,int l,int r,int L,int R,int w){
    if(l==L&&r==R){
        mx[p]=max(mx[p],w);
        yc[p]=max(yc[p],w);
        return;
    }
    down(p);
    int mid=(l+r)>>1;
    if(R<=mid)update(p<<1,l,mid,L,R,w);
    else if(L>mid)update(p<<1|1,mid+1,r,L,R,w);
    else update(p<<1,l,mid,L,mid,w),update(p<<1|1,mid+1,r,mid+1,R,w);
    mx[p]=max(mx[p<<1|1],mx[p<<1]);
}
int query(int p,int l,int r,int L,int R){
    if(l==L&&r==R)return mx[p];
    down(p);
    int mid=(l+r)>>1;
    if(R<=mid)return query(p<<1,l,mid,L,R);
    else if(L>mid)return query(p<<1|1,mid+1,r,L,R);
    else return max(query(p<<1,l,mid,L,mid),query(p<<1|1,mid+1,r,mid+1,R));
}
int main(){
    int n,t,k;
    scanf("%d%d%d",&n,&t,&k);
    for(int i=1;i<=n;++i)scanf("%d%d%d%d",&sk[i].a,&sk[i].b,&sk[i].c,&sk[i].d),sk[i].d--,sk[i].p=i,a[i*2]=sk[i].b,a[i*2-1]=sk[i].d;
    sort(a+1,a+2*n+1);int cnt=unique(a+1,a+2*n+1)-a-1;
    for(int i=1;i<=n;++i)sk[i].b=lower_bound(a+1,a+cnt+1,sk[i].b)-a,sk[i].d=lower_bound(a+1,a+cnt+1,sk[i].d)-a;
    memset(mx,-1,sizeof(mx));
    sort(sk+1,sk+n+1);
    for(int i=1;i<=n;++i)
        if(sk[i].p==t){
            update(1,1,cnt,sk[i].b,sk[i].d,sk[i].c-sk[i].a);
            sk[i].a+=k;
            for(int j=i+1;j<=n;++j){
                int w=query(1,1,cnt,sk[j].b,sk[j].d);
				cout<<w<<endl;
                if(w!=-1&&w+sk[i].a>sk[j].a){
                    update(1,1,cnt,sk[j].b,sk[j].d,w+sk[j].c-sk[j].a);
                    sk[j].a=w+sk[i].a;
                }
            }
            break;
        }
    for(int i=1;i<=n;++i)ans[sk[i].p]=sk[i].a;
    for(int i=1;i<=n;++i){
        if(i!=1)putchar(' ');
        printf("%d",ans[i]);
    }
}
