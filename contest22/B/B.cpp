#include<bits/stdc++.h>
#define M 50005
#define LL long long 
using namespace std;
int n;
struct node{int h,v,id;}A[M],tmp[M],tmpp[M];
bool cmp1(node a,node b){return a.h>b.h;}
bool cmp2(node a,node b){return a.h<b.h;}
struct Node{
    int x;
    double y;
}dp[2][M];
int B[M<<1],bcnt;
Node max(Node a,Node b){
    if(b.x>a.x)swap(a,b);
    if(a.x>b.x)return (Node){a.x,a.y};
    else if(a.x==b.x)return (Node){a.x,a.y+b.y};
}
struct BIT{
    Node C[M<<1];
    BIT(){
        for(int i=0;i<=2*n;i++)
            C[i]=(Node){0,0};
    }
    void add(int x,Node d,bool f){
        x++;
        if(f){
            while(x<=n*2+1){
                C[x]=max(C[x],d);
                x+=(x&-x);
            }
        }
        else {
            while(x){
                C[x]=max(C[x],d);
                x-=(x&-x);
            }
        }
    }
    Node sum(int x,bool f){
        Node res=(Node){0,0};x++;
        if(f){
            while(x){
                res=max(res,C[x]);
                x-=(x&-x);
            }
        }
        else {
            while(x<=2*n+1){
                res=max(res,C[x]);
                x+=(x&-x);
            }
        }
        return res;
    }
    void clear(int x,bool f){
        x++;
        if(f){
            while(x<=n*2+1){
                C[x]=(Node){0,0};
                x+=(x&-x);
            }
        }
        else {
            while(x){
                C[x]=(Node){0,0};
                x-=(x&-x);
            }
        }
    }
}T;
void CDQ(int l,int r,bool f){
    if(l==r)return;
    int mid=(l+r)>>1;
    CDQ(l,mid,f);
    for(int i=mid+1;i<=r;i++)tmpp[i]=A[i];
    if(f==0){
        sort(A+l,A+mid+1,cmp1);
        sort(A+mid+1,A+r+1,cmp1);
    }
    else {
        sort(A+l,A+mid+1,cmp2);
        sort(A+mid+1,A+r+1,cmp2);
    }
    int i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if((f==0&&A[i].h>=A[j].h)||(f==1&&A[i].h<=A[j].h)){
            T.add(A[i].v,dp[f][A[i].id],f);i++;
        }
        else {
            Node tmp=T.sum(A[j].v,f);tmp=(Node){tmp.x+1,tmp.y};
            // cout<<tmp.y<<endl;
            dp[f][A[j].id]=max(dp[f][A[j].id],tmp),j++;
        }
    }
    for(;j<=r;j++){
        Node tmp=T.sum(A[j].v,f);tmp=(Node){tmp.x+1,tmp.y};
        dp[f][A[j].id]=max(dp[f][A[j].id],tmp);
    }
    for(int i=l;i<=mid;i++)T.clear(A[i].v,f);
    for(int i=mid+1;i<=r;i++)A[i]=tmpp[i];
    CDQ(mid+1,r,f);
}
double ret[M<<1];
int main(){
    freopen("missile.in","r",stdin);
    freopen("missile.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&A[i].h,&A[i].v);A[i].id=i;
        B[++bcnt]=A[i].h;B[++bcnt]=A[i].v;
    }
    sort(B+1,B+bcnt+1);
    bcnt=unique(B+1,B+bcnt+1)-B-1;
    for(int i=1;i<=n;i++){
        A[i].h=lower_bound(B+1,B+bcnt+1,A[i].h)-B;
        A[i].v=lower_bound(B+1,B+bcnt+1,A[i].v)-B;
    }
    for(int i=1;i<=n;i++){
        dp[0][i].x=dp[1][i].x=0;
        dp[0][i].y=0;dp[0][i].y=0;
    }
    A[0].id=0;dp[0][0].x=dp[1][0].x=0;dp[0][0].y=dp[1][0].y=1.0;
    A[0].h=2*n;A[0].v=2*n;
    for(int i=1;i<=n;i++)tmp[i]=A[i];
    CDQ(0,n,0);
    A[0].h=0;A[0].v=0;
    for(int i=1;i<=n;i++)A[i]=tmp[n-i+1];
    CDQ(0,n,1);
    int ans=0;double c=0;
    for(int i=1;i<=n;i++){
        if(dp[0][i].x>ans){
            ans=dp[0][i].x;
            c=dp[0][i].y;
        }
        else if(dp[0][i].x==ans)
            c+=dp[0][i].y;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(dp[0][i].x+dp[1][i].x-1!=ans)
            printf("0.00000 ");
        else {
            printf("%.6Lf ",(long double)dp[0][i].y*dp[1][i].y/c);
        }
    }
    puts("");
    return 0;
}