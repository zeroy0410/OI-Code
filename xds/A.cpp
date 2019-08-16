#include<bits/stdc++.h>
#define M 30005
using namespace std;
int n,m,r;
struct Matrix{
    int a[2][2];
    void clear(){memset(a,0,sizeof(a));}
    Matrix operator * (Matrix res){
        Matrix ans;ans.clear();
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    ans.a[i][j]=(ans.a[i][j]+a[i][k]*res.a[k][j])%r;
                }
            }
        }
        return ans;
    }  
}A[M];
struct YD_tree{
    struct YD{
        int l,r;
        Matrix x;
    }tree[M<<2];
    #define fa tree[p]
    #define lson tree[p<<1]
    #define rson tree[p<<1|1]
    void Up(int p){
        fa.x=lson.x*rson.x;
    }
    void build(int l,int r,int p){
        fa.l=l;fa.r=r;
        if(l==r){
            fa.x=A[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
        Up(p);
    }
    Matrix query(int l,int r,int p){
        if(fa.l==l&&fa.r==r)return fa.x;
        int mid=(fa.l+fa.r)>>1;
        if(r<=mid)return query(l,r,p<<1);
        else if(l>mid)return query(l,r,p<<1|1);
        return query(l,mid,p<<1)*query(mid+1,r,p<<1|1);
    }
}Tr;
int main(){
    bool fl=1;
    while(~scanf("%d%d%d",&r,&n,&m)){
        if(!fl)printf("\n");
        fl=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    scanf("%d",&A[i].a[j][k]);
        }
        Tr.build(1,n,1);
        while(m--){
            int l,r;
            scanf("%d%d",&l,&r);
            Matrix res=Tr.query(l,r,1);
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    printf("%d",res.a[i][j]);
                    if(j!=1)printf(" ");
                }
                printf("\n");
            }
            if(m)printf("\n");
        }
    }
    return 0;
}