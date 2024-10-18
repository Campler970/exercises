#include <stdio.h>

void bubble_sort(int arry[], int n)
{
    int i = 0, j = 0, temp = 0;

    for(i = 0; i < n; i++){
        for(j = 0; j < n - i -1; j++){
            if(arry[i] > arry[i + 1]){
                temp = arry[i];
                arry[i] = arry[i + 1];
                arry[i + 1] = temp;
            }
        }
    }
}

void select_sort(int arry[], int size)
{
    int i = 0, j = 0, min_index = 0, temp = 0;

    for (i = 0; i < size - 1; i++) {
        min_index = i;
        for (j = i+1; j < size; j++) {
            if (arry[j] < arry[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = arry[i];
            arry[i] = arry[min_index];
            arry[min_index] = temp;
        }
    }
}

int quick_sort_partition(int arry[], int low, int high)
{
    int pivot = 0, i = 0, j = 0, temp = 0, position = 0;

    i = low - 1;
    pivot = arry[high]; // 将最后一个元素做为基准值
    for (j = low; j < high; j++) {
        if (arry[j] < pivot) {
            i++;
            temp = arry[i];  // 若有小于基准值元素，将其放在左侧
            arry[i] = arry[j];
            arry[j] = temp;
        }
    }

    temp = arry[high];  // 将基准值放在小于基准值元素的后面
    arry[high] = arry[i+1];
    arry[i+1] = temp;
    
    position = i+1; // 基准值的索引
    return position;
}

void quick_sort(int arry[], int low, int high)
{
    int position = 0;
    
    if (low < high){
        position = quick_sort_partition(arry, low, high);

        // 递归排序基准值左侧和右侧的元素
        quick_sort(arry, low, position-1);
        quick_sort(arry, position+1, high);
    }  
}

void insert_sort(int arry[], int size)
{
    int i = 0, j = 0, key = 0;

    for (i = 1; i < size; i++) {
        key = arry[i];
        j = i - 1;
        while (j >= 0 && arry[j] > key) {
            arry[j+1] = arry[j];
            j--;
        }

        arry[j+1] = key;
    }
}

int main()
{
    int arry[5] = {1, 3, 2, 5, 4};
    int n = 0;
    int i = 0;

    n = sizeof(arry) / sizeof(arry[0]);
    //bubble_sort(arry, n);
    select_sort(arry, n);
    for (i = 0; i < n; i++){
        printf("%2d", arry[i]);
    }
    return 0;
}