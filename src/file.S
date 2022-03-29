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

	# vi1 -> -4(%rbp)
	# vi2 -> -8(%rbp)
	# vi4 -> -12(%rbp)
	movl %edi, %eax
	leave
	ret
f3:
	pushq %rbp
	movq %rsp, rbp

	# vi1 -> -4(%rbp)
	# va2[0] -> -44(%rbp)
	# va2[1] -> -40(%rbp)
	# va2[2] -> -36(%rbp)
	cmpl %edi, $0
	jne end_if1

end_if1:

	cmpl %esi, $0
	jne end_if2

end_if2:

	cmpl 10, $0
	jne end_if3

end_if3:

	movl $10, %eax
	leave
	ret
