#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, const char * argv[]) {
 
    //申请内存
    int* arr = static_cast<int*>(mmap(
                    NULL,                   //分配的首地址
                    getpagesize(),          //分配内存大小(必须是页的整数倍, 32位1页=4k)
                    PROT_READ | PROT_WRITE, //映射区域保护权限：读|写
                    MAP_ANON | MAP_SHARED,  //匿名映射(不涉及文件io), 后面两个参数忽略
                    0,                      //要映射到内存中的文件描述符
                    0                       //文件映射的偏移量，通常设置为0，必须是页的整数倍
                ));
    printf("申请内存大小=%dk\n", sizeof(arr));
    
    *arr = 10;
    *(arr + 1) = 20;
    *(arr + 2) = 30;
    
    printf("arr[2]=%d\n", arr[2]);
    
    //释放指针arr指向的内存区域，并制定释放的内存大小
    munmap(arr, getpagesize());
    
    return 0;

}
