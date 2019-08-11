#include<bits/stdc++.h>
#define M 50005
#define LL long long 
using namespace std;
int n;
int h[M],v[M];
int dp1[M];
LL cnt1[M];
int dp2[M];
LL cnt2[M];
int main(){
    // freopen("missile.in","r",stdin);
    // freopen("biaoda.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&h[i],&v[i]);
    for(int i=1;i<=n;i++){
        dp1[i]=1;cnt1[i]=1;
        dp2[i]=1;cnt2[i]=1;
    }
    int ans=1;
    LL c=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(h[j]>=h[i]&&v[j]>=v[i]){
                if(dp1[i]<dp1[j]+1){
                    dp1[i]=dp1[j]+1;
                    cnt1[i]=cnt1[j];
                }
                else if(dp1[i]==dp1[j]+1){
                    cnt1[i]+=cnt1[j];
                }
            }
        }
        if(dp1[i]>ans){
            ans=dp1[i];
            c=cnt1[i];
        }
        else if(dp1[i]==ans){
            c+=cnt1[i];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=n;j>i;j--){
            if(h[j]<=h[i]&&v[j]<=v[i]){
                if(dp2[i]<dp2[j]+1){
                    dp2[i]=dp2[j]+1;
                    cnt2[i]=cnt2[j];
                }
                else if(dp2[i]==dp2[j]+1){
                    cnt2[i]+=cnt2[j];
                }
            }
        }
    }
    printf("%d\n",ans);
    cout<<c<<endl;
    for(int i=1;i<=n;i++)
        cout<<cnt1[i]<<' '<<cnt2[i]<<endl;
    // for(int i=1;i<=n;i++){
    //     if(dp1[i]+dp2[i]-1!=ans){
    //         printf("0.00000 ");
    //     }
    //     else {
    //         printf("%.5lf ",1.0*cnt1[i]*cnt2[i]/c);
    //     }
    // }
    puts("");
    return 0;
}