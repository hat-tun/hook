#include <stdio.h>

#define HOOK __asm__ volatile ("movl %%ebp, %0":"=r"(ebp_buf):);	\
  ret_addr = (unsigned int *)ebp_buf[1];				\
  ebp_buf[1] = (unsigned int)hook;		


unsigned int *ebp_buf;
unsigned int *ret_addr;

void hook(){
  
  int z;
  __asm__ volatile ("movl %%eax, %0":"=r"(z):);
  
  z=z*2;
  printf("hook!\n");

  __asm__ volatile ("movl %0 ,%%eax"::"r"(z));
  __asm__ volatile ("movl %0 ,%%ebx"::"m"(ret_addr));
  __asm__ volatile ("movl %%ebp, %%esp"::);  
  __asm__ volatile ("popl %%ebp"::);
  __asm__ volatile ("jmp *%ebx");

}


int func(){
  
  int x,y,z;

  HOOK;

  x=2;
  y=3;
  z=x+y;

  return z;
}

int main(){
 
  int z = func(); 
  
  printf("z = %d\n",z);
  
  return 0;
}
