#include <stdio.h>
#include <stdlib.h>

int get_mountain_num(int * arry,int arry_size)
{
    int result = 0;
    int i = 0;
    while (1){
        if(i >= arry_size){
            return result;
        } else {
            if(i == 0){
                if(arry[i+1] < arry[i]){
                    result++;
                } 
            }
            if(i == arry_size -1){
                if(arry[i-1] < arry[i]){
                    result++;
                }
            } else {
                if((arry[i-1] < arry[i]) && (arry[i+1] < arry[i])){
                    result++;
                }
            }
        }
        i++;
    }
    
}

int main()
{
    int arry[6] = {1, 3, 2, 4, 3, 5};
    printf("mountain num is %d\n", get_mountain_num(arry, 6));
    return 0;
}