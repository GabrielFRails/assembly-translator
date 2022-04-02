.section .rodata

.data

.text

.globl f1
f1:
	pushq %rbp
	movq %rsp, %rbp

	subq $0, %rsp

	# return ci10
	movl $10, %eax
	leave
	ret

.globl f2
f2:
	pushq %rbp
	movq %rsp, %rbp

	# vi1 -> -4(%rbp)
	# vi2 -> -8(%rbp)
	# vi3 -> -12(%rbp)
	# %rdi -> -24(%rbp)
	subq $32, %rsp

	# return pi1
	movl %edi, %eax
	leave
	ret

.globl f3
f3:
	pushq %rbp
	movq %rsp, %rbp

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
	# %rdi -> -56(%rbp)
	# %rsi -> -64(%rbp)
	subq $64, %rsp

	# vi1 = ci3
	movl $3, -4(%rbp)

	# vi1 = pi1 - pi2
	movl %edi, %eax
	subl %esi, %eax
	movl %eax, -4(%rbp)
	# if no. 1
	cmpl %edi, $0
	je end_if1

	# get va2 index ci8 to vi1
	leaq -12(%rbp), %rax
	movl (%rax), %eax
	movl %eax, -4(%rbp)

end_if1:

	# if no. 2
	cmpl %esi, $0
	je end_if2

	# get va2 index ci5 to pi1
	leaq -24(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %edi

end_if2:

	# if no. 3
	cmpl 10, $0
	je end_if3

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

.globl f4
f4:
	pushq %rbp
	movq %rsp, %rbp

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
	# %rdi -> -136(%rbp)
	subq $144, %rsp

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

	# salvando parametros
	movq %rdi, -136(%rbp)

	# vi2 = call f1 vi1 va3
	movl -4(%rbp), %edi
	leaq -128(%rbp), %rsi
	call f1
	movl %eax -8(%rbp)

	# recuperando parametros
	movq -136(%rbp), %rdi

	# salvando parametros
	movq %rdi, -136(%rbp)

	# vi2 = call f1 ci5 pa1
	movl $5, %edi
	leaq -136(%rbp), %rsi
	call f1
	movl %eax -8(%rbp)

	# recuperando parametros
	movq -136(%rbp), %rdi

	# return vi2
	movl -8(%rbp), %eax
	leave
	ret

.globl f5
f5:
	pushq %rbp
	movq %rsp, %rbp

	# vi1 -> -4(%rbp)
	# vi2 -> -8(%rbp)
	# vi3 -> -12(%rbp)
	# va4[0] -> -32(%rbp)
	# va4[1] -> -28(%rbp)
	# va4[2] -> -24(%rbp)
	# va4[3] -> -20(%rbp)
	# va4[4] -> -16(%rbp)
	# %rdi -> -40(%rbp)
	# %rsi -> -48(%rbp)
	subq $48, %rsp

	# vi1 = vi2 / ci2
	movl -8(%rbp), %eax
	cltd
	movl $2, %ecx
	idivl %ecx
	movl %eax, -4(%rbp)

	# vi2 = pi1 / vi1
	movl %edi, %eax
	cltd
	idivl -4(%rbp)
	movl %eax, -8(%rbp)

	# get pa2 index ci3 to vi3
	movq %rsi, %rax
	addq $12, %rax
	movl (%rax), %eax
	movl %eax, -12(%rbp)

	# vi3 = vi3 / pi1
	movl -12(%rbp), %eax
	cltd
	idivl %edi
	movl %eax, -12(%rbp)

	# pi1 = pi1 / vi3
	movl %edi, %eax
	cltd
	idivl -12(%rbp)
	movl %eax, -4(%rbp)

	# get va4 index ci3 to vi3
	leaq -20(%rbp), %rax
	movl (%rax), %eax
	movl %eax, -12(%rbp)

	# vi1 = vi2 / vi3
	movl -8(%rbp), %eax
	cltd
	idivl -12(%rbp)
	movl %eax, -4(%rbp)

	# return vi1
	movl -4(%rbp), %eax
	leave
	ret

.globl f6
f6:
	pushq %rbp
	movq %rsp, %rbp

	# vi1 -> -4(%rbp)
	# vi2 -> -8(%rbp)
	# %rdi -> -16(%rbp)
	subq $16, %rsp

	# salvando parametros
	movl %edi, -16(%rbp)

	# vi2 = call f2 vi1
	movl -4(%rbp), %edi
	call f2
	movl %eax -8(%rbp)

	# recuperando parametros
	movq -16(%rbp), %rdi

	# return vi1
	movl -4(%rbp), %eax
	leave
	ret

.globl f7
f7:
	pushq %rbp
	movq %rsp, %rbp

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
	# %rdi -> -56(%rbp)
	# %rsi -> -64(%rbp)
	subq $64, %rsp

	# vi1 = ci3
	movl $3, -4(%rbp)

	# vi1 = pi1 - pi2
	movl %edi, %eax
	subl %esi, %eax
	movl %eax, -4(%rbp)
	# if no. 1
	cmpl %edi, $0
	je end_if1

	# get va2 index ci8 to vi1
	leaq -12(%rbp), %rax
	movl (%rax), %eax
	movl %eax, -4(%rbp)

end_if1:

	# if no. 2
	cmpl %esi, $0
	je end_if2

	# get va2 index ci5 to pi1
	leaq -24(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %edi

end_if2:

	# if no. 3
	cmpl 10, $0
	je end_if3

	# get va2 index ci2 to pi2
	leaq -36(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %esi

end_if3:

	# if no. 4
	cmpl -4(%rbp) , $0
	je end_if4

	# get va2 index ci2 to pi1
	leaq -36(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %edi

end_if4:

	# if no. 5
	cmpl -44(%rbp) , $0
	je end_if5

	# get va2 index ci2 to pi1
	leaq -36(%rbp), %rax
	movl (%rax), %eax
	movl %eax, %edi

end_if5:


	# return ci10
	movl $10, %eax
	leave
	ret

