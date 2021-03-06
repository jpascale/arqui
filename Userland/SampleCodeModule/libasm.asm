global sys_write
global sys_read
global sys_time
global sys_time_write
global sys_screen_saver_set

sys_write:
	push rbp
	mov rbp,rsp
	push rbx

	mov rbx,1 	; STDOUT	
	mov rax,4 	; sys_call write
	mov rcx,rdi ; char
	mov rdx,rsi ; len
	int 80h

	pop rbx
	mov rsp,rbp
	pop rbp
	ret

sys_read:
	push rbp
	mov rbp,rsp
	push rbx

	mov rcx, rdi
	mov rdx,rsi ; len
	mov rax,3 	; sys_call read
	int 80h

	pop rbx
	mov rsp,rbp
	pop rbp
	ret

sys_time:
	push rbp
	mov rbp,rsp
	push rbx

	mov rbx,rsi
	mov rcx, rdi
	mov rax,2 	; sys_call get_time
	int 80h

	pop rbx
	mov rsp,rbp
	pop rbp
	ret

sys_time_write:
	push rax
	push rbx
	push rdx

	mov rax, 5	; sys_call write_time 
	mov rbx, rdi
	mov rdx, rsi
	int 80h

	pop rdx
	pop rbx
	pop rax
	ret

sys_screen_saver_set:
	push rax
	push rdx

	mov rax, 6 ; sys_call screen_saver_set
	mov rdx, rdi
	int 80h

	pop rdx
	pop rax
	ret