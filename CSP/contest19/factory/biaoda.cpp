#include<bits/stdc++.h>
using namespace std;
const int maxn=250;
bool cur1;
int n,m,id;
struct node{
    int l,r;
    bool operator <(const node &_)const{
        return l!=_.l?l<_.l:r>_.r;
    }
}A[maxn];
int dp[2][maxn][maxn];
int _min(int a,int b){
    return A[a].r<A[b].r?a:b;
}
void tomax(int &a,int b){
    if(a<b)a=b;
}
int calc(int i,int j){
    if(A[i].l>A[j].r)return -1e9;
    return A[j].r-A[i].l+1;
}
bool cur2;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&A[i].l,&A[i].r);
        A[i].l++;
    }
    sort(A+1,A+1+n);
    int cur=0;
    memset(dp[cur],-63,sizeof(dp[cur]));
    dp[0][0][1]=0;
    for(int i=1;i<=n;i++){
        cur^=1;
        memset(dp[cur],-63,sizeof(dp[cur]));
        for(int j=0;j<m;j++){
            for(int k=1;k<=i;k++){
                tomax(dp[cur][j][_min(i,k)],dp[cur^1][j][k]);
                if(k!=i)tomax(dp[cur][j+1][k],dp[cur^1][j][k]+A[i].r-A[i].l+1);
                tomax(dp[cur][j+1][i+1],dp[cur^1][j][k]+calc(i,_min(i,k)));
            }
        }
    }
    cout<<dp[cur][m][n+1]<<endl;
    return 0;
}
