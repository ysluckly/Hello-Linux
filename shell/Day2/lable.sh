#!/bin/bash 

i=0
bar=''
lable=("|" "/" "-" "\\")
while [ $i -le 100 ]
do 
  printf "[%-100s][%d%%][%c]\r" "$bar" "$i" "${lable[i%4]}"
  let i++
  bar=${bar}'#'
  sleep 0.1
done
