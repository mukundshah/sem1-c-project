// ! Works on OnlineGDB, but not on Windows machine.

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define BIT32 4294967295

typedef unsigned int uint32;

// ---------
// Extras
// ---------

// Slice string at between a range.
char *strslice(char *str, int start, int end){
    int length = end - start + 1;
    char *slice = (char *)malloc(length);
    int j =0;
    for (int i = start; i <= end; i++)
        slice[j++] = str[i];
    slice[j] = '\0';
    return slice;
    
}


// ---------
// Converters
// ---------

// Convert integer to binary string.
char *decimalToBinary(uint32 decimal, int bits){
    int cursor = bits;
    char *binary = (char *)malloc(bits+1);
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
    char *byte = (char *)malloc(bits);
    char *binary = (char *)malloc(binaryLength);
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
char *decimalToHex(uint32 decimal, int len){
    int cursor = len;
    char *hex = (char *)malloc(len+1);
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

// Convert binary string to base-10 int
uint32 binaryToDecimal(char *binary){
    int bits = strlen(binary);
    uint32 base10 = 0;
        for(int i = bits-1; i >= 0; --i)
        if(binary[i] == 49)
            base10 += pow(2, (bits - 1) - i);
    return base10;
}

// ----------
// Operations
// ----------

// Addition (also, truncate to 32 bits)
uint32 add(int argc,...){
    va_list args;
    uint32 total = 0;
    va_start(args, argc);
    for (int i = 0; i < argc; i++)
        total += va_arg(args, int);
    va_end(args);
    return (total % BIT32);
}

// Rotate right by n-bit (circular right shift)
uint32 rotr(int n, int x){
    uint32 right    = x >> n;
    uint32 left     = x << 32 - n;
    uint32 result   = right | left;
    return (result & BIT32);
}

// Shift right by n-bit
uint32 shr(int n, int x){
    uint32 result = x >> n;
    return result;
}

// ---------
// Functions - Combined rotations and shifts using operations above
// ---------

// σ0
uint32 sigma0(uint32 x){
    return rotr(7, x) ^ rotr(18, x) ^ shr(3, x);
}

// σ1
uint32 sigma1(uint32 x){
    return rotr(17, x) ^ rotr(19, x) ^ shr(10, x);
}

// Σ0 (uppercase sigma)
uint32 usigma0(uint32 x){
    return rotr(2, x) ^ rotr(13, x) ^ rotr(22, x);
}

// Σ1 (uppercase sigma)
uint32 usigma1(uint32 x){
    return rotr(6, x) ^ rotr(11, x) ^ rotr(25, x);
}

// Choice - Use first bit to choose the second or third bit.
// 1 → Second bit
// 0 → Third bit
uint32 ch(uint32 x, uint32 y, uint32 z){
    return (x & y) ^ (~x & z);
}

// Majority - Result is the majority of the three bits.
uint32 maj(uint32 x, uint32 y, uint32 z){
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
    char *size = decimalToBinary(len, 64);

    char *padded_message = (char *)malloc(total_length);

    strcat(padded_message, bin_msg);
    strcat(padded_message, "1");
    for (int i = 0; i < padding; i++) strcat(padded_message, "0");
    strcat(padded_message, size);
    *(padded_message + total_length) = '\0';

    free(size);
    return padded_message;
}

// -----------
// Message Blocks
// -----------

// Cut padded message into 512-bit blocks
char **createBlocks(char *message, int block_size, int *block_count){
    int msg_len = strlen(message);
    *block_count = msg_len / block_size;
    char **blocks = (char **)malloc(sizeof(char *) * *block_count);
    for (int i = 0; i < *block_count; i++)
        *(blocks + i) = strslice(message, block_size * i, (block_size * (i + 1)) - 1);
    return blocks;
}

// -----------
// Message Schedules
// -----------

// Cut each message block into 32-bit schedules and calculate all 64 words from the message block.

uint32 *calculateSchedules(char *block){
    uint32 *slice = (uint32 *)malloc(sizeof(uint32)*64);
    for (int i = 0; i < 16; i++)
        slice[i] = binaryToDecimal(strslice(block, 32 * i, (32 * (i + 1)) - 1));
    for (int i = 16; i < 64; i++)
        slice[i] = add(4, sigma1(slice[i-2]), slice[i-7], sigma0(slice[i-15]), slice[i-16]);
    return slice;
}

// ---------
// Constants
// ---------

const int PRIMES[64] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
            89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
            181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
            281, 283, 293, 307, 311};

// Constants (K) = Cube roots of the first 64 prime numbers (first 32 bits of the fractional part)
uint32 *K(){
    uint32 *arr = (uint32 *)malloc(sizeof(uint32)*64);
    for (int i = 0; i < 64; i++){
        double cb_root = pow(PRIMES[i], (1 / 3.0));
        arr[i] = (uint32)((cb_root - floor(cb_root)) * pow(2, 32));
    }
    return arr;
}

// Initial Hash Values (IHV) = Square roots of the first 8 prime numbers (first 32 bits of the fractional part)
uint32 *IHV(){
    uint32 *arr = (uint32 *)malloc(sizeof(uint32)*8);
    for (int i = 0; i < 8; i++)
    {
        double sq_root = pow(PRIMES[i], (1 / 2.0));
        arr[i] = (uint32)((sq_root - floor(sq_root)) * pow(2, 32));
    }
    return arr;
}

// ----------
// Compression
// ----------

uint32 *compression(uint32 *initial, uint32 *schedule, uint32 *constants){
    uint32 a = initial[0],
        b = initial[1],
        c = initial[2],
        d = initial[3],
        e = initial[4],
        f = initial[5],
        g = initial[6],
        h = initial[7];

    for (int i = 0; i < 64; i++){
        uint32 t1 = add(4, schedule[i], constants[i], usigma1(e), ch(e, f, g));
        uint32 t2 = add(2, usigma0(a), maj(a, b, c));

        h = g;
        g = f;
        f = e;
        e = add(2, d, t1);
        d = c;
        c = b;
        b = a;
        a = add(2, t1, t2);
    }

    uint32 *hash = (uint32 *)malloc(sizeof(uint32)*8);
    hash[7] = add(2, initial[7], h);
    hash[6] = add(2, initial[6], g);
    hash[5] = add(2, initial[5], f);
    hash[4] = add(2, initial[4], e);
    hash[3] = add(2, initial[3], d);
    hash[2] = add(2, initial[2], c);
    hash[1] = add(2, initial[1], b);
    hash[0] = add(2, initial[0], a);

    return hash;
}

char *sha256(char *message){
    char *bin_msg = textToBinary(message);
    char *padded_msg = paddingMessage(bin_msg);
    
    int block_count;
    char **blocks = createBlocks(padded_msg, 512, &block_count);
    
    uint32 *constants = K();
    uint32 *hash = IHV();
    uint32 *initial;

    for(int i=0; i<block_count; i++){
        uint32 *schedule = calculateSchedules(*(blocks+i));
        initial = hash;
        hash = compression(initial, schedule, constants);
    }
    
    char *sha256_hash = (char *)malloc(64);
    for (int i = 0;i<8;i++)
        strcat(sha256_hash, decimalToHex(*(hash + i), 8));
    free(hash);
    free(initial);
    free(padded_msg);
    free(blocks);
    return sha256_hash;
}

int main(){
    char msg_str[100] = "abjdhjfhc";
    char *str = sha256(msg_str);
    printf("%s", str);
    return 0;
}

//abc: 3dc6c922a81854e7963c4dbe4bc72c3da2731f3adb28283b8877ef4457804078
//abd: 9846cf86a328668a08c655fbf74b5f2ff203da86731d1f9649fe5dffc9db4f4a
//     9846cf86a328668a08c655fbf74b5f2ff203da86731d1f9649fe5dffc9db4f4a

// Let n is stored using 8 bits. Left rotation of n = 11100101 by 3 makes n = 00101111
// b3def9a16d6f39a2da00207ac66730711dc26493f31978901b6cc8561284da9a
