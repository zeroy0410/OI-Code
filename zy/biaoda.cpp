#include <bits/stdc++.h>
using namespace std;
#define M 35
int gcd(int a,int b){
    return !b?a:gcd(b,a%b);
}
const int P=1e9+7;
void calc(int &x,int y){
    x+=y;
    if(x>=P)x-=P;
}
void Mul(int &x,int y){
    x=1LL*x*y%P;
}
int F[M][M],A[M],n,K,lim,mark[M],Hv[M],C[M][M];
int Nd[1<<20],Cnt[1<<20],Pos[M],len_pos,bin[1<<20];
void Init(){
    C[0][0]=1;
    for(int i=1;i<=27;i++){
        C[i][0]=1;
        for(int j=1;j<i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
        C[i][i]=1;
    }
    for(int j=0;j<20;j++)bin[1<<j]=j;
    mark[11]=mark[13]=mark[17]=mark[19]=mark[22]=mark[23]=mark[26]=1;
    for(int i=1;i<=27;i++)if(!mark[i])Pos[len_pos++]=i;
    for(int i=1;i<1<<20;i++)Cnt[i]=Cnt[i^(i&-i)]+1;
    n=27;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)F[i][j]=gcd(i,j);
}
int main(){
	Init();
    int T;
    cin>>T;
    while(T--){
        scanf("%d%d%d",&n,&K,&lim);
        for(int i=1;i<=n;i++)
            scanf("%d",&A[i]);
        int bs=0,Bs=0;
        for(int i=1;i<=n;i++)bs|=1<<A[i]-1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)Bs|=1<<F[A[i]][A[j]]-1;
        for(int i=1;i<=lim;i++){
            Hv[i]=0;
            for(int j=1;j<=n;j++)Hv[i]|=1<<F[i][A[j]]-1;
        }
        int tt=0,ans=0,can_use=0;
        for(int i=1;i<=lim;i++)tt+=!mark[i];
        for(int i=1;i<=lim;i++)
            if(mark[i]&&(i&1))can_use++;
        for(int i=0;i<1<<tt;i++){
            Nd[i]=Bs;
            int tr=0;
            int last=bin[i&-i],res=0;
            for(int j=0;j<tt;j++)
                if((1<<j)&i)res|=1<<F[Pos[j]][Pos[last]]-1,tr|=1<<Pos[j]-1;
            Nd[i]|=Nd[i^(i&-i)];
            Nd[i]|=res;
            Nd[i]|=Hv[Pos[last]];
            tr|=bs;
            if((tr&Nd[i])!=Nd[i])continue;
            int fl=0;
            if(tr&2)fl=1;
            else {
                fl=1;
                for(int j=4;fl&&j<=lim;j+=2)
                    if(tr&(1<<j-1))fl=0;
            }
            if(fl){
                fl=0;
                if(lim>=22)fl++;
                if(lim>=26)fl++;
            }
            for(int j=0;j<=can_use;j++){
                if(j+Cnt[i]>K)break;
                calc(ans,1LL*C[can_use][j]*C[K-1][j+Cnt[i]-1]%P);
                if(fl&&j+Cnt[i]!=K)calc(ans,1LL*fl*C[can_use][j]*C[K-1][j+Cnt[i]]%P);
                if(fl==2&&(tr&2)&&j+Cnt[i]<K-1)calc(ans,1LL*C[can_use][j]*C[K-1][j+Cnt[i]+1]%P);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
