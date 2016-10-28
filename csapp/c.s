	.file	"c.c"
	.text
	.p2align 4,,15
	.globl	arith
	.type	arith, @function
arith:
.LFB0:
	.cfi_startproc
	leaq	(%rdi,%rsi), %rax
	addq	%rdx, %rax
	leaq	(%rsi,%rsi,2), %rdx
	salq	$4, %rdx
	leaq	4(%rdi,%rdx), %rdx
	imulq	%rdx, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	arith, .-arith
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
