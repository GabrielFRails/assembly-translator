.section .rodata

.data

.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp

	# vi1 -> -4(%rbp)
	subq $16, %rsp

	# vi1 = call f100 ci1024
	movl $1024, %edi
	call f100
	movl %eax, -4(%rbp)

	# vi1 = call f100 vi1
	movl -4(%rbp), %edi
	call f100
	movl %eax, -4(%rbp)

	# return vi1
	movl -4(%rbp), %eax
	leave
	ret

