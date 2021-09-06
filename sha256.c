#include<stdio.h>
#include<string.h>
#include <stdlib.h>


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
    printf("%s", size);
    
}


int main(){
    char *msg_bin,  msg_str[1000] = "Oh My Posh comes with many themes included out-of-the-box. Below are some screenshots of the more common themes.";
    char ch = 'a';
    
    int msg_len, msg_bin_len;

    msg_len = strlen(msg_str);
    msg_bin_len = msg_len * 8;

    padMessage(msg_str, msg_bin);

    return 0;
}