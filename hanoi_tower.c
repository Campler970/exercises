#include <stdio.h>

#define FROM_TOWER 'A' 
#define TO_TOWER 'B'
#define AUX_TOWER 'C'

int count = 0;

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("move disk 1 from %c to %c\n", from, to);
        count++;
        return;
    }
    hanoi(n - 1, from, aux, to);
    printf("move disk %d from %c to %c\n", n, from, to);
    count++;
    hanoi(n - 1, aux, to, from);
}

int main()
{
    int plate_num = 0;

    plate_num = 7;
    hanoi(plate_num, FROM_TOWER, TO_TOWER, AUX_TOWER);
    printf("move count is %d \n", count);
}