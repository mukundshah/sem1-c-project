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
void bin64(int dec, char *binary, int binaryLength){
    char *octoctet = malloc(64);
    if(octoctet == NULL)
        exit(1);
    
        octoctet = decimalToBinary(dec, 64);
        while(*octoctet)
            *binary++ = *octoctet++;
        
        octoctet -= 64;
    
    *binary = '\0';
    binary -= binaryLength;
    free(octoctet);
}

void padMessage(char *msg, char *msg_bin){
    //char *msg_bin;
    int msg_len = strlen(msg);
    int msg_bin_len = msg_len * 8;
    msg_bin = malloc(msg_bin_len);
    if (msg_bin == NULL)
        exit(1);

    textToBinary(msg, msg_len, msg_bin, msg_bin_len);
    

    msg_bin = realloc(msg_bin, msg_bin_len+1);
    *(msg_bin + (msg_bin_len)) = '1';
    *(msg_bin + (msg_bin_len+1)) = '\0';
    
    msg_bin_len = strlen(msg_bin);
    printf("%d\n", msg_bin_len);
    printf("Your binary encoding is:\n%s\n", msg_bin);
    int padding = 448 - msg_bin_len % 512;
    msg_bin = realloc(msg_bin, msg_bin_len+padding);
    for (int i = msg_bin_len; i < padding; i++)
    {
        *(msg_bin + i) = '0';
    }
    *(msg_bin + (msg_bin_len+padding)) = '\0';
    msg_bin_len = strlen(msg_bin);
    printf("%d\n", msg_bin_len);
    printf("Your binary encoding is (initial):\n%s\n", msg_bin);

    char *size = malloc(64);
    size = decimalToBinary(24, 64);

    msg_bin = realloc(msg_bin, msg_bin_len+64);
    while(*size)
            *msg_bin++ = *size++;
    *msg_bin = '\0';
    // bin64(24, msg_bin, msg_bin_len+padding+64);
    // *(msg_bin + (msg_bin_len+padding)) = '\0';
    msg_bin_len = strlen(msg_bin);
    printf("%d\n", msg_bin_len);
    printf("Your binary encoding is (last):\n%s", msg_bin);
    //printf("%s", size);
    
}


int main(){
    char *msg_bin,  msg_str[32] = "abc";
    char ch = 'a';
    
    int msg_len, msg_bin_len;

    msg_len = strlen(msg_str);
    msg_bin_len = msg_len * 8;
    // msg_bin = malloc(msg_bin_len);
    // if (msg_bin == NULL)
    //     return 0;

    //textToBinary(msg_str, msg_len, msg_bin, msg_bin_len);
    padMessage(msg_str, msg_bin);
    //printf("Your binary encoding is:\n%s\n", msg_bin);

}