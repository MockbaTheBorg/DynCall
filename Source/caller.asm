PUBLIC _DynCall

.code
 
_DynCall PROC

	push rsi							; Save some nonvolatile registers
	push rdi							;
	push r12							;

	sub	rsp, 10h						; Give the stack some slack
	mov	r12, rsp						; and save it

	mov rax, [rcx]						; Gets the number of arguments onto RAX

	add rcx, 8							; Gets the address of the called function 
	mov	r10, [rcx]						; onto R10

	test eax, eax						; Do we have any arguments?
	jz noargs							;

	shl eax,3							; Open enough space in the stack for the arguments
	sub rsp, rax						;
	shr eax,3							;

	add rcx, 8							; Points RCX to the first argument

	mov rsi, rcx						; Copies all the arguments to the stack
	mov rcx, rax						;
	mov rdi, rsp						;
	rep movsq							;

	mov	rcx, [rsp]						; Place arg1 on its register (RCX/XMM0)
	movq xmm0, rcx						;
	cmp eax, 1							; Only one arg?
	je noargs							; ... yes.

	mov rdx, [rsp + 08h]				; Place arg2 (if any) on its register (RDX/XMM1)
	movq xmm1, rdx						;
	cmp eax, 2							; Only two args?
	je noargs							; ... yes.

	mov r8, [rsp + 10h]					; Place arg3 (if any) on its register (R8/XMM2)
	movq xmm2, r8						;
	cmp eax, 3							; Only three args?
	je noargs							; ... yes.

	mov r9, [rsp + 18h]					; Place arg4 (if any) on its register (R9/XMM3)
	movq xmm3, r9						;

noargs:
    call r10							; Executes the called function
										;   Which will probably crash ...
										;      ... or maybe not!  :)

return:
	mov rsp, r12						; Restore the stack and...
	add	rsp, 10h						; get the stack slack back

	pop r12								; Restore nonvolatile registers
	pop rdi								;
	pop rsi								;

	ret									; Back to the original caller

_DynCall ENDP

END
