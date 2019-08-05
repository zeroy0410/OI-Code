#include<bits/stdc++.h>

#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;++x)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;--x)
#define FOR_(x,y,z,s) for(int x=y,x##_=z;x<=x##_;x+=s)
#define FOR__(x,y,z) for(int x=y,x##_=z;x<=x##_;x<<=1)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)

#define clr(x,y) memset(x,y,sizeof(x))
#define szf(x) sizeof(x)
#define min3(x,y,z) min(min(x,y),z)
#define max3(x,y,z) max(max(x,y),z)

#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read(x),read(y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define reads(str) sf("%s",str)

#define ts (*this)
#define sf scanf
#define pf printf

#define ll long long
#define ull unsigned long long
#define db double
#define ct clock_t
#define ck() clock()
#define rd rand()
#define rmx RAND_MAX
#define RD T*(rd*2-rmx)


using namespace std;

template<class T>bool tomin(T &x,T y){return x>y?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
template<class T>void read(T &x){
	char c;
	x=0;
	int f=1;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
	do x=(x<<3)+(x<<1)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	x*=f;
}

const db Pi=acos(-1);
const int maxn=4e6+5;
int n,m;
char s[maxn],t[maxn];
int p[maxn];
ll Manacher() {
	t[0]='$';
    t[m=1]='#';
    FOR(i,1,n){
    	t[++m]=s[i];
    	t[++m]='#';
    }
    int mx = 0, id = 0;
    ll ans=0;
    // puts(t+1);
    FOR(i,1,m){
        p[i]=mx>i?min(p[2*id-i],mx-i):1;
        while(i+p[i]<=m&&t[i+p[i]]==t[i-p[i]])++p[i];
        if(mx<i+p[i]){
            mx=i+p[i];
            id=i;
        }
        // pf("p[%d]=%d\n",i,p[i]);
        ans+=p[i]>>1;
    }
    return ans;
}

int main() {
	int T;
	read(T);
	while(T--){
		reads(s+1);
		reads(t+1);
		n=strlen(s+1);
		bool flag=1;
		FOR(i,1,n){
			if(s[i]!=t[i]){
				flag=0;
				break;
			}
		}
		if(flag)pf("%lld\n",Manacher());
		else{
			int l,r;
			FOR(i,1,n)if(s[i]!=t[i]){
				l=i;
				break;
			}
			DOR(i,n,1)if(s[i]!=t[i]){
				r=i;
				break;
			}
			int ans=0;
			FOR(i,l,r)if(s[i]!=t[r-i+l]){
				ans=-1;
				break;
			}
			if(~ans){
				while(l>=1&&r<=n&&s[l--]==t[r++])ans++;
				pf("%d\n",ans);
			}else pf("0\n");
		}
	}
	return 0;
}
