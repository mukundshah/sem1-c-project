#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



void strslice(char *str_in, char *str_out, int start, int end){
    int j =0;
    for (size_t i = start; i <= end; i++)
        str_out[j++] = str_in[i];
    str_out[j] = '\0';
}

char *decimalToBinary(int decimal, int bits){
    int cursor = bits;
    char *binary = malloc(bits+1);
    if(binary == NULL)
        exit(1);
    
    *(binary+cursor) = '\0';
    
    while(cursor){
        --cursor;
        *(binary+cursor) = decimal % 2 + '0';
        decimal /= 2;
    }

    return binary;
}

int binaryToDecimal(char *bin, int bits){
    int position = bits-1;
    int decimal = 0;
    for (size_t i = 0; i < bits; i++)
    {
        decimal += atoi(bin) * pow(2, position);
        --position;
    }
    
    // if(binary == NULL)
    //     exit(1);
    
    // *(binary+cursor) = '\0';
    
    // while(cursor){
    //     --cursor;
    //     *(binary+cursor) = decimal % 2 + '0';
    //     decimal /= 2;
    // }

    return decimal;
}

void textToBinary(char *text, int textlength, char *binary, int binaryLength){
    char *octet = malloc(8);
    if(octet == NULL)
        exit(1);
    while(*text){
        octet = decimalToBinary(*text, 8);
        while(*octet)
            *binary++ = *octet++;
        ++text;
        octet -= 8;
    }
    *binary = '\0';
    binary -= binaryLength;
    free(octet);
}



void padMessage(char *msg, char *msg_bin){
    //char *msg_bin;
    int cursor = 0;
    int msg_len = strlen(msg);
    int msg_bin_len = msg_len * 8;
    msg_bin = malloc(msg_bin_len);
    if (msg_bin == NULL)
        exit(1);
    char *size = malloc(64);
    size = decimalToBinary(msg_bin_len, 64);

    textToBinary(msg, msg_len, msg_bin, msg_bin_len);
    cursor += msg_bin_len;

    int padding = 512-(msg_bin_len % 512);
    int total_len = msg_bin_len + padding;
    printf("%d\t%d\t%d\n", msg_bin_len, padding, total_len);

    msg_bin = realloc(msg_bin, total_len);
    *(msg_bin + cursor) = '1';
    
    
    
    
    for (cursor += 1; cursor < total_len; cursor++){
        *(msg_bin + cursor) = '0';
        if((total_len-cursor)<=64)
            *(msg_bin + cursor) = *size++;
    }

    *(msg_bin + total_len) = '\0';
    
    msg_bin_len = strlen(msg_bin);
    printf("%d\n", msg_bin_len);
    printf("Your binary encoding is (last):\n%s\n", msg_bin);

    int block_count = msg_bin_len / 512;
    int schedule_count = block_count * 16;

    //char **blocks = malloc(block_count);
    // printf("%s", size);
    // char *sch = malloc(32);
    char **schedules = (char **)malloc(sizeof(char *)*schedule_count);

    // char *schedules[total_msg_schedules];
    for (int i = 0; i < schedule_count; ++i)
    {
    //int i = 1;
    schedules[i] = (char *)malloc(sizeof(char) * 32);
    int j = 0;
    for (size_t k = 32 * i; k <= (32 * (i + 1)) - 1; k++)
        schedules[i][j++] = msg_bin[k];
    schedules[i][j] = '\0';
    //strslice(msg_bin, schedules[i], 32*i, (32*(i+1))-1);
    printf("%d: (%d)\t%s\n", i, &schedules[i], schedules[i]);
    }
    // i = 2;
    // schedules[i] = (char *)malloc(sizeof(char) * 32);
    // j = 0;
    // for (size_t k = 32 * i; k <= (32 * (i + 1)) - 1; k++)
    //     schedules[i][j++] = msg_bin[k];
    // schedules[i][j] = '\0';
    // //strslice(msg_bin, schedules[i], 32*i, (32*(i+1))-1);
    // printf("%d: (%d) %s\n", i, &schedules[i], schedules[i]);
    // //}
    
    
}


int main(){
    char *msg_bin,  msg_str[1000] = "abcdef";
    char ch = 'a';
    
    int msg_len, msg_bin_len;

    msg_len = strlen(msg_str);
    msg_bin_len = msg_len * 8;
    msg_bin = malloc(1024);
    padMessage(msg_str, msg_bin);
    // printf("Your binary encoding is (last):\n%s\n", msg_bin);

    return 0;
}
