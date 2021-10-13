/* sort.c
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

/*
#define UNIX
#define UNIX_DEBUG
*/

#ifdef UNIX
#include <stdio.h>
#define Exit exit
#else
#include "syscall.h"
#endif /* UNIX */

//#define SIZE (1024)

// int A[SIZE];	/* size of physical memory; with code, we'll run out of space!*/

int main() {
    int SIZE;
    int i, j, tmp;
    int A[100];
    char *enterSIZE = "Nhap so luong phan tu <= 100: ";
    char *enterEle = "Nhap so thu ";
    char *ending = ": ";
    char *sortChoice =
        "Vui long chon sap xep tang dan hay giam dan (0: tang dan, 1: giam "
        "dan): ";
    char *newline = "\n";
    char *tab = "\t";
    int choice;
    do  // nhap vao do lon mang, nhap lai neu khong thoa 0 < SIZE <= 100
    {
        PrintString(enterSIZE);
        SIZE = ReadNum();
    } while (SIZE <= 0 || SIZE > 100);

    /* doc mang */
    for (i = 0; i < SIZE; i++) {
        PrintString(enterEle);
        PrintNum(i + 1);
        PrintString(ending);
        A[i] = ReadNum();
    }
    // doc tuy chon sap xep
    PrintString(sortChoice);
    choice = ReadNum();
    PrintString(newline);

    if (choice == 0) /* then sort! */
        for (i = 0; i < (SIZE - 1); i++) {
            for (j = 0; j < (SIZE - i - 1); j++) {
                if (A[j] > A[j + 1]) { /* out of order -> need to swap ! */
                    tmp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = tmp;
                }
            }
        }
    else if (choice == 1)
        /* then sort! */
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < (SIZE - i - 1); j++) {
                if (A[j] < A[j + 1]) { /* out of order -> need to swap ! */
                    tmp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = tmp;
                }
            }
        }
    // in mang
    for (i = 0; i < SIZE; i++) {
        PrintNum(A[i]);
        PrintString(tab);
    }

    Halt();
#ifdef UNIX_DEBUG
    for (i = 0; i < SIZE; i++) {
        printf("%4d ", A[i]);
        if (((i + 1) % 15) == 0) {
            printf("\n");
        }
        if (A[i] != i) {
            fprintf(stderr, "Out of order A[%d] = %d\n", i, A[i]);
            Exit(1);
        }
    }
    printf("\n");
#endif /* UNIX_DEBUG */

    for (i = 0; i < SIZE; i++) {
        if (A[i] != i) {
            Exit(1);
        }
    }

    Exit(0);
}
