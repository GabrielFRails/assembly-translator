.section .rodata

.data

.text

.globl main
main:
   pushq %rbp
   movq  %rsp, %rbp

f1:
   pushq %rbp
   movq %rsp, rbp

   leave
   ret
f2:
   pushq %rbp
   movq %rsp, rbp

   leave
   ret

   # return 0
   movl $0, %%eax
   leave
   ret