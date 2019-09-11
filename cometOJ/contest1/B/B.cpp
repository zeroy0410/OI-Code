#include<bits/stdc++.h>
#define M 400005
using namespace std;
int T,n;
char S[M];
// struct P100{
// 	struct YD_tree{
// 	    struct YD{
// 	        int l,r,mx;
// 	    }tree[M<<2];
// 	    #define fa tree[p]
// 	    #define lson tree[p<<1]
// 	    #define rson tree[p<<1|1]
// 	    void Up(int p){
// 	        fa.mx=max(lson.mx,rson.mx);
// 	    }
// 	    void build(int l,int r,int p){
// 	        fa.l=l;fa.r=r;
// 	        if(l==r){
// 	            fa.mx=nxt[l];
// 	            return;
// 	        }
// 	        int mid=(l+r)>>1;
// 	        build(l,mid,p<<1);
// 	        build(mid+1,r,p<<1|1);
// 	        Up(p);
// 	    }
// 	    int query(int l,int r,int p){
// 	        if(fa.l==l&&fa.r==r)return fa.mx;
// 	        int mid=(fa.l+fa.r)>>1;
// 	        if(r<=mid)return query(l,r,p<<1);
// 	        else if(l>mid)return query(l,r,p<<1|1);
// 	        return max(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
// 	    }
// 	}Tr;
// 	struct node{
// 		int id,v;
// 		bool operator < (const node& res)const{
// 			if(res.v!=v)return v<res.v;
// 			return id<res.id;
// 		}
// 	};
// 	set<node>SS;
// 	set<node>::iterator it;
// 	void solve(){
// 		S[n+1]='*';S[n+2]='*';SS.clear();
// 		memset(pre,-1,sizeof(pre));
// 		memset(nxt,0,sizeof(nxt));
// 		ans=0;
// 		pre[0]=nxt[0]=0;
// 		for(int i=1;i<=n;i++){
// 			pre[i]=pre[i-1];
// 			if(S[i]=='*'&&S[i+1]!='#')pre[i]++;
// 			if(S[i]=='*'&&S[i+1]=='#'&&S[i+2]=='.');
// 			if(S[i]=='*'&&S[i+1]=='#'&&S[i+2]=='*')pre[i]++;
// 			if(S[i]=='.'&&S[i+1]=='#'&&S[i+2]!='*')pre[i]--;
// 			if(S[i]=='.'&&S[i+1]=='#'&&S[i+2]=='*');
// 			if(S[i]=='#'&&S[i+1]=='#'&&S[i+2]!='*')break;
// 			if(pre[i]<0)break;
// 		}
// 		for(int i=1;i<=n;i++){
// 			if(S[i]=='.'&&S[i+1]=='#'&&S[i+2]!='*')S[i]='*';
// 			if(S[i]=='*'&&S[i+1]!='#')S[i]='.';
// 			if(S[i]=='*'&&S[i+1]=='#'&&S[i+2]=='*')S[i]='.';
// 		}
// 		for(int i=1;i<=n;i++)
// 			tmp[i]=S[n-i+1];
// 		int st=1;
// 		tmp[n+1]=tmp[n+2]='*';
// 		while(pre[n-st+1]==-1)st++;nxt[st-1]=0;
// 		// cout<<st<<endl;
// 		for(int i=st;i<=n;i++){
// 			nxt[i]=nxt[i-1];
// 			if(tmp[i]=='*'&&tmp[i+1]!='#')nxt[i]++;
// 			if(tmp[i]=='*'&&tmp[i+1]=='#'&&tmp[i+2]=='.');
// 			if(tmp[i]=='*'&&tmp[i+1]=='#'&&tmp[i+2]=='*')nxt[i]++;
// 			if(tmp[i]=='.'&&tmp[i+1]=='#'&&tmp[i+2]!='*')nxt[i]--;
// 			if(tmp[i]=='.'&&tmp[i+1]=='#'&&tmp[i+2]=='*');
// 			if(tmp[i]=='#'&&tmp[i+1]=='#'&&tmp[i+2]!='*')break;
// 		}
// 		for(int i=1;i<=n/2;i++)
// 			swap(nxt[i],nxt[n-i+1]);
// 		// for(int i=1;i<=n;i++)printf("%c",S[i]);
// 		// puts("");
// 		// for(int i=1;i<=n;i++)
// 		// 	printf("%d",pre[i]);
// 		// puts("");
// 		// for(int i=1;i<=n;i++)
// 		// 	printf("%d",nxt[i]);
// 		// puts("");
// 		nxt[n+1]=0;
// 		Tr.build(1,n,1);
// 		for(int i=1;i<=n;i++){
// 			if(pre[i]<0)break;
// 			// cout<<pre[i];
// 			ans=max(ans,pre[i]);
// 			SS.insert((node){i,nxt[i]});
// 			it=SS.lower_bound((node){-1,nxt[i+1]-pre[i]});
// 			if(it==SS.begin()){
// 				ans=max(ans,Tr.query(1,i,1)+pre[i]-nxt[i+1]);
// 			}
// 			else {
// 				it--;
// 				ans=max(ans,Tr.query((it->id)+1,i,1)+pre[i]-nxt[i+1]);
// 			}
// 		}
// 		printf("%d\n",ans);
// 	}
// }p100;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%s",S+1);
        n=strlen(S+1);
        int now=0,tot=0,pos=0,ans=0;
        for(int i=1;i<=n;i++){
            if(S[i]=='*'){
                now++;tot++;
                if(i>1&&S[i-1]=='#'&&S[i-2]=='#')tot--;
            }
            if(S[i]=='#'){
                if(S[i+1]=='*'){pos=0;continue;}
                if(S[i-1]=='#')break;
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