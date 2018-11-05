#include "Sort.h"


int main()
{
    int arr[]={2,55,77,2,98,12,43,66,7,3,33};
    int n = sizeof(arr)/arr[0];
    int start = 0;
    int end=n-1;
//插入排序
InsertSort(arr,n);
//希尔排序
ShellSort(arr, n);
//选择排序
SelectSort(arr,n);
//堆排序
HeapSort(arr, n);
//冒泡排序
BubbleSort(arr, n);
//快速排序
QuickSort(arr,start, end);
//归并排序
MergeSort(arr,n);
//计数排序
CountSort(arr, n);


}
