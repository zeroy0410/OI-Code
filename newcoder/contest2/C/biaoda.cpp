#include<bits/stdc++.h>
using namespace std;
const int M=100005;
int n,fl,tot,num,col;
int x,y,z,o;
struct node{int len; int ls,rs,ml,mr; }A[M];
struct Node{int len,Q[101]; }B[11];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&fl);
        if(fl==1){
            scanf("%d",&x);
            printf("%d %d\n",A[x].ml,A[x].mr);
        }
        if(fl==2){
            scanf("%d%d",&num,&col);
            A[++tot].len=num;
            if(!col){
                A[tot].ml=1,A[tot].mr=num;
                A[tot].ls=A[tot].rs=num;
            }
        }
        if(fl==3){
            scanf("%d%d%d%d",&x,&y,&z,&o);
            if(A[y].ls>=z){
                if(A[x].ls==A[x].len)A[y].ls+=A[x].ls;
                else A[y].ls=z+A[x].ls;
            }
            if(A[y].len-A[y].rs<=z){
                if(A[x].rs==A[x].len)A[y].rs+=A[x].rs;
                else A[y].rs=A[y].len-z+A[x].rs;
            }
            A[y].len+=A[x].len;
            int pl=0,pr=0,ma=0;
            if(A[y].ml<=z&&A[y].mr>z){
                int t=z-A[y].ml+1+A[x].ls;
                if(t>ma||(t==ma&&pl<A[y].ml)){
                    ma=t;
                    pl=A[y].ml,pr=A[x].ls+z;
                }
                t=A[y].mr-1+A[x].rs;
                if(t>=ma||(t==ma&&pr<A[y].mr+A[x].len)){
                    ma=t;
                    pl=A[y].ml,pr=A[x].ls+z;
                }
            }else{
                pl=A[y].ml,pr=A[y].mr;
                ma=pr-pl+1;
                if(A[y].ml>z)pl+=A[x].len,pr+=A[x].len;
            }
            if(A[y].ls>ma){
                pl=1,pr=A[y].ls;
                ma=A[y].ls;
            }
            int t=A[x].mr-A[x].ml+1;
            if((t==ma&&A[x].ml+z>pl)||t>ma)pl=z+A[x].ml,pr=z+A[x].mr,ma=t;
            if(A[y].rs>=ma){
                pl=A[y].len-A[y].rs+1,pr=A[y].len;
                ma=A[y].rs;
            }
            A[y].ml=pl,A[y].mr=pr;
            if(!o){
                A[x].ls=A[x].rs=A[x].ml=A[x].mr=0;
                A[x].len=0;
            }
        }
    }
    return 0;
}