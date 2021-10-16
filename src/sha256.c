// ! Works on OnlineGDB and Linux, but not on Windows machine.

//#include "sha256.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sha256.h>

#define BIT32 4294967295
#define SHA256_BLOCK_SIZE 512

#define ROTRIGHT(x,n) (((x) >> (n)) | ((x) << (32-(n))))
#define SHR(x,n) ((x) >> n)

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
#define USIG0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define USIG1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))



typedef unsigned int uint32;
typedef unsigned int WORD;
typedef unsigned char BYTE;

WORD K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

WORD IHV[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};


// ---------
// Utils
// ---------
void sliceString(char *str_in, char *str_out, int start, int end){
    int j =0;
    for (int i = start; i <= end; i++)
        str_out[j++] = str_in[i];
    str_out[j] = '\0';
}

// Addition (also, truncate to 32 bits)
uint32 add(int argc,...){
    va_list args;
    uint32 total = 0;
    va_start(args, argc);
    for (int i = 0; i < argc; i++)
        total += va_arg(args, int);
    va_end(args);
    return (total % (uint32)BIT32);
}

// ---------
// Converters
// ---------

// Convert integer to binary string.
 char *decimalToBinary(uint32 decimal, int bits){
    int cursor = bits;
     char *binary = ( char *)calloc(bits+1, sizeof( char));
    if(!binary) exit(1);
    *(binary+cursor) = '\0';
    while(cursor){
        --cursor;
        *(binary+cursor) = decimal % 2 + '0';
        decimal /= 2;
    }
    return binary;
}

// Convert string to binary string
 char *textToBinary( char *text){
    int bits = 8, binaryLength = strlen(text) * bits;
     char *byte = ( char *)calloc(bits, sizeof( char));
     char *binary = ( char *)calloc(binaryLength, sizeof( char));
    if(!byte || !binary) exit(1);
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

// Convert integer to 32-bit hexadecimal string.
char *decimalToHex(uint32 decimal){
    static char hex[8];
    sprintf(hex, "%08x", decimal);
    return hex;
}

// Convert binary string to base-10 int
uint32 binaryToDecimal( char *binary){
    int bits = strlen(binary);
    uint32 base10 = 0;
        for(int i = bits-1; i >= 0; --i)
        if(binary[i] == 49)
            base10 += pow(2, (bits - 1) - i);
    return base10;
}


// -------------
// Preprocessing
// -------------

// Pad binary string message to multiple of 512 bits.
 char *paddingMessage( char *bin_msg){
    int len                 = strlen(bin_msg);
    int padding             = 447 - (len % 512);
    int total_length        = len + 1 + padding + 64;
    char *size              = decimalToBinary(len, 64);
    char *padded_message    = ( char *)calloc(total_length, sizeof( char));

    strcat(padded_message, bin_msg);
    strcat(padded_message, "1");
    for (int i = 0; i < padding; i++) strcat(padded_message, "0");
    strcat(padded_message, size);

    free(size);
    return padded_message;
}

// -----------
// Message Schedules
// -----------

// Cut each message block into 32-bit schedules and calculate all 64 words from the message block.

uint32 *calculateSchedules( char *block){
    uint32 *slice = (uint32 *)calloc(64,sizeof(uint32));
     char *str = ( char *)calloc(32, sizeof( char));
    for (int i = 0; i < 16; i++){
        sliceString(block, str, 32 * i, (32 * (i + 1)) - 1);
        slice[i] = binaryToDecimal(str);
    }
    for (int i = 16; i < 64; i++)
        slice[i] = add(4, SIG1(slice[i-2]), slice[i-7], SIG0(slice[i-15]), slice[i-16]);
    return slice;
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
        uint32 t1 = add(4, schedule[i], constants[i], USIG1(e), CH(e, f, g));
        uint32 t2 = add(2, USIG0(a), MAJ(a, b, c));

        h = g;
        g = f;
        f = e;
        e = add(2, d, t1);
        d = c;
        c = b;
        b = a;
        a = add(2, t1, t2);
    }

    uint32 *hash = (uint32 *)calloc(8, sizeof(uint32));
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
    char *bin_msg       = textToBinary(message);
    char *padded_msg    = paddingMessage(bin_msg);

    int block_count     = strlen(padded_msg) / SHA256_BLOCK_SIZE;
    uint32 *constants   = K;
    uint32 *hash        = IHV;
    uint32 *initial;

    char block512[SHA256_BLOCK_SIZE];
    for(int i=0; i<block_count; i++){
        initial = hash;
        sliceString(padded_msg, block512, SHA256_BLOCK_SIZE * i, ((SHA256_BLOCK_SIZE * (i + 1)) - 1));
        uint32 *schedule = calculateSchedules(block512);
        hash = compression(initial, schedule, constants);
    }

    static char sha256_hash[64] = {'\0'};
    for (int i = 0;i<8;i++)
        strcat(sha256_hash, decimalToHex(*(hash + i)));
    
    return sha256_hash;
}
