#!/bin/bash 

#逆序
echo "before"
cat file
echo "after"
while read line
do 

done < file 

#求斐波那契数列
#read num
#((num1 = num - 2))
#a=1
#b=2
#result=0
#i=0
#while [ $i -le $num1 ]
#do 
#  let i++
#  let result=$a+$b
#  a=$b
#  b=$result
#done
#
#echo $a

#求最大值，最小值以及平均值
#i=0
#max=$1
#min=$1
#mid=0
#for i in $@
#do 
#  let mid+=$i
#  [ $max -lt $i ] && max=$i
#  [ $min -gt $i ] && min=$i
#done
#
#((a = mid / $#))
#echo $a
#echo "max : $max"
#echo "min : $min"
#printf "%.2f\n" "$mid"
