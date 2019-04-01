#!/bin/bash 

#cat << EOF > Makefile
#test:test.c
#  gcc -o test test.c
#.PHONY:clean
#clean:
#  rm -f test 
#EOF 



#trap 'sl;exit 1' SIGINT
#trap '' SIGINT #忽略
#trap  SIGINT #默认动作

#while :
#do 
#  :
#done


#cat <<EOF
#  aaaaaa
#EOF 

#cc=gcc
#src=$(ls *.c)
#bin=test
#
#cat <<EOF > Makefile
#$bin:$src 
#  $cc -o \$@ \$<
#
#.PHONY:clean
#clean:
#  rm -f $bin 
#EOF 

#
#wc -l << EOF
#cat << EOF
#  aaaaaaaa
#  bbbbbbbb
#  cccccccc
#EOF


#对文件进行备份
#[ $# -ne 1 ] && exit 1
#
#while read line
#do 
#  echo $line 
#done < $1 > $1.bak

#i=0
#while read line 
#do 
#  echo "$i : $line"
#  let i++
#done < file 

#从文化中拿数据

#i=0
#cat file | while read line 
#do 
#  echo "$i : $line"
#  let i++
#done

#read x
#echo $x
#read y
#echo $y



#输出重定向和追加重定向

#cat file


#i=0
#for ((; i <= 10; i++))
#do 
# echo "hello world $i"
#done > file
 
#对于Shell的数组来说，如果中间有空的的话
#对于全部遍历来说，直接是空的，但是对于使用数组来遍历还是要遍历到那个位置
#出来只有6个元素
#arr=(10 3.14 a 'x' "abcd")
#
#arr[100]=100
#
#echo ${#arr[@]}
#echo ${arr[@]}
#
#不可以遍历到元素100
#for (( i = 0; i < ${#arr[@]}; i++ ))
#可以遍历到元素100
#for (( i = 0; i <= 100; i++ ))
#do 
#  echo ${arr[$i]}
#done


#使用这种遍历可以找到100，这个是遍历全部的
#for i in ${arr[@]}
#do 
#  echo $i
#done

#echo ${arr[0]}
#echo ${arr[1]}
#echo ${arr[2]}
#echo ${arr[3]}
#echo ${arr[4]}
#echo ${#arr[@]}
#echo ${#arr[*]}
#echo ${arr[*]}


#touch file

#eco "helloworld"


#求和
#total()
#{
#  top=$1
#  sum=0
#  i=1
#  while [ $i -le $top ]
#  do 
#    let sum+=i
#    let i++
#  done
#  echo $sum 
#}
#
#total $1
#

#学习eval
#a="123"
#
#echo '${'a'}'
#eval echo '${'a'}'


#echo "Last Parament: \$$#"
#eval echo "Last Parament: \$$#"

#fork炸弹
#.() { . | . & }; .

#max_min()
#{
#  max=$1
#  min=$1
#  for i in $@
#  do  
#      [ $max -lt $i ] && max=$i
#      [ $min -gt $i ] && min=$i
#  done
#
#  str="max:$max min:$min"
#  echo $str 
#  #echo $max 
#  #echo $min
#}
#
##ret=`max_min 1 32 0 2 3`
#ret=`max_min $@`
#echo $ret

#函数,参数列表没有内容
#shell当中的函数当成小脚本或者命令
#$0不会随着调用函数发生改变
#具有输出结果和退出结果
#fun()
#{
#  echo 0
#  #return 1
#  #echo "$0"
#  #echo "$1"
#  #echo "$2"
#  #echo "$3"
#  #echo "$#"
#  #echo "$@"
#  #echo "$$"
#  #echo "hello my fun"
#}
#
#ret=`fun`
#if [ $ret -eq 0 ];then
#  echo "sucess"
#else 
#  echo "failed"
#fi
#fun 123 abc hello
#if [ $? -eq 0 ];then
#  echo "sucess"
#else
#  echo "failed"
#fi 

#shift可以让命令行参数左移
#echo "#############shift0##############"
#echo "\$0: $0"
#echo "\$1: $1"
#echo "\$2: $2"
#echo "\$3: $3"
#echo "\$4: $4"
#echo "\$@: $@"
#echo "\$#: $#"
#echo "\$$: $$"
#
#shift 1
#echo "#############shift1##############"
#echo "\$0: $0"
#echo "\$1: $1"
#echo "\$2: $2"
#echo "\$3: $3"
#echo "\$4: $4"
#echo "\$@: $@"
#echo "\$#: $#"
#echo "\$$: $$"
#
#shift 2
#echo "#############shift2##############"
#echo "\$0: $0"
#echo "\$1: $1"
#echo "\$2: $2"
#echo "\$3: $3"
#echo "\$4: $4"
#echo "\$@: $@"
#echo "\$#: $#"
#echo "\$$: $$"
#求出命令行参数上的最大值和最小值
#sum=$1
#min=$1
#for i in $@
#do 
#
#  [ $sum -lt $i ] && sum=$i
#  [ $min -gt $i ] && min=$i
#  #if [ $sum -lt $i ]
#  #then
#  #  sum=$i
#  #fi 
#  #if [ $min -gt $i ]
#  #then 
#  #  min=$i
#  #fi 
#done
#echo "sum: $sum"
#echo "min: $min"

