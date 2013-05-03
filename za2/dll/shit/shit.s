	.file	"shit.c"
	.section	.rodata
.LC1:
	.string	"%c\n"
.LC0:
	.string	"ABSsdjl"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$36, %esp
	movl	.LC0, %eax
	movl	.LC0+4, %edx
	movl	%eax, -16(%ebp)
	movl	%edx, -12(%ebp)
	leal	-16(%ebp), %eax
	movl	%eax, -8(%ebp)
	jmp	.L2
.L3:
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$64, %al
	jle	.L4
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$90, %al
	jg	.L4
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	addl	$32, %eax
	movl	%eax, %edx
	movl	-8(%ebp), %eax
	movb	%dl, (%eax)
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
.L4:
	addl	$1, -8(%ebp)
.L2:
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L3
	movl	$0, %eax
	addl	$36, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.2 20080704 (Asianux 3.0 4.1.2-48)"
	.section	.note.GNU-stack,"",@progbits
