	.file	"b.c"
	.text
	.p2align 4,,15
	.globl	m12
	.type	m12, @function
m12:
.LFB0:
	.cfi_startproc
	leaq	(%rdi,%rdi,2), %rax
	salq	$2, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	m12, .-m12
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
