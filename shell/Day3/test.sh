#!/bin/bash 

source  api.sh 

myAdd 1 2
echo $?


#while read line
#do 
#  echo "$line"
#done < file >> file.bak
#
#read line < file
#echo "$line"

#echo "hello world two" >> file
#for (( i = 0; i <= 3; i++ ))
#do 
#  echo "${i}hello world"
#done >> file1 

#arr=(1 2.23 "hello" 'b')
#
#i=0
#while [ $i -lt ${#arr[@]} ]
#do 
#  echo "$i:  ${arr[$i]}"
#  let i++
#done
#
#for i in ${arr[@]}
#do 
#  echo $i
#done 

#echo "0: ${arr[0]}"
#echo "1: ${arr[1]}"
#echo "2: ${arr[2]}"
#echo "3: ${arr[3]}"
#
#echo ${#arr[*]}
#echo ${#arr[@]}

#function fun()
#{
#  echo "sucess"
#  return 1;
#}
#
#set +x
#ret=$(fun)
#echo "$ret"
#set -x
#echo $?


#function myfun()
#{
#  echo "hello"
#  echo "$1"
#  echo "$2"
#  echo "$3"
#}

#myfun 1 2 3 4

#for i in $@
#do 
#  echo "$i"
#done

#while [ $# -gt 0 ]
#do 
#  echo "$1"
#  shift
#done
#
#echo "##############shift before###############"
#echo "\$0 -> $0"
#echo "\$1 -> $1"
#echo "\$2 -> $2"
#echo "\$3 -> $3"
#echo "\$# -> $#"
#echo "\$@ -> $@"
#echo "\$$ -> $$"
#
#shift #shift 1
#echo "##############shift after###############"
#echo "\$0 -> $0"
#echo "\$1 -> $1"
#echo "\$2 -> $2"
#echo "\$3 -> $3"
#echo "\$# -> $#"
#echo "\$@ -> $@"
#echo "\$$ -> $$"
#echo "\$0 -> $0"
#echo "\$1 -> $1"
#echo "\$2 -> $2"
#echo "\$3 -> $3"
#echo "\$# -> $#"
#echo "\$@ -> $@"
#echo "\$$ -> $$"

#sum=0
#for ((i = 1; i <= 100; i += 2))
#do 
#  let sum+=$i
#done  
#echo "$sum"

#sum=0
#for ((i = 1;i <= 100; i++))
#do
#  if [ -z $str ];then
#    str=$i
#  else
#    str=$str'+'$i
#  fi 
#  let sum+=$i;
#done 
#echo "$str""=$sum"
#
#until /bin/false
#do 
#  echo "hello"
#done

#while :
#do 
#  echo "hello"
#done

#for (( ; ; ))
#do 
#  echo "hello"
#done
#
#i=10
#until [ $i -le 0 ]
#do 
#  echo "hello $i"
#  let i--
#done

#i=0
#while [ $i -le 10 ]
#do 
#  echo "hello $i"
#  let i++
#done

#for i in {1..4} {a..f}
#do 
#  echo "$i"
#done 
#
#for i in {1..3}{a..d}
#do 
#  echo "$i"
#done 
#
#for i in {a..z}
#do 
#  echo "$i"
#done 
#
#for i in {1..10}
#do 
#  echo "$i"
#done

#for i in {1,2,3,4}
#do 
#  echo $i
#done

#for ((i = 0; i <= 10; i++))
#do 
#  echo "hello$i"
#done

#str='hello'
#read mystr 
#case $mystr in 
##case $1 in 
#  "$str" )
#    echo "start"
#    ;;
#  'stop'| "-s" )
#    echo "stop"
#    ;;
#   [Rr]estart )
#    echo "restart"
#    ;;
#  'down' )
#    echo "down"
#    ;;
#  'up' )
#    echo "up"
#    ;;
#  * )
#    echo "default"
#    ;;
#esac
