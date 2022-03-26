.section .rodata

.data

.text

f1:
	pushq %rbp
	movq %rsp, rbp

	movl $10, %eax
	leave
	ret
f2:
	pushq %rbp
	movq %rsp, rbp

	movl %edi, %eax
	leave
	ret
