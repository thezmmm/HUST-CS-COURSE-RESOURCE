.686p
.model flat,c

 
 ExitProcess proto  stdcall :dword
 includelib  kernel32.lib
 printf      proto c :vararg
 includelib  libcmt.lib
 includelib  winmm.lib
 includelib  legacy_stdio_definitions.lib
 timeGetTime proto stdcall
.data
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
TIMES DD 100000000
__t1		dd	?
__t2		dd	?
__fmtTime	db	0ah,0dh,"Time elapsed is %ld ms",2 dup(0ah,0dh),0
szMsg db "在汇编程序中调用C的PRINTF函数!",0
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
main proc
		invoke printf,offset szMsg
		invoke winTimer,0;
BEGIN:	MOV ESI, OFFSET FIRST
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
        MOV ECX, 128
        IDIV CX
        CMP EAX,100
        JNE EQUAL
        JMP NEW
		
EQUAL:  CMP EAX,100
        JG  A1                       
        jmp A2
         
A1:  	MOV EDI,COUNTH
		IMUL EDI, 16
		MOV HIGHF[EDI],EAX
		MOV EBP, 04H[ESI]
		MOV HIGHF[EDI+4],EBP
		MOV EBP, 08H[ESI]
		MOV HIGHF[EDI+8],EBP
		MOV EBP, 12H[ESI]
		MOV HIGHF[EDI+12],EBP
		ADD ESI,10H
		INC COUNTH
		DEC EBX
		JZ BY
		JMP START1
		
A2:		MOV EDI,COUNTL
		IMUL EDI, 16
		
		MOV LOWF[EDI],EAX
		MOV EBP, 04H[ESI]
		MOV LOWF[EDI+4],EBP
		MOV EBP, 08H[ESI]
		MOV LOWF[EDI+8],EBP
		MOV EBP, 12H[ESI]
		MOV LOWF[EDI+12],EBP
		ADD ESI,10H
		INC COUNTL
		DEC EBX
		JZ BY
		JMP START1
		
NEW:	MOV EDI,COUNTM
		IMUL EDI, 16
		MOV MIDF[EDI],EAX
		MOV EBP, 04H[ESI]
		MOV MIDF[EDI+4],EBP
		MOV EBP, 08H[ESI]
		MOV MIDF[EDI+8],EBP
		MOV EBP, 12H[ESI]
		MOV MIDF[EDI+12],EBP
		ADD ESI,10H
		INC COUNTM
		DEC EBX
		JZ BY
		JMP START1 
		
BY:		JMP BEGIN

LAST:	invoke winTimer,1;
		invoke printf,offset szMsg
		invoke ExitProcess, 0
main endp
	

end
