#include<bits/stdc++.h>
#define LL long long
#define M 1000005
using namespace std;
int n,q;
struct node{ int l,r,h,op; };
node S[M],tmp[M];
node stk[M];
int topS,topt,top;
void Add(int x){
    topt=0;
    for(int i=1;i<=topS;i++){
        node e=S[i];
        if(e.op==0){
            if(e.h+x>e.l){
                int tr=min(e.h+x,e.r);
                tmp[++topt]=(node){e.l,tr,e.l,1};
                int tl=tr+1;
                if(tl<=e.r)
                    tmp[++topt]=(node){tl,e.r,e.h+x,0};
            }
            else
                tmp[++topt]=(node){e.l,e.r,e.h+x,0};
        }
        else {
            int to=min(e.h+x,e.l);
            tmp[++topt]=(node){e.l,e.r,to,1};
        }
    }
    topS=topt;
    for(int i=1;i<=topS;i++)
        S[i]=tmp[i];
}
void Del(int x){
    topt=0;
    for(int i=1;i<=topS;i++){
        node e=S[i];
        if(e.op==0){
            int to=max(0,e.h+x);
            tmp[++topt]=(node){e.l,e.r,to,0};
        }
        else {
            if(e.h+x<=0){
                int tr=min(e.l-(e.h+x),e.r);
                tmp[++topt]=(node){e.l,tr,0,0};
                int tl=tr+1;
                if(tl<=e.r)
                    tmp[++topt]=(node){tl,e.r,1,1};
            }
            else tmp[++topt]=(node){e.l,e.r,e.h+x,1};
        }
    }
    topS=topt;
    for(int i=1;i<=topS;i++)
        S[i]=tmp[i];
}
bool check(node a,node b){
    if(a.op!=b.op)return 0;
    if(a.op==1){
        if(a.h+a.r-a.l+1==b.h)return 1;
        return 0;
    }
    else
        return a.h==b.h;
}
node merge(node a,node b){
    if(a.op==0)return (node){a.l,b.r,a.h,0};
    return (node){a.l,b.r,a.h,1};
}
void qc(){
    top=0;
    for(int i=1;i<=topS;i++){
        bool fl=0;
        if(top&&check(stk[top],S[i])){
            stk[top]=merge(stk[top],S[i]);
            fl=1;
        }
        if(!fl)stk[++top]=S[i];
    }
    topS=top;
    for(int i=1;i<=topS;i++)
        S[i]=stk[i];
}
int main(){
    scanf("%d%d",&n,&q);
    S[++topS]=(node){1,n,0,0};
    for(int i=1,x;i<=q;i++){
        scanf("%d",&x);
        if(x>=0)Add(x);
        else Del(x);
        qc();
        LL ans=0;
        for(int j=1;j<=topS;j++){
            node e=S[j];
            if(e.op==0)ans=ans+1LL*(e.r-e.l+1)*e.h;
            else ans=ans+1LL*(e.h+e.h+e.r-e.l)*(e.r-e.l+1)/2;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
