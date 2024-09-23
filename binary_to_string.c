#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void binary_to_hexstring(int binary)
{
    char str[10] = {0};
    sprintf(str, "%x", binary);
    printf("binary_to_hexstring is %s\n", str);
}

void binaryfile_to_hexstring(char* file_name)
{
    FILE *file = NULL;
    char* buffer = NULL;
    char* hex_buffer = NULL;
    int file_size = 0;
    int i = 0;

    if(file_name == NULL){
        printf("file can not be null\n");
        return;
    }

    if((file = fopen(file_name, "rb+")) == NULL){
        printf("fail to open the file\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if((buffer = (char*)malloc(sizeof(char) * file_size)) == NULL){
        printf("fail to malloc\n");
        goto ERROR;
    }

    if((hex_buffer = (char*)malloc(sizeof(char) * 2 * file_size + 1)) == NULL){
        printf("fail to malloc\n");
        goto ERROR;
    }

    printf("binaryfile_to_hexstring:");
    if((fread(buffer, 1, file_size, file)) != file_size){
        printf("fail to read\n");
        goto ERROR;
    }

    for(i = 0; i < file_size; i++){
        sprintf(hex_buffer + i * 2, "%02x", (unsigned char)buffer[i]);
    }
    hex_buffer[2 * file_size] = '\0';
    printf("%s\n", hex_buffer);

ERROR:
    if(buffer){
        free(buffer);
    }
    if(hex_buffer){
        free(hex_buffer);
    }
    fclose(file);
}

void binary_to_binarystring(int binary)
{
    char str[10] = {0};
    char temp = {0};
    int index = 0;
    int i =0;

    if(binary == 0){
        str[0] = '0';
        printf("binary_to_binarystring is %s\n", str);
        return;
    }

    while(binary > 0){
        str[index] = (binary % 2) + '0'; 
        binary = binary / 2;
        index++;
    }

    str[index] = '\0';

    for(i = 0; i < index /2; i++){
        char temp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = temp;
    }

    printf("binary_to_binarystring is %s\n", str);
}

void binary_to_ascii(int binary)
{
    int i = 0;
    int decimal = 0;
    int last_num = 0;
    char ascii_char = '0';

    while(binary > 0){
        last_num = binary % 2;
        binary = binary / 2;
        decimal += last_num * pow(2, i);
        i++;
    }
   
    ascii_char = (char) decimal;
    printf("binary_to_ascii is %c\n", ascii_char);    
}

int main(int argc, char* argv[])
{
    int binary = 0;

    binary = 0b01000001; //二进制数
    binaryfile_to_hexstring(argv[1]);
    binary_to_hexstring(binary);
    binary_to_binarystring(binary);
    binary_to_ascii(binary); //终端仅能打印出部分ASCII码
}