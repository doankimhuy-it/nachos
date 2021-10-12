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

#include "kernel.h"
#include "synchconsole.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *User2System(int virtAddr, int limit);
int System2User(int virtAddr, int len, char *buffer);
bool WillOverflow(int cur, int next);

void SysHalt() { kernel->interrupt->Halt(); }

int SysAdd(int op1, int op2) { return op1 + op2; }

int SysReadNum() {
  int res = 0, i, j;
  char ch;
  char str[255];
  for (i = 0; i < 255; i++) {
    ch = kernel->synchConsoleIn->GetChar();
    if (ch == '\n')
      break;
    else
      str[i] = ch;
  }
  for (j = 0; j < i; j++) {
    ch = str[j];
    if (ch == '\n')
      return res;
    if (ch < '0' || ch > '9') {
      return 0;
    }
    if (!WillOverflow(res, ch - '0'))
      if (res >= 0)
        res = res * 10 + (ch - '0');
      else
        res = res * 10 - (ch - '0');
    else
      return 0;
  }
  return res;
}

bool WillOverflow(int cur, int next) {
  // Perform your overflow check
  return (((INT_MAX - next) / 10) < cur || (INT_MIN + next) / 10 > cur);
}

void SysPrintNum(int number) {
  char str[20];
  int i = 0;
  sprintf(str, "%d", number);
  while (str[i] != '\0') {
    kernel->synchConsoleOut->PutChar(str[i]);
    i++;
  }
}

char SysReadChar() { return kernel->synchConsoleIn->GetChar(); }

void SysPrintChar(char character) {
  kernel->synchConsoleOut->PutChar(character);
}

int SysRandomNum() {
  srand(time(0));
  return rand();
}

void SysReadString(int virtAddress, int length) {
  char *buffer;
  buffer = User2System(virtAddress, length);
  for (int i = 0; i < length; i++) {
    buffer[i] = kernel->synchConsoleIn->GetChar();
    if (buffer[i] == '\n') {
      break;
    }
  }
  System2User(virtAddress, length, buffer);

  delete buffer;
}

char *User2System(int virtAddr, int limit) {
  int i; // index
  int oneChar;
  char *kernelBuf = NULL;
  kernelBuf = new char[limit + 1]; // need for terminal string
  if (kernelBuf == NULL)
    return kernelBuf;
  memset(kernelBuf, 0, limit + 1);
  // printf("\n Filename u2s:");
  for (i = 0; i < limit; i++) {
    kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
    kernelBuf[i] = (char)oneChar;
    // printf("%c",kernelBuf[i]);
    if (oneChar == 0)
      break;
  }
  return kernelBuf;
}

void SysPrintString(int virtAdrr) {
  char *buffer;
  buffer = User2System(virtAdrr, 255);
  int i = 0;
  while (buffer[i] != '\0') {
    kernel->synchConsoleOut->PutChar(buffer[i]);
    i++;
  }
  delete buffer;
}

int System2User(int virtAddr, int len, char *buffer) {
  if (len < 0)
    return -1;
  if (len == 0)
    return len;
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
