	.file	"test_boost.cpp"
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.type	_ZStL13allocator_arg, @object
	.size	_ZStL13allocator_arg, 1
_ZStL13allocator_arg:
	.zero	1
	.type	_ZStL6ignore, @object
	.size	_ZStL6ignore, 1
_ZStL6ignore:
	.zero	1
	.local	_ZN12_GLOBAL__N_12_1E
	.comm	_ZN12_GLOBAL__N_12_1E,1,1
	.local	_ZN12_GLOBAL__N_12_2E
	.comm	_ZN12_GLOBAL__N_12_2E,1,1
	.local	_ZN12_GLOBAL__N_12_3E
	.comm	_ZN12_GLOBAL__N_12_3E,1,1
	.local	_ZN12_GLOBAL__N_12_4E
	.comm	_ZN12_GLOBAL__N_12_4E,1,1
	.local	_ZN12_GLOBAL__N_12_5E
	.comm	_ZN12_GLOBAL__N_12_5E,1,1
	.local	_ZN12_GLOBAL__N_12_6E
	.comm	_ZN12_GLOBAL__N_12_6E,1,1
	.local	_ZN12_GLOBAL__N_12_7E
	.comm	_ZN12_GLOBAL__N_12_7E,1,1
	.local	_ZN12_GLOBAL__N_12_8E
	.comm	_ZN12_GLOBAL__N_12_8E,1,1
	.local	_ZN12_GLOBAL__N_12_9E
	.comm	_ZN12_GLOBAL__N_12_9E,1,1
.LC0:
	.string	"Hello"
	.text
	.globl	_Z4testv
	.type	_Z4testv, @function
_Z4testv:
.LFB2661:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2661
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	leaq	-33(%rbp), %r12
	movl	$8, %edi
.LEHB0:
	call	_Znwm
.LEHE0:
	movq	%rax, %rbx
	movq	%r12, %rdx
	movl	$.LC0, %esi
	movq	%rbx, %rdi
