	.file	"wc209.c"
	.globl	state
	.bss
	.align 4
	.type	state, @object
	.size	state, 4
state:
	.zero	4
	.globl	result
	.align 4
	.type	result, @object
	.size	result, 4
result:
	.zero	4
	.globl	from
	.align 4
	.type	from, @object
	.size	from, 4
from:
	.zero	4
	.globl	file
	.align 4
	.type	file, @object
	.size	file, 4
file:
	.zero	4
	.comm	c,4,4
	.comm	nErrorLine,4,4
	.globl	nLine
	.data
	.align 4
	.type	nLine, @object
	.size	nLine, 4
nLine:
	.long	1
	.comm	nWord,4,4
	.comm	nChar,4,4
	.text
	.globl	Add
	.type	Add, @function
Add:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	nLine(%rip), %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, nLine(%rip)
	movl	nWord(%rip), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, nWord(%rip)
	movl	nChar(%rip), %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, nChar(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	Add, .-Add
	.globl	StartFunc
	.type	StartFunc, @function
StartFunc:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$47, %eax
	jne	.L4
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$1, file(%rip)
	movl	$4, state(%rip)
	jmp	.L5
.L4:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L6
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	je	.L6
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$1, file(%rip)
	movl	$1, state(%rip)
	jmp	.L5
.L6:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L7
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L8
	movl	$1, %edx
	movl	$0, %esi
	movl	$1, %edi
	call	Add
	jmp	.L9
.L8:
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
.L9:
	movl	$1, file(%rip)
	jmp	.L5
.L7:
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	jne	.L5
	movl	file(%rip), %eax
	testl	%eax, %eax
	jne	.L5
	movl	$0, nLine(%rip)
.L5:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	StartFunc, .-StartFunc
	.globl	CharFunc
	.type	CharFunc, @function
CharFunc:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$47, %eax
	jne	.L12
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$1, from(%rip)
	movl	$4, state(%rip)
	jmp	.L13
.L12:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L14
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	je	.L14
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	jmp	.L13
.L14:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L15
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L16
	movl	$1, %edx
	movl	$1, %esi
	movl	$1, %edi
	call	Add
	movl	$3, state(%rip)
	jmp	.L13
.L16:
	movl	$1, %edx
	movl	$1, %esi
	movl	$0, %edi
	call	Add
	movl	$2, state(%rip)
	jmp	.L13
.L15:
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	jne	.L13
	movl	$0, %edx
	movl	$1, %esi
	movl	$0, %edi
	call	Add
.L13:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	CharFunc, .-CharFunc
	.globl	SpaceFunc
	.type	SpaceFunc, @function
SpaceFunc:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$47, %eax
	jne	.L20
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$4, state(%rip)
	jmp	.L21
.L20:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L22
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	je	.L22
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$1, state(%rip)
	jmp	.L21
.L22:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L21
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L23
	movl	$1, %edx
	movl	$0, %esi
	movl	$1, %edi
	call	Add
	movl	$3, state(%rip)
	jmp	.L21
.L23:
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
.L21:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	SpaceFunc, .-SpaceFunc
	.globl	NewLineFunc
	.type	NewLineFunc, @function
NewLineFunc:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$47, %eax
	jne	.L26
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$4, state(%rip)
	jmp	.L27
.L26:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L28
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	je	.L28
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$1, state(%rip)
	jmp	.L27
.L28:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L27
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L29
	movl	$1, %edx
	movl	$0, %esi
	movl	$1, %edi
	call	Add
	jmp	.L27
.L29:
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$2, state(%rip)
.L27:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	NewLineFunc, .-NewLineFunc
	.globl	Check1Func
	.type	Check1Func, @function
Check1Func:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$42, %eax
	jne	.L32
	movl	from(%rip), %eax
	testl	%eax, %eax
	jne	.L33
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	jmp	.L34
.L33:
	movl	from(%rip), %eax
	cmpl	$1, %eax
	jne	.L34
	movl	$1, %edx
	movl	$1, %esi
	movl	$0, %edi
	call	Add
	movl	$0, from(%rip)
.L34:
	movl	$5, state(%rip)
	movl	nLine(%rip), %eax
	movl	%eax, nErrorLine(%rip)
	jmp	.L35
.L32:
	movl	c(%rip), %eax
	cmpl	$47, %eax
	jne	.L36
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	jmp	.L35
.L36:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L37
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	je	.L37
	movl	$1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$0, from(%rip)
	movl	$1, state(%rip)
	jmp	.L35
.L37:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	c(%rip), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L38
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L39
	movl	$1, %edx
	movl	$1, %esi
	movl	$1, %edi
	call	Add
	movl	$3, state(%rip)
	jmp	.L40
.L39:
	movl	$1, %edx
	movl	$1, %esi
	movl	$0, %edi
	call	Add
	movl	$2, state(%rip)
.L40:
	movl	$0, from(%rip)
	jmp	.L35
.L38:
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	jne	.L35
	movl	$0, %edx
	movl	$1, %esi
	movl	$0, %edi
	call	Add
.L35:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	Check1Func, .-Check1Func
	.globl	CommentFunc
	.type	CommentFunc, @function
CommentFunc:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$42, %eax
	jne	.L43
	movl	$6, state(%rip)
	jmp	.L44
.L43:
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L45
	movl	$1, %edx
	movl	$0, %esi
	movl	$1, %edi
	call	Add
	jmp	.L44
.L45:
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	jne	.L44
	movl	$1, result(%rip)
.L44:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	CommentFunc, .-CommentFunc
	.globl	Check2Func
	.type	Check2Func, @function
Check2Func:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	c(%rip), %eax
	cmpl	$47, %eax
	jne	.L48
	movl	$-1, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	Add
	movl	$0, state(%rip)
	jmp	.L49
.L48:
	movl	c(%rip), %eax
	cmpl	$10, %eax
	jne	.L50
	movl	$1, %edx
	movl	$0, %esi
	movl	$1, %edi
	call	Add
	movl	$5, state(%rip)
	jmp	.L49
.L50:
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	jne	.L51
	movl	$1, result(%rip)
	jmp	.L49
.L51:
	movl	c(%rip), %eax
	cmpl	$42, %eax
	je	.L49
	movl	$5, state(%rip)
.L49:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	Check2Func, .-Check2Func
	.section	.rodata
	.align 8
.LC0:
	.string	"Error: line %d: unterminated comment\n"
	.text
	.globl	ErrorFunc
	.type	ErrorFunc, @function
ErrorFunc:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	nErrorLine(%rip), %edx
	movq	stderr(%rip), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	ErrorFunc, .-ErrorFunc
	.section	.rodata
.LC1:
	.string	"%d %d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
.L65:
	call	getchar@PLT
	movl	%eax, c(%rip)
	movl	state(%rip), %eax
	cmpl	$6, %eax
	ja	.L56
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L58(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L58(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L58:
	.long	.L57-.L58
	.long	.L59-.L58
	.long	.L60-.L58
	.long	.L61-.L58
	.long	.L62-.L58
	.long	.L63-.L58
	.long	.L64-.L58
	.text
.L57:
	call	StartFunc
	jmp	.L56
.L59:
	call	CharFunc
	jmp	.L56
.L60:
	call	SpaceFunc
	jmp	.L56
.L61:
	call	NewLineFunc
	jmp	.L56
.L62:
	call	Check1Func
	jmp	.L56
.L63:
	call	CommentFunc
	jmp	.L56
.L64:
	call	Check2Func
	nop
.L56:
	movl	c(%rip), %eax
	cmpl	$-1, %eax
	jne	.L65
	movl	result(%rip), %eax
	cmpl	$1, %eax
	jne	.L66
	call	ErrorFunc
	movl	$1, %eax
	jmp	.L67
.L66:
	movl	nChar(%rip), %esi
	movl	nWord(%rip), %ecx
	movl	nLine(%rip), %edx
	movq	stdout(%rip), %rax
	movl	%esi, %r8d
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, %eax
.L67:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