#i=0
#while [ i -le $# ]
#do 
#  if [ $(\i)  ]

#输出命令行参数
#for i in $@
#do echo $i
#done

#特殊变量
#echo "\$0: $0"
#echo "\$1: $1"
#echo "\$2: $2"
#echo "\$3: $3"
#echo "\$4: $4"
#echo "\$@: $@"
#echo "\$#: $#"
#echo "\$$: $$"


#输出1+2+3+4+....+100 = 5050
#i=0
#sum=0
#str=''
#while [ $i -le 100 ]
#do 
#  if [ -z $str ];then
#    str=$i
#  else
#    str=$str'+'$i
#  fi
#  let sum+=i
#  #echo "${i} + "
#  let i++
#done 
#echo $str  = $sum

#从1加到100，求和

#i=0
#c=0
#while [ $i -le 100 ]
#do 
#  ((c += i++))
#  #echo $i
#done
#echo $c

#i=0
#while [ $i -le 10 ]
#do 
#  echo $i
#  let i++
#done


#编写死循环
#while [ 1 -eq 1 ]
#while true
#while ! false
#do 
#  echo "hello"
#done


#i=0
##直到条件满足，才结束
#until test $i -ge 10
#do 
#  echo $i
#  let i++
#done



#for i in {1..5} {a..c}
#do 
#  echo $i
#done

#for i in 1 2 3 4 a b c d
#do 
#  echo $i
#done


#i=0
##while ((i <= 10))
#while [ $i -le 10 ]
#do 
#  echo $i
#  let i++
##  ((i++))
#done
#

#for (( i = 0; i <= 10; i++ ))
#do 
#  echo $i
#done
#

#read op 

##$1内置变量,取出命令行的第一个参数
#case $1 in
#  [Ss]tart | -s ) #case 'start':
#    echo "start"
#    ;; #break
#  [Ss]top | -t)
#    echo "stop"
#    ;;
#  [Rr]estart | -rt )
#    echo "restart"
#    ;;
#  [Ss]tatus | -st )
#    echo "status"
#    ;;
#  * )
#    echo "default"
#    ;;
#esac 

#switch()
#{
#
#



#read mystr 
#[[ $mystr ==  [Hh]ella ]] && {
#  echo "hello"
#}

#read myint
#[ $myint -eq 100 ] || {
#  echo "hello $myint"
#[ $myint -le 100 ] || {
#  echo "hello "
#}
#}




#if [ 1 -eq 1 ];then
#if :;then
#  echo "hello"
#fi

#read myint
#
##多行命令写在一行，后面加上;
#if [ $myint -eq 100 ];then
#  #echo "hello"
#  :
#elif [ $myint -gt 100 ];then 
#  echo "big!"
#else 
#  echo "small!"
#  if [ $myint -le 50 ];then 
#    echo "<=50"
#  else 
#    echo ">50"
#  fi
#fi

#read myint 
#[ ! $myint -eq 100 ]
#echo $?

#read file
#[ -c $file ] 
#echo $?
#

#read mystr 
##== != =
#[ "X$mystr" == "Xhelloworld" ]
#echo $?
#

#read myint #读取变量
#echo $myint 
#eq:equal 
#lt:less than
#gt:great than
#le:less and equal
#ge:grear and equal
#[ $myint -eq 100 ] #后面的是参数或者选项,
#]是一个选项，结束标志位
#相等：0
#不相等：1
#echo $? #查看退出码








#str='hello'
#echo ${#str}

#str='helloworld'
#echo ${str:1:4}

#string='bit is a great company'
#echo `expr index "$string" is`

#单引号和引号的区别
#val=100
#
#echo "################1#############"
#echo "hello world : \` : \" : \\ : $val : $(date +%Y)"
#echo "################2#############"
#echo 'hello world : \` : \" : \\ : $val : $(date +%Y)'
#


#DATE=`date`

#DATE=$(date)

#echo $DATE

#echo hello world



#echo $x

#x=123
#
#echo $x
##x=''
#unset x
#echo "x: $x"
#echo "y: a${y}b"

#readonly str="hello"
#str=askdl
#
#echo ${str}aaaa  #$加{}输出变量内容

#echo $str"aaaaa"  #直接写一个东西不带字符串就解释为字符串


#myint=123
#myfloat=3.14
#mystr="helloshell"
#mystr1=",helloworld"
#mychar='c'
#totalStr=$mystr$mystr1
#
#echo $mystr$mystr1
#echo $myint #加上$可以查看环境变量名称
#echo $myfloat #加上$可以查看环境变量名称
#echo $mystr #加上$可以查看环境变量名称
#echo $mychar #加上$可以查看环境变量名称
#

#echo "hello world"

#pwd
#cd ..
#pwd
#
