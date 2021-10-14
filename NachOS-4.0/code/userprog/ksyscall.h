/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kernel.h"
#include "synchconsole.h"

char *User2System(int virtAddr, int limit);
int System2User(int virtAddr, int len, char *buffer);
bool WillOverflow(int cur, int next);

void SysHalt() { kernel->interrupt->Halt(); }

int SysAdd(int op1, int op2) { return op1 + op2; }

// Cai dat cua ham ReadNum, duoc goi trong exception.cc
int SysReadNum() {
    int res = 0,
        sign = 1;  // res la ket qua tra ve, sign la dau (1: duong, -1: am)
    char ch;       // ky tu dang duoc doc
    ch = kernel->synchConsoleIn
             ->GetChar();  // doc ky tu dau tien de xem so am hay duong
    if (ch == '-') {
        sign = -1;
    } else if (ch == '+') {
        sign = 1;
    } else if (ch < '0' || ch > '9') {  // neu khong phai so thi tra ve 0
        return 0;
    } else {
        res = ch - '0';  // neu khong phai so am thi luw ket qua
    }

    while (true) {
        ch = kernel->synchConsoleIn->GetChar();  /// doc toan bo chuoi con lai
        if (ch == '\n') {                        // neu la enter, luu gia tri duoc nhap
            return res * sign;
        }
        if (ch < '0' || ch > '9') {
            return 0;
        }
        if (!WillOverflow(res, ch - '0')) {  // neu khong tran so, tinh gia tri
                                             // den vi tri dang doc
            res = res * 10 + (ch - '0');
        } else {  // new tran so, tra ve 0
            return 0;
        }
    }
}

bool WillOverflow(int cur, int next) {
    // Xet tran so, neu > INT_MAX hoac < INT_MIN thi tran so
    return (((INT_MAX - next) / 10) < cur || (INT_MIN + next) / 10 > cur);
}

// Cai dat cua ham PrintNum, duoc goi trong exception.cc
void SysPrintNum(int number) {
    char str[20];
    int i = 0;
    sprintf(str, "%d", number);  // Bien so thanh chuoi
    while (str[i] != '\0') {     // in ra tung ky tu cua chuoi
        kernel->synchConsoleOut->PutChar(str[i]);
        i++;
    }
}

// Cai dat cua ham ReadChar, duoc goi trong exception.cc
char SysReadChar() {
    return kernel->synchConsoleIn->GetChar();
}  // doc ky tu tu console

// Cai dat cua ham PrintChar, duoc goi trong exception.cc
void SysPrintChar(char character) {
    kernel->synchConsoleOut->PutChar(character);  // in ky tu ra man hinh
}

// Cai dat cua ham RandomNum, duoc goi trong exception.cc
int SysRandomNum() {
    srand(time(0));
    return rand();
}

// Cai dat cua ham ReadString, duoc goi trong exception.cc
void SysReadString(int virtAddress, int length) {
    char *buffer;
    int i = 0;
    int onechar = 0;
    buffer = User2System(virtAddress, length);
    do {
        onechar = (int)buffer[i];
        printf("%d\n", onechar);
        i++;
    } while (i < length && onechar != 0);
    for (i = 0; i < length; i++) {
        buffer[i] = kernel->synchConsoleIn->GetChar();
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
        System2User(virtAddress, length, buffer);  // chuyen vung nho ve lai user-space

        delete buffer;
    }
}

// Ham copy buffer tu user-space vao kernel-space
char *User2System(int virtAddr, int limit) {
    int i;  // index
    int oneChar;
    char *kernelBuf = NULL;
    kernelBuf = new char[limit + 1];  // need for terminal string
    if (kernelBuf == NULL) return kernelBuf;
    memset(kernelBuf, 0, limit + 1);
    for (i = 0; i < limit; i++) {
        kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
        kernelBuf[i] = (char)oneChar;
        if (oneChar == 0) break;
    }
    return kernelBuf;
}

// Cai dat cua ham PrintString, duoc goi trong exception.cc
void SysPrintString(int virtAdrr) {
    char *buffer;
    buffer = User2System(virtAdrr, 1000);  // chuyen du lieu tu user-space vao kernel-space
    int i = 0;
    while (buffer[i] != '\0') {  // in tung ky tu ra man hinh
        kernel->synchConsoleOut->PutChar((char)buffer[i]);
        i++;
    }
    delete buffer;
}

// Ham copy buffer tu kernel-space ra user-space
int System2User(int virtAddr, int len, char *buffer) {
    if (len < 0) return -1;
    if (len == 0) return len;
    int i = 0;
    int oneChar = 0;
    do {
        oneChar = (int)buffer[i];
        kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
        i++;
    } while (i < len && oneChar != 0);
    return i;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
