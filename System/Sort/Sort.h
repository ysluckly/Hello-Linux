#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <string.h>
#incldue <stdlib.h>
#include <unistd.h>

//插入排序
void InsertSort(int *arr,int n);
//希尔排序
void ShellSort(int* arr,int n);
//选择排序
void SelectSort(int* arr,int n);
//堆排序
void HeapSort(int* arr, int n);
//冒泡排序
void BubbleSort(int* arr, int n);
//快速排序
void QuickSort(int* arr,int start, int end);
//归并排序
void MergeSort(int* arr,int n);
//计数排序
void CountSort(init* arr, int n);



#endif //__SORT_H__
