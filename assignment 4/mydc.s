### --------------------------------------------------------------------
### mydc.s
### 20140475
### 임범혁
### assignment 4
### Desk Calculator (dc)
### --------------------------------------------------------------------

	.equ	ARRAYSIZE, 20
	.equ	EOF, -1
	
### --------------------------------------------------------------------

	.section ".rodata"
	
scanfFormat:
	.asciz	"%s"
printFormat:	
        .asciz	"%d\n"
printStackEmpty:
        .asciz	"dc: stack empty\n"
	
### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"
	
buffer:
        .skip	ARRAYSIZE
iIndex:
        .skip	4
numStack:
	.skip	4
	
### --------------------------------------------------------------------

	.section ".text"

	## -------------------------------------------------------------
	## int main(void)
	## Runs desk calculator program.  Returns 0.
	## -------------------------------------------------------------

	.globl	main
	.type	main,@function

main:

	pushl   %ebp
	movl	%esp, %ebp
	movl	$0, iIndex
	movl	$0, numStack
	
input:

	## dc number stack initialized. %esp = %ebp
	
	## scanf("%s", buffer)
	pushl	$buffer
	pushl	$scanfFormat
	call    scanf
	addl    $8, %esp

	## check if user input EOF
	cmpl	$EOF, %eax
	je	quit

	## EAX = buffer[0]
	movl	$0, %eax
	movb	buffer(%eax), %al

	## check if user input p
	cmpl	$'p', %eax
	je	print


	## check if user input q
        cmpl    $'q', %eax
        je      quit
	

	## check if user input +
	cmpl	$'+', %eax
	je	addition

	
	## check if user input -
	cmpl	$'-', %eax
	je	subtraction


	## check if user input *
	cmpl    $'*', %eax
	je	multiplication
	
	## check if user input /
	cmpl    $'/', %eax
	je	quotient

	## check if user input %
	cmpl    $'%', %eax
	je	remainder

	## check if user input ^
	cmpl    $'^', %eax
	je	exponentiation

	## check if user input f
        cmpl    $'f', %eax
        je	LIFOprint

	## check if user input c
        cmpl    $'c', %eax
        je	clear

	## check if user input d
        cmpl    $'d', %eax
        je	duplicate

	## check if user input r
        cmpl    $'r', %eax
        je	swap

	## check if user input x
        cmpl    $'x', %eax
        je	random

	## check if user input y
        cmpl    $'y', %eax
        je	primenum

	## check if user input stars with _
	cmpl	$'_', %eax
	je	underbar

	## check if user input number
	pushl	%eax
	call	isdigit
	addl	$4, %esp
	cmpl	$0, %eax
	## user input invalid value
	je	invalidinput

	## user input number
	movl    $0, %eax
        leal    (buffer), %eax	

	pushl 	%eax
	call	atoi
	addl	$4, %esp

	pushl	%eax
	incl	numStack
	jmp	input

invalidinput:
	## pass the invalid number, do nothing
	jmp	input
	
print:
	## if the stack is empty
	cmpl    %ebp, %esp
        je      StackEmpty

	## printf("%d\n", value on the top)
	pushl	$printFormat
	call	printf
	addl	$4, %esp
	jmp	input

addition:
	## if the stack	is empty
	cmpl	%ebp, %esp
	je 	StackEmpty
	popl	%ebx ## EBX = value on the top

	## if the stack is empty after popping the top
	cmpl    %ebp, %esp
	je      SingleStack
	popl	%eax ##	EAX = value on the second top

	addl	%ebx, %eax ## EAX = EAX + EBX
	pushl	%eax
	decl	numStack

	jmp	input

subtraction:
	## if the stack	is empty
	cmpl    %ebp, %esp
	je      StackEmpty
	popl	%ebx ##	EBX = value on the top

	## if the stack is empty after popping the top
	cmpl    %ebp, %esp
	je      SingleStack
	popl    %eax ## EAX = value on the second top

	subl	%ebx, %eax ## EAX = EAX - EBX
	pushl	%eax
	decl	numStack

	jmp	input

multiplication:
	## if the stack	is empty
	cmpl    %ebp, %esp
	je      StackEmpty
	popl	%ebx ## EBX = value on the top
	
	## if the stack is empty after popping the top
	cmpl    %ebp, %esp
	je      SingleStack
	popl    %eax ## EAX = value on the second top

	mull	%ebx ## EAX = EAX * EBX
	pushl	%eax
	decl	numStack

	jmp	input
	
quotient:
	## if the stack	is empty
	cmpl    %ebp, %esp
	je      StackEmpty
	popl	%ebx ## EBX = value on the top

	## if the stack is empty after popping the top
	cmpl    %ebp, %esp
	je      SingleStack
	popl    %eax ## EAX = value on the second top
	
	cdq
	idivl	%ebx ## EAX = EAX / EBX
	pushl	%eax
	decl	numStack

	jmp	input

