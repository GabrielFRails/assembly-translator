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
f4:
	pushq %rbp
	movq %rsp, rbp

	# vi1 -> -4(%rbp)
	# vi2 -> -8(%rbp)
	# va3[0] -> -128(%rbp)
	# va3[1] -> -124(%rbp)
	# va3[2] -> -120(%rbp)
	# va3[3] -> -116(%rbp)
	# va3[4] -> -112(%rbp)
	# va3[5] -> -108(%rbp)
	# va3[6] -> -104(%rbp)
	# va3[7] -> -100(%rbp)
	leave
	ret
