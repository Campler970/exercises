#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
enum Status
{
    VALID,
    INVALID
};

enum Status status = INVALID;

int my_atoi(char *str)
{
    int flag = 1; //数字正负标志
    int ret = 0;

    if (str == NULL) {
        printf ("str can not be null\n");
        return 0;
    }

    if(*str == '\0'){
        printf("str can not be space\n");
        return 0;
    }

    while (isspace(*str)){
        str ++;
    }

    if (*str == '+'){
        str ++;
    } else if (*str == '-'){
        flag = -1;
        str ++;
    }

    while (isdigit(*str)){
        ret = ret * 10 + flag * (*str - '0'); //将数字字符转换为整数
        str ++;
    }

    if (*str == '\0'){
        status = VALID;
        return ret;
    } else {
        printf("qq");
        return 0;
    } 
}

int main()
{
    char input[20] = {0};
    scanf ("%s", input);
    int ret = my_atoi(input);
    if (status == VALID){
        printf("transform is %d\n", ret);
    } else {
        printf("fail to transform\n");
    }
    
    return 0;
}