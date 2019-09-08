#include<bits/stdc++.h>
#define debug(x) cerr<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl
#define debug2(a,x) cerr<<#a<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl
using namespace std;
const int maxn=2e6+100,P=1e9+7;
bool cur1;
inline void Rd(int &res){
    static char c;res=0;
    while((c=getchar())<48);
    do res=(res<<1)+(res<<3)+(c^48);
    while((c=getchar())>47);
}
long long qpow(long long p,long long q){
    long long res=1;
    while(q){
        if(q&1)res=res*p%P;
        p=p*p%P;
        q>>=1;
    }
    return res;
}
int n,r,q,t;
int id,pos[30][10];
 
struct matrix {
    double a[55][55];
    matrix(){
        for(int i=1;i<=id;i++)
            for(int j=1;j<=id;j++)
                a[i][j]=0;
    }
    matrix operator *(const matrix &b)const{
        matrix res;
        for(int i=1;i<=id;i++)
            for(int j=1;j<=id;j++)
                for(int k=1;k<=id;k++)
                    res.a[i][j]+=a[i][k]*b.a[k][j];
        return res;
    }
    void Print(){
        for(int i=1;i<=id;i++){
            for(int j=1;j<=id;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
};
matrix qpow(matrix p,int q){
    matrix res;
    for(int i=1;i<=id;i++)
        res.a[i][i]=1;
    while(q){
        if(q&1)res=res*p;
        p=p*p;
        q>>=1;
    }
    return res;
}
bool check(double p){
    matrix s,tmp,res;
    s.a[id][1]=1;
    for(int k=1;k<=q;k++){
        int ed=min(r,k-1);
        if(k==q)ed=r;
        for(int j=0;j<=ed;j++){
            tmp.a[pos[j][k]][pos[min(r,j+1)][min(q,k+1)]]+=p;
            tmp.a[pos[j][k]][id]+=p*min(r,j+1);
            if(k!=1)tmp.a[pos[j][k]][pos[0][k-1]]+=1-p;
        }
    }
    tmp.a[id][id]=1;
    res=qpow(tmp,n)*s;
    return res.a[pos[0][q]][1]>t;
}
bool cur2;
int main(){
    Rd(n);Rd(r);Rd(q);Rd(t);
    for(int k=1;k<=q;k++){
        int ed=min(r,k-1);
        if(k==q)ed=r;
        for(int j=0;j<=ed;j++){
            pos[j][k]=++id;
        }
    }
    id++;
    double l=0,r=1,ans=-1;
    while(l+1e-9<=r){
        double mid=(l+r)*0.5;
        if(check(mid)){
            ans=mid;
            r=mid;
        }else l=mid;
    }
    if(ans<0){
        puts("Impossible.");
    }else printf("%.6f\n",ans);
    return 0;
}
