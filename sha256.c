#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define BIT32 4294967295

// ---------
// Extras
// ---------

// Slice string at between a range.
char *strslice(char *str, int start, int end){
    int length = end - start + 1;
    char *slice = malloc(length);
    int j =0;
    for (size_t i = start; i <= end; i++)
        slice[j++] = str[i];
    slice[j] = '\0';
    return slice;
}


// ---------
// Converters
// ---------

// Convert integer to binary string.
char *decimalToBinary(int decimal, int bits){
    int cursor = bits;
    char *binary = malloc(bits+1);
    if(binary == NULL) exit(1);
    *(binary+cursor) = '\0';
    while(cursor){
        --cursor;
        *(binary+cursor) = decimal % 2 + '0';
        decimal /= 2;
    }
    return binary;
}

// Convert string to binary string
char *textToBinary(char *text){
    int bits = 8, binaryLength = strlen(text) * bits;
    char *byte = malloc(bits);
    char *binary = malloc(binaryLength);
    if(byte == NULL || binary == NULL)
        exit(1);
    while(*text){
        byte = decimalToBinary(*text, 8);
        while(*byte)
            *binary++ = *byte++;
        ++text;
        byte -= 8;
    }
    *binary = '\0';
    binary -= binaryLength;
    free(byte);
    return binary;
}

// Convert integer to hexadecimal string (32 bits)
char *decimalToHex(int decimal, int len){
    int cursor = len;
    char *hex = malloc(len+1);
    if(hex == NULL) exit(1);
    *(hex+cursor) = '\0';
    while(cursor){
        --cursor;
        int rem = decimal % 16;
        if(rem<10)
            *(hex+cursor) = rem + '0';
        else if (rem >= 10){
            if (rem == 10) *(hex+cursor) = 'a';
            if (rem == 11) *(hex+cursor) = 'b';
            if (rem == 12) *(hex+cursor) = 'c';
            if (rem == 13) *(hex+cursor) = 'd';
            if (rem == 14) *(hex+cursor) = 'e';
            if (rem == 15) *(hex+cursor) = 'f';
        }
        decimal /= 16;
    }
    return hex;
}


// ----------
// Operations
// ----------

// Addition (also, truncate to 32 bits)
int add(int argc,...){
    va_list valist;
    int total = 0;
    va_start(valist, argc);
    for (int i = 0; i < argc; i++)
        total += va_arg(va_list, int);
    va_end(valist);
    return (total % BIT32);
}

// Rotate right (circular right shift)
int rotr(int n, int x){
    int right = x >> n;
    int left = x << 32 - n;
    int result = right | left;
    return (result & BIT32);
}

// Shift right
int shr(int n, int x){
    int result = x >> n;
    return result;
}

// ---------
// Functions - Combined rotations and shifts using operations above
// ---------

// σ0
int sigma0(int x){
    return rotr(7, x) ^ rotr(18, x) ^ shr(3, x);
}

// σ1
int sigma1(int x){
    return rotr(17, x) ^ rotr(19, x) ^ shr(10, x);
}

// Σ0 (uppercase sigma)
int usigma0(int x){
    return rotr(2, x) ^ rotr(13, x) ^ rotr(22, x);
}

// Σ1 (uppercase sigma)
int usigma1(int x){
    return rotr(6, x) ^ rotr(11, x) ^ rotr(25, x);
}

// Choice - Use first bit to choose the second or third bit.
// 1 → Second bit
// 0 → Third bit
int ch(int x, int y, int z){
    return (x & y) ^ (~x & z);
}

// Majority - Result is the majority of the three bits.
int maj(int x, int y, int z){
    return (x & y) ^ (x & z) ^ (y & z);
}


// -------------
// Preprocessing
// -------------

// Pad binary string message to multiple of 512 bits.
char *paddingMessage(char *bin_msg){
    int len = strlen(bin_msg);
    int padding = 447 - (len % 512);
    int total_length = len + 1 + padding + 64;
    // char *size = malloc(64);
    // size = decimalToBinary(msg_bin_len, 64);
    char *size = decimalToBinary(len, 64);
    char *padded_message = malloc(total_length);
    strcat(padded_message, bin_msg);
    strcat(padded_message, '1');
    for (size_t i = 0; i < padding; i++)
        strcat(padded_message, '0');
    strcat(padded_message, size);
    free(size);
    return padded_message;
}

// -----------
// Message Blocks
// -----------

// Cut padded message into 512-bit blocks

// -----------
// Message Schedules
// -----------

// Cut each message block into 32-bit schedules and calculate all 64 words from the message block.

// ---------
// Constants
// ---------
// Constants = Cube roots of the first 64 prime numbers (first 32 bits of the fractional part)

int K[64] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
            89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
            181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
            281, 283, 293, 307, 311};

// Initial Hash Values = Square roots of the first 8 prime numbers (first 32 bits of the fractional part)

int IHV[8] = {2, 3, 5, 7, 11, 13, 17, 19};

// ----------
// Compression
// ----------

int compression(int *initial, int *schedule, int *constants){
    int a = initial[0],
        b = initial[1],
        c = initial[2],
        d = initial[3],
        e = initial[4],
        f = initial[5],
        g = initial[6],
        h = initial[7];

    for (size_t i = 0; i < 64; i++){
        int t1 = add(4, schedule[i], constants[i], usigma1(e), ch(e, f, g));
        int t2 = add(2, usigma0(a), maj(a, b, c));

        a = add(2, t1, t2),
        b = a, c = b, d = c, e = add(2, d, t1), f = e, g = f, h = g;
    }
    
    

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

    textToBinary(msg);
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
