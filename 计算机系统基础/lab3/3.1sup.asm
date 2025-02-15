.386
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 printf      PROTO C :VARARG
 system      PROTO C :VARARG
 strcmp      PROTO C :VARARG
 getchar     PROTO C :VARARG
 scanf       PROTO C :VARARG

 includelib  kernel32.lib  
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 timeGetTime proto stdcall
 includelib  Winmm.lib
 public match 
 
 public Log3 
 public lpFmt3 
 public lpFmt1 


.DATA
  FIRST  DB 9 DUP(0)   
SDA   DD  2540   
SDB   DD  16      
SDC   DD  16      
SF    DD 0
SECOND DB 9 DUP(0)
BBA   DD  456   
BBB   DD  78      
BBC   DD  9      
BBF    DD ?
THIRD DB 9 DUP(0)
CCA   DD  8888   
CCB   DD  88      
CCC   DD  999      
CCF   DD ?
FOURTH DB 9 DUP(0)
DDA   DD  2600   
DDB   DD  0      
DDC   DD  300      
DDF    DD ?
FIFTH DB 9 DUP(0)
EEA   DD  123   
EEB   DD  456      
EEC   DD  789      
EEF    DD ?
SIXTH DB 9 DUP(0)
FFA   DD  4579   
FFB   DD  2836      
FFC   DD  1997      
FFF    DD ?
SEVENTH DB 9 DUP(0)
GGA   DD  6732   
GGB   DD  3232     
GGC   DD  2345      
GGF    DD ?
EIGHTH DB 9 DUP(0)
HHA   DD  0   
HHB   DD  12700      
HHC   DD  0   
HHF    DD ?
NINTH DB 9 DUP(0)
IIA   DD  2900   
IIB   DD  130    
IIC   DD  89      
IIF    DD ?
TENTH DB 9 DUP(0)
JJA   DD  1888   
JJB   DD  44      
JJC   DD  2022      
JJF    DD ?
LOWF DD 30 DUP(0)
MIDF DD 30 DUP(0)
HIGHF DD 30 DUP(0)
COUNTL DD 0
COUNTM DD 0
COUNTH DD 0
TIMES DD 1000000
  lpFmt1	DB	"%s",0ah, 0dh, 0
  lpFmt2	DB	"%s",0
  lpFmt3	DB	"%x ",0
  szMsg db "Over!!",0
;REQUIRE A 0
__t1		dd	?
__t2		dd	?
__fmtTime	db	0ah,0dh,"Time elapsed is %ld ms",2 dup(0ah,0dh),0
  BNAME DB   'myh';,0  ;用户名
  NAMENUM EQU $-BNAME        ;用户名长度
  BPASS DB   '156308';,0  ;密码
  PASSNUM EQU $-BPASS         ;密码长度
  Log1  DB  'Username:',0
  Log2  DB  'Password:',0
  Log3  DB  'Wrong! Try again',0
  Log4  DB  'Log in successfully！Enter any key to continue.',0
  time  dd 0
  num   dd 0
  match DB 0
  buf   DB   20 dup(0)
.stack 200
.code
winTimer	proc stdcall, flag:DWORD
		jmp	__L1
__L1:		call	timeGetTime
		cmp	flag, 0
		jnz	__L2
		mov	__t1, eax
		ret	4
__L2:		mov	__t2, eax
		sub	eax, __t1
		invoke	printf,offset __fmtTime,eax
		ret	4
winTimer	endp

StrCmpr proc c uses ecx ebx edx,tar:ptr sbyte, src:ptr sbyte, srcnum:DWORD
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
StrCmpr endp

LOGIN proc c
    invoke printf,offset lpFmt1,OFFSET Log1
    invoke scanf ,offset lpFmt2,OFFSET buf;输入账号
    mov ecx,0
LG1: 
    invoke StrCmpr,offset buf,offset BNAME,NAMENUM
    cmp match,1
    jne LG3
    invoke printf,offset lpFmt1,OFFSET Log2
    invoke scanf ,offset lpFmt2,OFFSET buf;输入密码
    mov ecx,0
LG2: 
    invoke StrCmpr,offset buf,offset BPASS,PASSNUM
    cmp match,1
    jne LG3
    invoke printf,offset lpFmt1,OFFSET Log4
    invoke getchar
    invoke getchar
LG3: 
    RET;
LOGIN endp

exeute proc c
		invoke winTimer,0
BEGUN:
		MOV ESI, OFFSET FIRST
		MOV EBX, 10
		MOV COUNTL,0
		MOV COUNTH,0
		MOV COUNTM,0
		DEC TIMES
		MOV EBP, TIMES
		JZ LAST 
START1:
        ADD ESI, 09H
        MOV EAX, [ESI]
        IMUL EAX,5
        ADD EAX, 04H[ESI]
        SUB EAX, 08H[ESI]    
        ADD EAX, 100
        CWD
        SAR EAX,7
        CMP EAX,100
        JNE EQUAL
        JMP NEW
		
EQUAL:  CMP EAX,100
        JG  A1                       
        jmp A2
         
A1:  	MOV EDI,COUNTH
		IMUL EDI, 16
		MOV HIGHF[EDI],EAX
		MOV EBP, [ESI]
		MOV HIGHF[EDI+4],EBP
		MOV EBP, 04H[ESI]
		MOV HIGHF[EDI+8],EBP
		MOV EBP, 08H[ESI]
		MOV HIGHF[EDI+12],EBP
		ADD ESI,10H
		INC COUNTH
		DEC EBX
		JZ BY
		JMP START1
		
A2:		MOV EDI,COUNTL
		IMUL EDI, 16
		
		MOV LOWF[EDI],EAX
		MOV EBP, [ESI]
		MOV LOWF[EDI+4],EBP
		MOV EBP, 04H[ESI]
		MOV LOWF[EDI+8],EBP
		MOV EBP, 08H[ESI]
		MOV LOWF[EDI+12],EBP
		ADD ESI,10H
		INC COUNTL
		DEC EBX
		JZ BY
		JMP START1
		
NEW:	MOV EDI,COUNTM
		IMUL EDI, 16
		MOV MIDF[EDI],EAX
		MOV EBP, [ESI]
		MOV MIDF[EDI+4],EBP
		MOV EBP, 04H[ESI]
		MOV MIDF[EDI+8],EBP
		MOV EBP, 08H[ESI]
		MOV MIDF[EDI+12],EBP
		ADD ESI,10H
		INC COUNTM
		DEC EBX
		JZ BY
		JMP START1 
		
BY:		JMP BEGUN

LAST:	invoke printf,OFFSET lpFmt3,MIDF
		invoke printf,OFFSET lpFmt3,MIDF+4
		invoke printf,OFFSET lpFmt3,MIDF+8
		invoke printf,OFFSET lpFmt3,MIDF+16
		invoke printf,OFFSET lpFmt3,MIDF+20
		invoke printf,OFFSET lpFmt3,MIDF+24
		invoke printf,OFFSET lpFmt3,MIDF+28
		invoke printf,OFFSET lpFmt3,MIDF+32
		invoke printf,OFFSET lpFmt3,MIDF+36
		invoke printf,OFFSET lpFmt3,MIDF+40
		invoke printf,OFFSET lpFmt3,MIDF+44

		invoke winTimer,1
		invoke printf,offset szMsg
		MOV EAX,10000000;
		MOV TIMES,EAX
		RET

exeute endp

END
