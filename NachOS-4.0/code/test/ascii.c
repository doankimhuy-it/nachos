/* ascii.c
 * In ra cac ky tu thuoc bang ma ascii, chi in cac ky tu in duoc
 */

#include "syscall.h"

int main() {
    char* tab = "\t";
    char* newline = "\n";
    int i = 0;
    for (i = 33; i < 128; ++i) {
        PrintNum(i);
        PrintString(tab);
        PrintChar((char)i);
        PrintString(newline);
    }

    Halt();
    /* not reached */
}
