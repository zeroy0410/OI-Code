#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int mod=1e9+7;
const int base=233;
int n,T,cur;
char S[10550005];
int st[M],ed[M];
char tmp1[10550005],tmp2[10550005];
int P[10550005],Pow[10550005];
vector<int>wk;
void Init_HS(){
	Pow[0]=1;
	for(int i=1;i<=cur;i++)
		Pow[i]=1LL*Pow[i-1]*base%mod;
	for(int i=0;i<cur;i++){
		P[i+1]=((1LL*P[i]*base%mod+1LL*S[i])%mod+mod)%mod;
	}
}
int query(int l,int r){
	return ((1LL*P[r+1]-1LL*P[l]*Pow[r-l+1]%mod)%mod+mod)%mod;
}
int main(){
	freopen("hs.in","r",stdin);
	freopen("hs.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int l1=0,l2=0;
		cur=0;
		for(int i=1;i<=n;i++){
			st[i]=cur;char c;
			while(1){c=getchar();if(c!='\n'&&c!='\r'){S[cur++]=c;break;}}
			while(1){
				c=getchar();
				if(c=='\n'||c=='\r'||c==EOF)break;
				S[cur++]=c;
			}
			ed[i]=cur;
		}
		int li=-1,milen=1e9+7;
		for(int i=1;i<=n;i++){
			bool f=1;
			for(int j=st[i];j<ed[i]&&f;j++)if(S[j]=='*')f=0;
			if(f){
				if(milen>ed[i]-st[i]){
					li=i;
					milen=ed[i]-st[i];
				}
			}
		}
		if(li==-1){
			for(int i=st[1];i<ed[1];i++){
				if(S[i]=='*')break;
				tmp1[l1++]=S[i];
			}
			for(int i=ed[1]-1;i>=st[1];i--){
				if(S[i]=='*')break;
				tmp2[l2++]=S[i];
			}
			bool flag=1;
			for(int i=2;i<=n&&flag;i++){
				int j,k;
				for(j=st[i],k=0;j<ed[i]&&k<l1;j++,k++){
					if(S[j]=='*')break;
					if(S[j]!=tmp1[k])flag=0;
				}
				if(flag){
					if(k==l1){
						for(;j<ed[i];j++){
							if(S[j]=='*')break;
							tmp1[l1++]=S[j];
						}
					}
				}
				if(!flag)break;
				for(j=ed[i]-1,k=0;j>=st[i]&&k<l2;j--,k++){
					if(S[j]=='*')break;
					if(S[j]!=tmp2[k])flag=0;
				}
				if(flag){
					if(k==l2){
						for(;j>=st[i];j--){
							if(S[j]=='*')break;
							tmp2[l2++]=S[j];
						}
					}
				}
			}
			puts(flag?"Y":"N");
		}
		else {
			bool flag=1;
			Init_HS();
			for(int i=1;i<=n&&flag;i++){
				if(i==li)continue;
				int ct=0;
				for(int j=st[i];j<ed[i];j++)ct+=(S[j]!='*');
				if(ct>ed[li]-st[li]){flag=0;break;}
				int j,k;
				for(j=st[i],k=st[li];j<ed[i]&&flag&&k<ed[li];j++,k++){
					if(S[j]=='*')break;
					if(S[j]!=S[k])flag=0;
				}
				if(flag==0)break;
				int L=j,LL=k;
				for(j=ed[i]-1,k=ed[li]-1;j>=st[i]&&flag&&k>=st[li];j--,k--){
					if(S[j]=='*')break;
					if(S[j]!=S[k])flag=0;
				}
				if(flag==0)break;
				int R=j,RR=k;
				wk.clear();
				int tmp=0;
				for(int j=L;j<=R;j++){
					if(S[j]=='*'){
						if(tmp!=0)wk.push_back(tmp);
						tmp=0;
					}
					else tmp++;
				}
				if(wk.empty())continue;
				int pos=0,now=L,r;
				while(S[now]=='*'&&now<ed[i]-1)now++;
				for(r=LL;r<=RR&&pos<wk.size();){
					int l=wk[pos];
					if(now+l-1>=ed[i])continue;
					if(query(r,r+l-1)==query(now,now+l-1)){
						r+=l;
						now+=l;
						while(S[now]=='*'&&now<ed[i]-1)now++;
						pos++;
					}
					else r++;
				}
				if(pos!=wk.size())flag=0;
			}
			puts(flag?"Y":"N");
		}		
	}
	return 0;
}
