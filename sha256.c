#include<stdio.h>
#include<string.h>
#include <stdlib.h>


char *decimalToBinary(int decimal, int bits){
    int cursor = bits;
    char *binary = malloc(bits+1);
    if(binary == NULL)
        exit(1);
    // for (int i = 0; i < bits;i++){
    //     *binary ='5';
    //     binary++;
    // }
    //binary += bits;
    //*binary = '\0';
    *(binary+cursor) = '\0';
    
    //while(decimal > 0){
    while(cursor){
        --cursor;
        *(binary+cursor) = decimal % 2 + '0';
        decimal /= 2;
    }
    // if(decimal == 0){
    //     --binary;
    //     *binary = '0';
    // }
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
// *binary++ = ' ';
        ++text;
        octet -= 8;

    }
    //*binary = '\0';
    binary -= binaryLength;
    free(octet);
}


int main(){
    char *msg_bin,  msg_str[32] = "pa ss\n";
    char ch = 'a';
    
    int msg_len, msg_bin_len;

    // for(int i=0; msg_str[i]!='\0'; i++)
    //     msg_len++;
    msg_len = strlen(msg_str);
    msg_bin_len = msg_len * 8;
    msg_bin = malloc(msg_bin_len);
    if (msg_bin == NULL)
        return 0;

    // textToBinary(msg_str, msg_len, msg_bin, msg_bin_len);




    // int bin = 0b110;
    // int ascii = (int)ch;
    // printf("%d", ascii);
    // printf("Your binary encoding is:\n%s\n", msg_bin);

    char *out = malloc(8);
    out = decimalToBinary('a',8);
    printf("%s", out);
}