.LEHB1:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE1:
	leaq	-32(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZN5boost10scoped_ptrISsEC1EPSs
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK5boost10scoped_ptrISsEptEv
	movq	%rax, %rdi
	call	_ZNKSs4sizeEv
	movq	%rax, %rsi
	movl	$_ZSt4cout, %edi
.LEHB2:
	call	_ZNSolsEm
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.LEHE2:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN5boost10scoped_ptrISsED1Ev
	jmp	.L8
.L5:
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	_ZdlPv
	movq	%r12, %rbx
	jmp	.L3
.L6:
	movq	%rax, %rbx
.L3:
	leaq	-33(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB3:
	call	_Unwind_Resume
.L7:
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN5boost10scoped_ptrISsED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE3:
.L8:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2661:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2661:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2661-.LLSDACSB2661
.LLSDACSB2661:
	.uleb128 .LEHB0-.LFB2661
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L6-.LFB2661
	.uleb128 0
	.uleb128 .LEHB1-.LFB2661
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L5-.LFB2661
	.uleb128 0
	.uleb128 .LEHB2-.LFB2661
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L7-.LFB2661
	.uleb128 0
	.uleb128 .LEHB3-.LFB2661
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE2661:
	.text
	.size	_Z4testv, .-_Z4testv
	.align 2
	.type	_ZZ4mainENKUliiE_clEii, @function
_ZZ4mainENKUliiE_clEii:
.LFB2663:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	-12(%rbp), %edx
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2663:
	.size	_ZZ4mainENKUliiE_clEii, .-_ZZ4mainENKUliiE_clEii
	.globl	main
	.type	main, @function
main:
.LFB2662:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$1, -8(%rbp)
	movl	$2, -4(%rbp)
	call	_Z4testv
	leaq	-9(%rbp), %rax
	movl	$3, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	_ZZ4mainENKUliiE_clEii
	movl	%eax, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2662:
	.size	main, .-main
	.section	.text._ZN5boost3argILi1EEC2Ev,"axG",@progbits,_ZN5boost3argILi1EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi1EEC2Ev
	.type	_ZN5boost3argILi1EEC2Ev, @function
_ZN5boost3argILi1EEC2Ev:
.LFB2722:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2722:
	.size	_ZN5boost3argILi1EEC2Ev, .-_ZN5boost3argILi1EEC2Ev
	.weak	_ZN5boost3argILi1EEC1Ev
	.set	_ZN5boost3argILi1EEC1Ev,_ZN5boost3argILi1EEC2Ev
	.section	.text._ZN5boost3argILi2EEC2Ev,"axG",@progbits,_ZN5boost3argILi2EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi2EEC2Ev
	.type	_ZN5boost3argILi2EEC2Ev, @function
_ZN5boost3argILi2EEC2Ev:
.LFB2725:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2725:
	.size	_ZN5boost3argILi2EEC2Ev, .-_ZN5boost3argILi2EEC2Ev
	.weak	_ZN5boost3argILi2EEC1Ev
	.set	_ZN5boost3argILi2EEC1Ev,_ZN5boost3argILi2EEC2Ev
	.section	.text._ZN5boost3argILi3EEC2Ev,"axG",@progbits,_ZN5boost3argILi3EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi3EEC2Ev
	.type	_ZN5boost3argILi3EEC2Ev, @function
_ZN5boost3argILi3EEC2Ev:
.LFB2728:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2728:
	.size	_ZN5boost3argILi3EEC2Ev, .-_ZN5boost3argILi3EEC2Ev
	.weak	_ZN5boost3argILi3EEC1Ev
	.set	_ZN5boost3argILi3EEC1Ev,_ZN5boost3argILi3EEC2Ev
	.section	.text._ZN5boost3argILi4EEC2Ev,"axG",@progbits,_ZN5boost3argILi4EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi4EEC2Ev
	.type	_ZN5boost3argILi4EEC2Ev, @function
_ZN5boost3argILi4EEC2Ev:
.LFB2731:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2731:
	.size	_ZN5boost3argILi4EEC2Ev, .-_ZN5boost3argILi4EEC2Ev
	.weak	_ZN5boost3argILi4EEC1Ev
	.set	_ZN5boost3argILi4EEC1Ev,_ZN5boost3argILi4EEC2Ev
	.section	.text._ZN5boost3argILi5EEC2Ev,"axG",@progbits,_ZN5boost3argILi5EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi5EEC2Ev
	.type	_ZN5boost3argILi5EEC2Ev, @function
_ZN5boost3argILi5EEC2Ev:
.LFB2734:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2734:
	.size	_ZN5boost3argILi5EEC2Ev, .-_ZN5boost3argILi5EEC2Ev
	.weak	_ZN5boost3argILi5EEC1Ev
	.set	_ZN5boost3argILi5EEC1Ev,_ZN5boost3argILi5EEC2Ev
	.section	.text._ZN5boost3argILi6EEC2Ev,"axG",@progbits,_ZN5boost3argILi6EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi6EEC2Ev
	.type	_ZN5boost3argILi6EEC2Ev, @function
_ZN5boost3argILi6EEC2Ev:
.LFB2737:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2737:
	.size	_ZN5boost3argILi6EEC2Ev, .-_ZN5boost3argILi6EEC2Ev
	.weak	_ZN5boost3argILi6EEC1Ev
	.set	_ZN5boost3argILi6EEC1Ev,_ZN5boost3argILi6EEC2Ev
	.section	.text._ZN5boost3argILi7EEC2Ev,"axG",@progbits,_ZN5boost3argILi7EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi7EEC2Ev
	.type	_ZN5boost3argILi7EEC2Ev, @function
_ZN5boost3argILi7EEC2Ev:
.LFB2740:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2740:
	.size	_ZN5boost3argILi7EEC2Ev, .-_ZN5boost3argILi7EEC2Ev
	.weak	_ZN5boost3argILi7EEC1Ev
	.set	_ZN5boost3argILi7EEC1Ev,_ZN5boost3argILi7EEC2Ev
	.section	.text._ZN5boost3argILi8EEC2Ev,"axG",@progbits,_ZN5boost3argILi8EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi8EEC2Ev
	.type	_ZN5boost3argILi8EEC2Ev, @function
_ZN5boost3argILi8EEC2Ev:
.LFB2743:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2743:
	.size	_ZN5boost3argILi8EEC2Ev, .-_ZN5boost3argILi8EEC2Ev
	.weak	_ZN5boost3argILi8EEC1Ev
	.set	_ZN5boost3argILi8EEC1Ev,_ZN5boost3argILi8EEC2Ev
	.section	.text._ZN5boost3argILi9EEC2Ev,"axG",@progbits,_ZN5boost3argILi9EEC5Ev,comdat
	.align 2
	.weak	_ZN5boost3argILi9EEC2Ev
	.type	_ZN5boost3argILi9EEC2Ev, @function
_ZN5boost3argILi9EEC2Ev:
.LFB2746:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2746:
	.size	_ZN5boost3argILi9EEC2Ev, .-_ZN5boost3argILi9EEC2Ev
	.weak	_ZN5boost3argILi9EEC1Ev
	.set	_ZN5boost3argILi9EEC1Ev,_ZN5boost3argILi9EEC2Ev
	.section	.text._ZN5boost10scoped_ptrISsEC2EPSs,"axG",@progbits,_ZN5boost10scoped_ptrISsEC5EPSs,comdat
	.align 2
	.weak	_ZN5boost10scoped_ptrISsEC2EPSs
	.type	_ZN5boost10scoped_ptrISsEC2EPSs, @function
_ZN5boost10scoped_ptrISsEC2EPSs:
.LFB2760:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2760:
	.size	_ZN5boost10scoped_ptrISsEC2EPSs, .-_ZN5boost10scoped_ptrISsEC2EPSs
	.weak	_ZN5boost10scoped_ptrISsEC1EPSs
	.set	_ZN5boost10scoped_ptrISsEC1EPSs,_ZN5boost10scoped_ptrISsEC2EPSs
	.section	.text._ZN5boost10scoped_ptrISsED2Ev,"axG",@progbits,_ZN5boost10scoped_ptrISsED5Ev,comdat
	.align 2
	.weak	_ZN5boost10scoped_ptrISsED2Ev
	.type	_ZN5boost10scoped_ptrISsED2Ev, @function
_ZN5boost10scoped_ptrISsED2Ev:
.LFB2763:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZN5boost14checked_deleteISsEEvPT_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2763:
	.size	_ZN5boost10scoped_ptrISsED2Ev, .-_ZN5boost10scoped_ptrISsED2Ev
	.weak	_ZN5boost10scoped_ptrISsED1Ev
	.set	_ZN5boost10scoped_ptrISsED1Ev,_ZN5boost10scoped_ptrISsED2Ev
	.section	.rodata
	.align 8
.LC1:
	.string	"/usr/include/boost/smart_ptr/scoped_ptr.hpp"
.LC2:
	.string	"px != 0"
	.section	.text._ZNK5boost10scoped_ptrISsEptEv,"axG",@progbits,_ZNK5boost10scoped_ptrISsEptEv,comdat
	.align 2
	.weak	_ZNK5boost10scoped_ptrISsEptEv
	.type	_ZNK5boost10scoped_ptrISsEptEv, @function
_ZNK5boost10scoped_ptrISsEptEv:
.LFB2765:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L26
	movl	$_ZZNK5boost10scoped_ptrISsEptEvE19__PRETTY_FUNCTION__, %ecx
	movl	$99, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	__assert_fail
.L26:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2765:
	.size	_ZNK5boost10scoped_ptrISsEptEv, .-_ZNK5boost10scoped_ptrISsEptEv
	.section	.text._ZN5boost14checked_deleteISsEEvPT_,"axG",@progbits,_ZN5boost14checked_deleteISsEEvPT_,comdat
	.weak	_ZN5boost14checked_deleteISsEEvPT_
	.type	_ZN5boost14checked_deleteISsEEvPT_, @function
_ZN5boost14checked_deleteISsEEvPT_:
.LFB2813:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rbx
	testq	%rbx, %rbx
	je	.L28
	movq	%rbx, %rdi
	call	_ZNSsD1Ev
	movq	%rbx, %rdi
	call	_ZdlPv
.L28:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2813:
	.size	_ZN5boost14checked_deleteISsEEvPT_, .-_ZN5boost14checked_deleteISsEEvPT_
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2876:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L30
	cmpl	$65535, -8(%rbp)
	jne	.L30
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
	movl	$_ZN12_GLOBAL__N_12_1E, %edi
	call	_ZN5boost3argILi1EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_2E, %edi
	call	_ZN5boost3argILi2EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_3E, %edi
	call	_ZN5boost3argILi3EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_4E, %edi
	call	_ZN5boost3argILi4EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_5E, %edi
	call	_ZN5boost3argILi5EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_6E, %edi
	call	_ZN5boost3argILi6EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_7E, %edi
	call	_ZN5boost3argILi7EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_8E, %edi
	call	_ZN5boost3argILi8EEC1Ev
	movl	$_ZN12_GLOBAL__N_12_9E, %edi
	call	_ZN5boost3argILi9EEC1Ev
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2876:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.section	.rodata
	.align 4
	.type	_ZN9__gnu_cxxL21__default_lock_policyE, @object
	.size	_ZN9__gnu_cxxL21__default_lock_policyE, 4
_ZN9__gnu_cxxL21__default_lock_policyE:
	.long	2
	.text
	.type	_GLOBAL__sub_I__Z4testv, @function
_GLOBAL__sub_I__Z4testv:
.LFB2877:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2877:
	.size	_GLOBAL__sub_I__Z4testv, .-_GLOBAL__sub_I__Z4testv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z4testv
	.section	.rodata
	.align 32
	.type	_ZZNK5boost10scoped_ptrISsEptEvE19__PRETTY_FUNCTION__, @object
	.size	_ZZNK5boost10scoped_ptrISsEptEvE19__PRETTY_FUNCTION__, 79
_ZZNK5boost10scoped_ptrISsEptEvE19__PRETTY_FUNCTION__:
	.string	"T* boost::scoped_ptr<T>::operator->() const [with T = std::basic_string<char>]"
	.align 8
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, @object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 8
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.quad	_ZL28__gthrw___pthread_key_createPjPFvPvE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
