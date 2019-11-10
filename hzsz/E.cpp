#include<cstdio>
#include<string.h>
using namespace std;
void get_nxt(char *S,int *nxt){
	nxt[1]=nxt[2]=1;
	int len=strlen(S+1);
	for(int i=2;i<=len;i++){
		int j=nxt[i];
		while(j>1&&S[i]!=S[j])j=nxt[j];
		if(S[i]==S[j])j++;
		nxt[i+1]=j;
	}
}
char S[1000005];
int nxt[1000005];
int main(){
	while(scanf("%s",S+1)&&S[1]!='.'){
		get_nxt(S,nxt);
		int l=strlen(S+1);
		int lop=l-nxt[l+1]+1;
		printf("%d\n",l%lop?1:l/lop);
	}
	return 0;
}
