#!/bin/bash 


read myint
[ $myint -eq 100 ] && echo "yes 100"
[ $myint -eq 200 ] || echo "no 200"

#aread myint 
#if /bin/true ;then
#  :
#else 
#  echo "noequal"
#fi

#read myint 
#if [ $myint -eq 100 ];then
#  echo "equal"
#else 
#  echo "noequal"
#fi
#
#read filename
#if grep '222' "$filename";then
#  echo "yes"
#else
#  echo "no"
#fi


#read myint 
#if [ $myint -le 100 ];then
#  echo "le 100"
#  if [ $myint -le 50 ];then 
#    echo "le 50"
#  elif [ $myint -ge 50 ];then 
#    echo "ge 50"
#  else 
#    echo "myint in 50 ~ 100"
#  fi 
#else
#  echo "gt 100"
#fi

#read mystring
#if [ "$mystring" == "hello" ];then
#  echo "hello"
#fi

#read d1 d2 
#[ $d1 -eq 100 -o $d2 -eq 200 ]
#echo $?

#read d1 d2 
#[ $d1 -eq 100 -a $d2 -eq 200 ]
#echo $?

#read mystring
#[ ! "$mystring" == "hello" ]
#echo $?
#
#[ -c /dev/tty ]
#echo $?
#[ -b /dev/sda ]
#echo $?
#[ -f ./test.sh ]
#echo $?
#[ -d / ]
#echo $?

#read mystring
#
#[ "$mystring" == "hello" ]
#echo $?
#


#read mystring 
#[ $mystring == "helloworld" ]
#echo $?
#[ $mystring != "helloworld" ]
#echo $?
#[ -z $mystring ]
#echo $?
#[ -n $mystring ]
#echo $?
#

#read myint
#[ $myint -eq 100 ] 
#echo $?
#[ $myint -ne 100 ] 
#echo $?
#[ $myint -lt 100 ] 
#echo $?
#[ $myint -gt 100 ] 
#echo $?


#read myint
#test $myint -eq 100
#echo $?
#


#myint=520
#echo $myint 
#ret=$((myint++))
#echo $myint


#echo `date +%Y`
#echo $(date +%Y)

#your_name="yk"
#echo ${#your_name}
#echo "hello, $your_name"
#echo "hello, ${your_name}"
#echo 'hello, '$your_name''
#echo 'hello, ${your_name}'


#echo $a

#pwd
#cd ..
#pwd

#echo $RANDOM


#-e开启转义，-c不换行
#echo -e "OK! \c a"
#echo "sadas"

#字符串运算符
#a="abc"
#
#if [ $a ];then 
#  echo "true"
#else
#  echo "false"
#fi
#
#布尔运算
#a=10
#b=20
#
#if [ $a -lt 100 -a $b -gt 0 ];then
#  echo "true"
#else
#  echo "false"
#fi
#
#if [ $a -lt 2 -o $b -gt 0 ];then
#  echo "true"
#else
#  echo "false"
#fi

#使用expr进行算术运算
#a=10
#b=20
#
##必须要使用命令代换$()或``
#val=$(expr $a + $b)
#echo "a + b = $val"
#
#val=`expr $a  \* $b`
#echo "a * b = $val"
#
#if [ $a == $b ];then
#  echo "=="
#else
#  echo "!="
#fi
#
#
#if [ $a != $b ];then
#  echo "!="
#else
#  echo "=="
#fi
#
#进行了文件包含
#. api.sh 
#
#read d1 d2 
#result=$(intAdd $d1 $d2)
#
#echo $result



#str1="hello"
#
#if [ $str == $str1 ];then
#  echo "true"
#else
#  echo "false"
#fi 


#case $1 in
#  'start' )
#    echo "start"
#    ;;
#  'stop' )
#    echo "stop"
#    ;;
#  * )
#    echo "default"
#    ;;
#
#esac
#

#trap 'echo "hello";exit 1' SIGINT
#until false
#do 
#  :
#done

#arr=(1 2 3 4 5 5)

#echo ${arr[0]}
#echo ${arr[0]}
##echo ${arr[@]}
##echo ${#arr[*]}
#echo ${#arr[@]}
#echo ${arr[*]}
