while true; do
./data.exe > data.in 
./B.exe < data.in > 1.ans 
./biaoda.exe < data.in > 2.ans 
if diff 1.ans 2.ans; then 
printf AC
echo
else
echo WA
exit 0
fi 
done 
