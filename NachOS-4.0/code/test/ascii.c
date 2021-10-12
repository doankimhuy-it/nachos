/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main()
{
  char* tab = "\t";
  char* newline = "\n";
  int i = 0;
  for(i = 33; i < 128; ++i){
      PrintNum(i);
      PrintString(tab);
      PrintChar((char)i);
      PrintString(newline);
  }

  Halt();
  /* not reached */
}
