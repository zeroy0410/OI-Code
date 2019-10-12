#include<bits/stdc++.h>
#pragma GCC optinize(3)
using namespace std;
int x=142,y=48;
int X[]={0,0,23,27,29,39,43,46,51,53,54,57,58,71,77,78,85,99,101,102,106,108,113,139,141,142,153,170,197,198,201,202,204,275,277,281,305,503,507,509,547,550,554,561,759,763,765,785,887,891,893,955,983,987,989,999,1003,1011,1093,1094,1100,1271,1275,1277,1278,1399,1403,1405,1495,1501,1655,1661,1723,1767,1771,1774,1847,1851,1879,1885,1895,1907,2185,2186,2188,2295,2299,2301,2302,2491,2493,2519,2525,2747,2749,2791,2795,2798,2971,2973,2987,3191,3293,3307,3310,3415,3687,3755,4369,4471,4475,4477,4539,4567,4571,4573,4595,4919,4923,4979,5463,5469,5491,5939,6555,6557,8183,8823,8891,8935,8939,9015,9019,9831,10923,13107,14327,15351,16247,17527,17751,18023,30583},Y[]={0,15,23,39,46,51,54,71,78,99,102,108,113,114,116,142,198,204,226,228,232,275,305,306,547,550,561,562,610,612,785,802,1094,1100,1122,1124,1220,1224,1570,1604,2188,2244,2248,3140,3208,4369,8738,17476,34952};//合法状态 四联通快
const int mod=998244353;
struct Matrix{
	int a[145][145];
	Matrix(){memset(a,0,sizeof(a));}
	Matrix operator * (const Matrix& res){ 
		Matrix ans;
		for(int k=1;k<=x;k++)
			for(int i=1;i<=x;i++){
				if(a[i][k]==0)continue;
				for(int j=1;j<=x;j++){
					if(res.a[k][j]==0)continue;
					ans.a[i][j]=(ans.a[i][j]+1LL*a[i][k]*res.a[k][j])%mod;
				}
			}
		return ans;
	}
	Matrix operator + (const Matrix& res){
		Matrix ans;
		for(int k=1;k<=x;k++){
			int i=1;
			if(a[i][k]==0)continue;
			for(int j=1;j<=x;j++){
				if(res.a[k][j]==0)continue;
				ans.a[i][j]=(ans.a[i][j]+1LL*a[i][k]*res.a[k][j])%mod;
			}
		}
		return ans;
	}
}ma,in[35];
Matrix qkpow(int b){
	Matrix res;
	for(int i=1;i<=x;i++)
		res.a[i][i]=1;
	int ct=0;
	while(b){
		if(b&1)res=res+in[ct];
		ct++;
		b>>=1;
	}
	return res;
}
int T;
int main(){
//	freopen("fudepen.in","r",stdin);
//	freopen("fudepen.out","w",stdout);
	for(int i=1;i<=x;i++){
		int s=X[i],w=0;
		for(int j=0;j<16;j++)
			if(~s&1<<j){
				w=1<<j;
				break;
			}
		if(w>=16)continue;
		for(int j=1;j<=y;j++){
			if((~s&Y[j])==Y[j]&&(Y[j]&w)){
				int nxt=s|Y[j],nxtp;
				while((nxt&15)==15)nxt>>=4;
				for(int k=1;k<=x;k++)
					if(X[k]==nxt){
						nxtp=k;
						break;
					}
				ma.a[i][nxtp]++;
			}
		}
	}
	in[0]=ma;
	for(int i=1;i<=31;i++)
		in[i]=in[i-1]*in[i-1];
	scanf("%d",&T);
	while(T--){
		int x;
		scanf("%d",&x);
		Matrix fa;
		fa.a[1][1]=1;
		Matrix ans=fa*qkpow(x);
		printf("%d\n",ans.a[1][1]);
	}
	return 0;
}
