.386
.model flat, c

public asm_avg
public c_in_asm

.data
c_in_asm dd 10

.code


;C����printv��ԭ��
printv PROTO C, v:DWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;int asm_avg(int num1,int num2,int num3);
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
asm_avg proc num1:dword,num2:dword,num3:dword
    MOV     EAX,num1
    SAL     EAX,2
    MOV     EBX,num2
    SAL     EBX,1
    ADD     EAX,EBX
    MOV     EBX,num3
    ADD     EAX,EBX
    MOV     EDX,0
    MOV     ECX,7
    DIV     ECX
    ;PUSH  EAX
    invoke printv, EAX
    ;POP  EAX
	;��һ�룬ΪʲôEAX���ñ������ڵ���printv��EAX����ı�
    ;����EAX����asm_avg�ķ���ֵ
    RET
asm_avg endp

end
