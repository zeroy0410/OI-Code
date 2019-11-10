#include<bits/stdc++.h>
using namespace std;
int T;
char a[400004];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%s",a+1);
        int n=strlen(a+1);
        int now=0,tot=0,pos=0,ans=0;
        for(int i=1;i<=n;i++){
            if(a[i]=='*'){
                now++;tot++;
                if(i>1&&a[i-1]=='#'&&a[i-2]=='#')tot--;
            }
            if(a[i]=='#'){
                if(a[i+1]=='*'){pos=0;continue;}
                if(a[i-1]=='#')break;
                if(now==0)break;
                now--;pos=1;
            }
            if(now+pos>1)now=tot;
            ans=max(ans,now);
        }
        printf("%d\n",ans);
    }
    return 0;
}