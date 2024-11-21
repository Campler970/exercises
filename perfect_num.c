#include <stdio.h>

#define MAX_NUM 1000

int is_perfect_num(int n)
{
    int sum = 0;
    int i = 0;

    for (i = 0; i < n /2 ;i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum == n;
}

int main()
{
    int i = 0;

    for ( i = 1; i < MAX_NUM; i++) {
        if(is_perfect_num(i)) {
            printf("%d \n", i);
        }
    }
      
    return 0;
}