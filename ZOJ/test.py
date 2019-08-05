import sys
T=int(input())
lis=[0,1,1,2]
for i in range(T):
	a,b= map(int,sys.stdin.readline().split())
	if a//3!=b//3:
		a=a%3
		b=b%3
		ans=0
		if a==0:
   			ans=ans+2
		elif a==1:
   			ans=ans+2
		elif a==2:
   			ans=ans+1
		if b==0:
   			ans=ans+2
		elif b==1:
			ans=ans+1
		elif b==2:
   			ans=ans+2
	else:
		a=a%3+1
		b=b%3+1
		ans=0
		for j in range(a,b+1):
			ans=ans+lis[j]
	print ans%2	
