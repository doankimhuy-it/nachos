/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main()
{
  int result;
  // result = Add(42, 23);

  //PrintNum(100);
  result = ReadNum();
  PrintNum(result);
  //result = ReadChar();

  //PrintChar('a');

  //result = RandomNum();
  //PrintNum(result);
  // char *str;
  // ReadString(str, 255);
  // PrintString(str);

  /*char* school = "DH KHTN - DHQG TP.HCM\n";
  char* class = "19CNTN\n";
  char* team = "Doan Kim Huy - 19120239\n"
                "Vo Chanh Hung - 19120523\n"
                "Quach Binh Long - 19120283\n";

  char* slash = "----------------------------------------------\n";

  char* sortIntroduction = "Chuong trinh Sort cho phep sap xep mot mang so nguyen co so phan tu nho hon 100.\n";
  char* sortUsage = "Cach su dung:\n"
                    "1. Nhap so phan tu cua mang nho hon 100.\n"
                    "2. Chon sap xep tang dan hoac giam dan.\n"
                    "3. Sap xep mang bang thuat toan Bubble Sort.\n";

  char* asciiIntroduction = "Chuong trinh Ascii in ra danh sach cac ky tu thuoc bang ma ascii.\n";
       
  // Gioi thieu nhom
  PrintString(school);
  PrintString(class);
  PrintString(team);

  PrintString(slash);

  // Gioi thieu chuong trinh Sort
  PrintString(sortIntroduction);
  PrintString(sortUsage);

  PrintString(slash);

  // Gioi thieu chuong trinh Ascii
  PrintString(asciiIntroduction);*/   

  Halt();
  /* not reached */
}