remainder:
	## if the stack	is empty
	cmpl    %ebp, %esp
	je      StackEmpty
	popl    %ebx ## EBX = value on the top

	## if the stack is empty after popping the top
	cmpl    %ebp, %esp
	je      SingleStack
	popl    %eax ## EAX = value on the second top

	cdq
	idivl   %ebx ## EDX = EAX % EBX
	pushl   %edx
	decl	numStack

	jmp	input

exponentiation:
	## if the stack	is empty
	cmpl    %ebp, %esp
	je      StackEmpty
	popl    %ebx ## EBX = value on the top

	## if the stack is empty after popping the top
	cmpl    %ebp, %esp
	je      SingleStack
	popl    %eax ## EAX = value on the second top

	cmpl	$1, %ebx ## EAX ^ 1 = EAX
	je	expo_end

	movl	%eax, %ecx ## ECX = EAX
	decl	%ebx

expo_loop:
	## if iIndex >= EBX, goto expo_end
	cmpl    iIndex, %ebx
	jle	expo_end
	
	mull    %ecx ## EAX = EAX * ECX
        incl    iIndex

	jmp	expo_loop
	
expo_end:
	pushl	%eax ## EAX = EAX ^ EBX
	movl	$0, iIndex ## inintialize iIndex
	decl	numStack
	
	jmp	input

LIFOprint:
	movl    iIndex, %eax ## EAX = iIndex
	## if iIndex >= numStack, goro LIFO_end
	cmpl    numStack, %eax
	jge     LIFOprint_end
	
	movl	%esp, %eax ## EAX = value on the top
	movl	iIndex, %ebx
	sall	$2, %ebx

	## EAX = value the iIndex-th stack from the top
	addl	%ebx, %eax
	movl	(%eax), %eax
	incl    iIndex

	## printf("%d\n", EAX)
        pushl   %eax
	pushl   $printFormat
        call    printf
	addl    $8, %esp

        jmp     LIFOprint

LIFOprint_end:
	movl	$0, iIndex ## initialize iIndex
	jmp	input

clear:
	movl	%ebp, %esp
	movl	$0, numStack
	
	jmp	input

duplicate:
	## if the stack	is empty
	cmpl    %ebp, %esp
        je      StackEmpty

	## EAX = value on the top
	movl	(%esp), %eax
	pushl	%eax
	incl	numStack

	jmp	input

swap:
	## if the stack	is empty
	cmpl    %ebp, %esp
        je      StackEmpty
        popl    %ebx ## EBX = value on the top

	## if the stack is empty after popping the top
        cmpl    %ebp, %esp
        je      SingleStack
        popl    %eax ## EAX = value on the second top

	pushl	%ebx
	pushl	%eax

	jmp	input

random:
	pushl	%eax

random_loop:
	## EAX = random number
	## loop until EAX is smaller than 1024
	call	rand
	cmpl	$1024, %eax
	jge	random_loop
	addl	$4, %esp

random_end:
	incl	numStack
	pushl	%eax
	jmp	input


primenum:
	## if the stack	is empty
	cmpl    %ebp, %esp
        je      StackEmpty

	## EAX = value on the top
	movl	%esp, %eax
	movl	(%eax), %eax
	movl    %eax, %ebx ## EBX = EAX
        movl    %eax, %ecx ## ECX = EAX

	## if EAX is 1, no prime number
	cmpl	$1, %eax
	je	input

	jmp	primenum_loop
	
primenum_next:
	## EAX is not a prime number
	## check if EAX-1 is a prime number
	decl	%eax
	movl    %eax, %ebx
        movl    %eax, %ecx

primenum_loop:
	## check if remainder of EAX/EBX is 0
	## EBX = 2 ~ EAX-1
	decl	%ebx
	
	cmpl	$1, %ebx
	## if none of EBX make 0 remainder, EAX is prime number
        je      primenum_end

	cdq
	idivl	%ebx
	
	movl    %ecx, %eax

	cmpl	$0, %edx ## EDX = EAX % EBX
	## if raminder is 0, EAX is not a prime number
	je	primenum_next
	
	jmp	primenum_loop

primenum_end:
	pushl	%eax
	incl	numStack
	
	jmp	input

underbar:
	movl    $0, %eax
        leal    (buffer), %eax ## EAX = address of buffer
	addl	$1, %eax ## skip first byte which is '_'

	pushl	%eax
	call	atoi ## make EAX to integer
	addl	$4, %esp
	
	negl	%eax ## make EAX to negative
	pushl	%eax

	jmp	input
	
StackEmpty:
	## printf("dc : dc: stack empty\n")
	pushl	$printStackEmpty
	call	printf
	addl	$4, %esp
	
	jmp	input

SingleStack:
	## printf("dc : dc: stack empty\n")
	pushl   $printStackEmpty
        call    printf
        addl    $4, %esp
	pushl	%ebx
	
	jmp	input
	
quit:	
	## return 0
	movl    $0, %eax
	movl    %ebp, %esp
	popl    %ebp
	ret
