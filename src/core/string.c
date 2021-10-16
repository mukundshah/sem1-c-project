// #include <stdio.h>
// #include <stdlib.h>

// char **stringArr(char *text){
//     char **strings = (char **)calloc(2, sizeof(char *));
//     for(int i=0; i<3; i++){
//         *(strings + i) = text;
//         //*(*(strings + i) + 5) = '\0';
//     }
//     return strings;
// }

// int main(){
//     char text[5] = "abcd";
//     char **stringsArrRecived = stringArr(text);
//     for(int i=0; i<3; i++)
//         printf("%s\n", *(stringsArrRecived + i));
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers/sha256/sha256.h"

// char *truncString(char *str, int pos)
// {
//     size_t len = strlen(str);

//     if (len > abs(pos)) {
//         if (pos > 0)
//             str = str + pos;
//         else
//             str[len + pos] = 0;
//     }

//     return str;
// }

// int main(void) {

//     char *str1 = "the string to be truncated";

//     printf("%s\n", str1);
//     printf("%s \n", truncString(strdupa(str1), 4));
//     printf("%s \n", truncString(strdupa(str1), -4));

//    // exit(EXIT_SUCCESS);
// }


int main(){
    printf("Here\n");
     char msg_str[5] = "abc";
//      char main[600] = "11111111111111111111111111111111111111100000000000000001111111111111111000001000000001010111111111010111111111101011111111111111111111111111111111111111111111111111111111111100000000000000001111111111111111000001000000001010111111111010111111111101011111111111111111111111111111111111111111111111111111111111100000000000000001111111111111111000001000000001010111111111010111111111101011111111111111111111111111111111111111111111111111110000000000000000111111111111111100000100000000101011111111101011111111110101";
//     char *out = ( char *)calloc(64, sizeof( char));
//    sliceString(main, out, 0, 512);
//     // char *out = decimalToHex(409496729, 8);
//     printf("%s\n", out);


    //sliceString(main, out,32, 63);
     char *str = sha256(msg_str);
    printf("%s\n", str);
    //printf("Here");
    //printf("%s\n", out);
    return 0;
}