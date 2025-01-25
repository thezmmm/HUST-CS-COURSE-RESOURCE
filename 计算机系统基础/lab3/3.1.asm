.686p
.model flat,c

 
 ExitProcess proto  stdcall :dword
 printf      PROTO C :VARARG
 system      PROTO C :VARARG
 strcmp      PROTO C :VARARG
 getchar     PROTO C :VARARG
 scanf       PROTO C :VARARG
 LOGIN       PROTO C
 exeute      PROTO C
 StrCmpr     PROTO C
 extern match:byte

.data

TIMES1 DD 3
szMsg db "Over!!",0
Fmt2	DB	"%s",0
shibai db "三次输入了错误的账号密码，拒绝登入本系统",0
shibai1 db "Try again!",0
JIXU db "q";,0
JIXUNUM EQU $-JIXU 
buffer   DB   20 dup(0)
Fmt3	DB	"%08x ",0
.stack
.code
StrCmpM proc c uses ecx ebx edx,tar:ptr sbyte, src:ptr sbyte, srcnum:DWORD
    local u:dword
    mov u,0
    mov ebx,tar
    mov edx,src
 e7cmp:
    cmp u,0
    je adtion
    inc ebx
    inc edx
    adtion:
    inc u
    mov al,byte ptr [ebx]
    mov ah,byte ptr [edx]
    cmp ah,0
    je _end
    cmp al,byte ptr [edx]
    je e7cmp
  _end:
    dec u
    mov esi,srcnum
    cmp esi,u
    jne Dif
 Same:
    mov match,1
    RET
 Dif:
    mov match,0
    RET
StrCmpM endp
main proc

		call LOGIN
		CMP match,0
		JE ERROR1
		JMP BEGIA
		;invoke winTimer,0
ERROR1:
		invoke printf, OFFSET shibai1
		DEC TIMES1
		JZ ERROR2
		call LOGIN
		cmp match,0
		JE ERROR1
		JMP BEGIA
ERROR2: invoke printf,offset shibai
		invoke ExitProcess, 0
BEGIA:	call exeute

ANOTHER: invoke scanf, offset Fmt2,OFFSET buffer
		invoke StrCmpM,offset buffer,offset JIXU,JIXUNUM
		cmp match,1
		JNE BEGIA
		JMP ENDDER
ENDDER: invoke ExitProcess, 0

		
main endp
	

end