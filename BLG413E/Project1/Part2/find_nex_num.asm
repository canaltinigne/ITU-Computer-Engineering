; BLG 413E - SYSTEM PROGRAMMING
; PROJECT 1 - PART 2
; TEAM 6
;
; 150120107 AHMET TÜRK
; 150130039 OZAN ATA
; 150130132 CAN YILMAZ ALTINİĞNE

segment .data
	rules          times 32 dd 0            ; RULE ARRAY
    cnesw          dd 0, 0, 0, 0, 0         ; SITUATIONS OF DIRECTIONS
    total_number   dd 0
    column_number  dd 0                     ; COLUMN NUMBER OF BIG MATRIX
	start_address  dd 0                     ; CURRENT LOCATION IN BIG MATRIX
    keep_ebx       dd 0

segment .text
global find_nex_num

find_nex_num:
    push ebp
	mov ebp, esp
	mov dword[keep_ebx], ebx
	mov ecx, [ebp+8]                        ; CURRENT LOCATION IN THE EXTENDED MATRIX
    mov dword[start_address], ecx
    mov ecx, [ebp+16]                       ; COLUMN NUMBER OF THE EXTENDED MATRIX
    mov dword[column_number], ecx
    mov ecx, [ebp+12]
    mov dword[total_number], 0              ; TOTAL NUMBER KEEPS THE 16*C + 8*N + 4*E + 2*S + W
    mov edx, 0                              ; PUT 0 TO EDX

moving_rule:
    mov eax, [ecx + 4*edx]                  ; ASSIGNING THE ELEMENTS OF RULE ARRAY
    mov dword[rules + 4*edx], eax
    inc edx
    cmp edx, 32                             ; UNTIL 32
    je  find_them
    jmp moving_rule

find_them:
    mov ebx, [start_address]            ; EBX = CURRENT LOCATION IN EXTENDED MATRIX SAY N
    mov ecx, [column_number]            ; ECX = COLUMN NUMBER OF THE EXTENDED MATRIX
    mov eax, [ebx + 4*ecx + 4]          ; N+COL+1 IS CENTER WE MULTIPLY IT BY 4 BECAUSE DWORD TO BYTE TRANSFORMATION
    mov dword[cnesw], eax               ; PUT C
    mov eax, [ebx + 4]                  ; N+1 IS NORTH
    mov dword[cnesw+4], eax
    mov eax, [ebx + 4*ecx + 8]          ; N+COL+2 IS EAST
    mov dword[cnesw+8], eax
    mov eax, [ebx + 8*ecx + 4]          ; N+2*COL+1 IS SOUTH
    mov dword[cnesw+12], eax
    mov eax, [ebx + 4*ecx]              ; N+COL IS WEST
    mov dword[cnesw+16], eax
    mov ecx, 0                          ; CNESW IS COMPLETED
    mov ebx, 16

control_rule:
    mov eax, [cnesw + 4*ecx]            ; MULTIPLY CNESW ELEMENTS WITH 16,8,4,2,1 RESPECTIVELY
    mul ebx
    add eax, [total_number]
    mov dword[total_number], eax        ; KEEP THE TOTAL IN TOTAL NUMBER
    shr ebx,1
    inc ecx
    cmp ecx, 5
    jne control_rule
    mov ebx, [keep_ebx]
    mov edx, [total_number]
    mov eax, [rules + 4*edx]            ; FIND THE ELEMENT IN RULE ARRAY WHICH CORRESPONDS TO THE RESULT WHICH IS BETWEEN 0 AND 31
 	pop ebp                             ; PUT THE RESULT IN EAX RETURN IT AS INTEGER (0/1)
	ret
