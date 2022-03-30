.section .rodata

.data

.text

f1:
	pushq %rbp
	movq %rsp, rbp


	# return ci10
	movl $10, %eax
	leave
	ret
f2:
	pushq %rbp
	movq %rsp, rbp

	# vi1 -> -4(%rbp)
	# vi2 -> -8(%rbp)
	# vi3 -> -12(%rbp)

	# return pi1
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
	# va2[3] -> -32(%rbp)
	# va2[4] -> -28(%rbp)
	# va2[5] -> -24(%rbp)
	# va2[6] -> -20(%rbp)
	# va2[7] -> -16(%rbp)
	# va2[8] -> -12(%rbp)
	# va2[9] -> -8(%rbp)

	# vi1 = ci3
	movl $3, -4(%rbp)

	# vi1 = pi1 - pi2
	movl %edi, %eax
	subl %esi, %eax
	movl %eax, -4(%rbp)
	# if no. 1
	cmpl %edi, $0
	jne end_if1

	# get va2 index ci8 to vi1
	leaq -12(%rbp), %rax
	movl (%rax), %eax
	movl %eax, -4(%rbp)

end_if1:

	# if no. 2
	cmpl %esi, $0
	jne end_if2

	# get va2 index ci5 to pi1
	leaq -24(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %edi

end_if2:

	# if no. 3
	cmpl 10, $0
	jne end_if3

	# get va2 index ci2 to pi2
	leaq -36(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %esi

end_if3:


	# set va2 index ci9 with pi2
	movl %esi, -8(%rbp)

	# return ci10
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
	# va3[8] -> -96(%rbp)
	# va3[9] -> -92(%rbp)
	# va3[10] -> -88(%rbp)
	# va3[11] -> -84(%rbp)
	# va3[12] -> -80(%rbp)
	# va3[13] -> -76(%rbp)
	# va3[14] -> -72(%rbp)
	# va3[15] -> -68(%rbp)
	# va3[16] -> -64(%rbp)
	# va3[17] -> -60(%rbp)
	# va3[18] -> -56(%rbp)
	# va3[19] -> -52(%rbp)
	# va3[20] -> -48(%rbp)
	# va3[21] -> -44(%rbp)
	# va3[22] -> -40(%rbp)
	# va3[23] -> -36(%rbp)
	# va3[24] -> -32(%rbp)
	# va3[25] -> -28(%rbp)
	# va3[26] -> -24(%rbp)
	# va3[27] -> -20(%rbp)
	# va3[28] -> -16(%rbp)
	# va3[29] -> -12(%rbp)

	# get pa1 index ci2 to vi2
	movq %rdi, %rax
	addq $8, %rax
	movl (%rax), %eax
	movl %eax, -8(%rbp)

	# set va3 index ci7 with vi1
	movl -4(%rbp), %ecx
	movl %ecx, -100(%rbp)

	# set pa1 index ci2 with vi2
	movq %rdi, %rax
	addq $8, %rax
	movl -8(%rbp), %ecx
	movl %ecx, (%eax)

	# vi1 = vi2 + ci6
	movl -8(%rbp), %eax
	addl $6, %eax
	movl %eax, -4(%rbp)

	# vi1 = vi2 - ci1
	movl -8(%rbp), %eax
	subl $1, %eax
	movl %eax, -4(%rbp)

	# vi1 = vi2 * ci2
	movl -8(%rbp), %eax
	imull $2, %eax
	movl %eax, -4(%rbp)

	# return vi2
	movl -8(%rbp), %eax
	leave
	ret
