; BLG 413E - SYSTEM PROGRAMMING
; PROJECT 1 - PART 1
; TEAM 6
;
; 150120107 AHMET TÜRK
; 150130039 OZAN ATA
; 150130132 CAN YILMAZ ALTINİĞNE

segment .bss
	size_of_gen resd 1                  ; SIZE OF GENERATION
	start_address resd 1                ; START ADDRESS OF PREVIOUS ARRAY
	next_start_address resd 1           ; START ADDRESS OF NEXT GENERATION ARRAY

segment .data                           ; RULES ARRAY KEEPS THE BINARY FORM OF OUR DECIMAL RULE NUMBER
	rules dd 0, 0, 0, 0, 0, 0, 0, 0     ; THIS ARRAY KEEPS RULES AND TRIOS KEEP THREE MEMORY LOCATIONS IN ARRAY
	trios dd 0, 0, 0                    ; WHICH STANDS IN ORDER
	total_point dd 0                    ; TOTAL POINT ENABLE US TO HAVE THE LOCATION IN RULES ARRAY WE WANT
    keep_ebx dd 0

segment .text
global generate_next_seq

carry_one:                          ; IF CARRY IS 1 CARRY_ONE PUTS 1 IN THE CURRENT POSITION IN RULES ARRAY
	mov dword[rules + 4*ebx], 1
	inc ebx
	cmp ebx, 8                      ; CONVERTING DECIMAL TO BINARY IS FINISHED ?
	je painting
	jmp shifting_number

carry_zero:                         ; SAME THING LIKE CARRY_ONE BUT THIS TIME 0 WILL BE PUT IN RULES ARRAY
	mov dword[rules + 4*ebx], 0
	inc ebx
	cmp ebx, 8
	je painting
	jmp shifting_number

generate_next_seq:				; ENTRY POINT
	push ebp
	mov ebp, esp
	mov dword[keep_ebx], ebx
	mov ebx, 0
	mov eax, [ebp+16] ; THIS IS THE RULE NUMBER

shifting_number:        ; SHIFT RIGHT THE RULE NUMBER TO CONVERT DECIMAL TO BINARY
	shr eax, 1
	jc carry_one
	jmp carry_zero

painting:               ; PAINTING DECIDES THE 0/1 SITUATION OF LOCATION IN NEXT ARRAY
	mov eax, [ebp+8]    ; START ADDRESS OF PREVIOUS ARRAY
	mov ebx, [ebp+12]   ; START ADDRESS OF NEXT ARRAY
	mov ecx, [ebp+20]   ; SIZE OF GENERATION
	mov dword[size_of_gen], ecx         ; PUT THEM INTO MEMORY
	mov dword[start_address], eax
	mov dword[next_start_address], ebx

push_front_to_stack:            ; FIRST TWO ELEMENTS AND THE ZERO WHICH IS IN THE LEFT SIDE OF THE FIRST ELEMENT OF THE ARRAY
	push dword 0                ; PUSH THREE OF THEM INTO STACK AND CALCULATE THE ELEMENT IN THE NEXT ARRAY
	mov eax, [start_address]
	push dword[eax]
	add eax, 4
	push dword[eax]
	jmp calculate

push_last_to_stack:             ; LAST TWO ELEMENTS AND THE ZERO WHICH IS IN THE RIGHT SIDE OF THE LAST ELEMENT OF THE ARRAY
	mov eax, [start_address]    ; PUSH THREE OF THEM INTO STACK AND CALCULATE THE ELEMENT IN THE NEXT ARRAY
	push dword[eax]
	add eax, 4
	push dword[eax]
	push dword 0
	jmp calculate

push_middle:                    ; IF ALL THREE ELEMENTS ARE IN THE ARRAY, PUSH THREE OF THEM TO STACK AND CALCULATE
	mov eax, [start_address]
	push dword[eax]
	add eax, 4
	mov dword[start_address], eax
	push dword[eax]
	add eax, 4
	push dword[eax]
	jmp calculate

calculate:                      ; POP THREE ELEMENTS FROM THE STACK
	pop edx
	mov dword[trios+8], edx     ; PUT THEM IN THE TRIOS ARRAY
	pop edx
	mov dword[trios+4], edx
	pop edx
	mov dword[trios], edx
	mov eax, [trios]            ; FIRST ELEMENT IN THE TRIOS ARRAY WILL BE MULTIPLIED BY 4
	mov ebx, 4
	mul ebx
	mov dword[total_point], eax ; PUT THE RESULT IN TOTAL_POINT
	mov eax, [trios+4]          ; SECOND ELEMENT IN THE TRIOS ARRAY WILL BE MULTIPLIED BY 2
	mov ebx, 2
	mul ebx
	add eax, [total_point]      ; ADD TOTAL POINT TO RESULT AND PUT IT IN TOTAL_POINT
	add eax, [trios+8]          ; ADD RESULT THE LAST ELEMENT OF THE TRIOS
	mov edx, [rules + 4*eax]    ; THE RESULT IS 0 AT LEAST OR 7 AT MOST MULTIPLY THE RESULT BY 4 AND FIND THE 0 OR 1 SITUATION IN RULES ARRAY
	mov ecx, [next_start_address]
	mov dword[ecx], edx         ; THE RESULT IS ASSIGNED TO THE LOCATION IN THE NEXT ARRAY
	mov eax, ecx
	add eax, 4                  ; SKIP TO THE NEXT LOCATION IN THE NEXT ARRAY
	mov dword[next_start_address], eax  ; NEW ADDRESS
	mov eax, [size_of_gen]              ; DECREMENT THE SIZE BECAUSE SITATION OF ONE LOCATION HAS BEEN DECIDED
	dec eax
	mov [size_of_gen], eax
	cmp eax, 1                      ; IF WE ARE AT THE SECOND LAST ELEMENT OF ARRAY JMP LAST_TO_STACK
	je push_last_to_stack
	cmp eax, 0                      ; ARE WE DONE ?
	je finish
	jmp push_middle

finish:
    mov ebx, [keep_ebx]
	mov esp, ebp
 	pop ebp
	ret
