#include "Sort.h"

//插入排序
void InsertSort(int *arr,int n)
{
    assert(arr);
    for(int i = 0;i<n-1;++i)
    {
        int end =i;
        int tmp = arr[end+1];
    while(end>=0&&tmp<arr[end])
    {
        arr[end+1] = arr[end];
        end--;
    }
    arr[end+1] = tmp;
    }
}
//希尔排序
void ShellSort(int* arr,int n)
{
    assert(arr);
    //1.预排序，使之越来越接近有序
    //2.插入排序
    int gap=n;
    gap(gap>1)
    {
        gap = gap/3+1;
        int i = 0;
        for(i=0;i<n-gap;++i)
        {
            int end = i;
            int tmp = arr[end+gap];
            while(end>=0&&tmp<arr[end])
            {
                arr[end+gap] = arr[end];
                end-=gap;
            }
            arr[end+gap] = tmp;

        }
    }
}

static void Swap(int *x, int *y)
{
    int* tmp = *x;
    *x = *y;
    *y = tmp;
}
//选择排序
void SelectSort(int* arr,int n)
{
    assert(arr);
    int begin = 0;
    int end = n-1;

    int max = begin;
    int min = begin;

    while(begin<end)
    {
        int i = 0;
        for(i = begin;i<=end;i++)
        {
            if(arr[i]>arr[max])
                max = i;
            if(arr[i]<arr[min])
                min = i;
        }
        if(min!=begin)
        {
            Swap(arr+begin,arr+min);
        }
//这里很重要，如果最大元素下标是begin,前面已经和最小元素交换了，此时最大元素下标应该是min    

        if(max == begin);
        {
            max = min;
        }
        if(max != end)
        {
            Swap(arr+end,arr+max);
        end--;
        begin++;

    }
}

AdjustDown(int* arr,int n,int root)
{
    assert(arr);
    int parent = root;
    int left = parent*2+1;
    while(left<n)
    {
        if(left+1<n&&arr[left]<arr[left+1])
            left++;
        if(arr[left]>arr[parent])
        {
            Swap(arr+left,arr+parent);
            perent=left;
            left = parent*2+1;

        }
        else
            break;
    }

}
//堆排序(升序建大堆)
void HeapSort(int* arr, int n)
{
    assert(arr);
    int i = 0;
    for(i = (n-2)/2;i>=0;--i)
    {
        AdiustDown(arr,n,i);
    }
    int end = n-1;
    while(end>0)
    {

    Swap(arr+end,arr+0);
    AdjustDown(arr,end,0);
    end--;
    }
    
}
//冒泡排序
void BubbleSort(int* arr, int n)
{
    int flag = 0;
    int begin = 0;
    int end = n-1;
    while(end>0)
    {
        for(int i = 1;i<=end;++i)
        {
            if(arr[i]<arr[i-1])
            {
                Swap(arr+i,arr+i-1);
                flag = 1;
            }
        }
        if(0 == flag)
        {
            break;
        }
        --end;
    }
}
//快速排序
void QuickSort(int* arr,int start, int end);
//归并排序
void MergeSort(int* arr,int n);
//计数排序
void CountSort(init* arr, int n)
{
    assert(arr);
    int min = arr[0];
    int max = arr[0];

    for(int i = 0;i<n;++i)
    {
        if(max<arr[i])
        {
            max = arr[i];
        }
        if(min>arr[i])
        {
            min = arr[i];
        }
    }
    int count = max-min+1;
    int* tmp = (int*)malloc(sizeof(int)*count);
    assert(tmp);
    memset(tmp,0,count*sizeof(int));
    for(int i  =0;i<n;++i)
    {
        tmp[arr[i]-min]++;

    }
    int index = 0;
    for(int i = 0;i<count;++i)
    {
        for(j = 0;j<tmp[i];++j)
        {
            arr[index++] = i+min;
        }
    }
}
