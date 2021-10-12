/* add.c
 *	Simple program to test whether the systemcall interface works.
 */

#include "syscall.h"

int main()
{
    int result;

    result = ReadNum();

    Halt();
    /* not reached */
}